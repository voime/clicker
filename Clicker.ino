#include <SimpleTimer.h>
#include <Bounce.h>


int sp, osp, de = 0; // speed, old speed and delay
int pinBtn = 2; // start/stop push button
int pinLed = 13; // indicatro led
int pinPot = 0; // potensiometer
int ot; // Timer object number
bool st; // started or not

int s = 5; // delay for keypress

// the timer object
SimpleTimer timer;

Bounce bouncer = Bounce( pinBtn, 5 ); 

// a function to be executed periodically
void repeatMe() {
    Keyboard.set_key1(KEY_1);
    Keyboard.send_now();
    digitalWrite(pinLed, HIGH);
    delay(s);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    digitalWrite(pinLed, LOW);
}

void setup() {
    Serial.begin(9600);
    
      pinMode(pinLed, OUTPUT);
      //pinMode(c_pinPot[0], INPUT);
      pinMode(pinBtn, INPUT_PULLUP);
      
      sp = osp = analogRead(pinPot);
      de = convertSpeed(sp);
      ot = timer.setInterval(de, repeatMe);
}

void loop() {

      //read potensiometer and change speed    
      sp = analogRead(pinPot);
      
      if (sp > (osp + 10) or sp < (osp - 10)) {
        de = convertSpeed(sp);
        timer.delayTimer(de, ot);
        osp = sp;
        
        Serial.print("Change speed:");
        Serial.print(sp);
        Serial.print(":");
        Serial.print(osp);
        Serial.print(":");
        Serial.println(de);
  
      }
  
      // start/stop
      if ( bouncer.update() ) {
        if ( bouncer.read() == LOW) {
          Serial.println("Button pressed");
          st = !st;
        }
      }

      if (st) {
        timer.enable(ot);
        //digitalWrite(c_pinLed[0], HIGH);
      }else{
        timer.disable(ot);
        //digitalWrite(c_pinLed[0], LOW);       
      }
    
    timer.run();

}

long convertSpeed(int val) {
  return map(val, 525, 1023, 1, 3000);
}


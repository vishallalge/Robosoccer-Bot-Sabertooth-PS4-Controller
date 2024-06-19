
#include <PS4BT.h>
#include <usbhub.h>

#include <SabertoothSimplified.h>
#include <SoftwareSerial.h>


#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>


#define pwmMax 127  // or less, if you want to lower the maximum motor's speed
//with Sabertooth, the maximum speed is 127 = full forward or -127 full reverse

// defining the range of potentiometer's rotation
const int potMini = 208;
const int potMaxi = 815;

#define motLeft 1
#define motRight 2
#define potL A0
#define potR A1



USB Usb;
BTD Btd(&Usb);

PS4BT PS4(&Btd, PAIR);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;


int DataValueL = 512;  //middle position 0-1024
int DataValueR = 512;  //middle position 0-1024

SoftwareSerial SWSerial(NOT_A_PIN, 7);  //declare the Pin 8 to be used to communicate with Sabertooth
SabertoothSimplified ST(SWSerial);      //open a serial COM on previously identified pin2

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial)
    ;
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1)
      ;
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));


  // Serial.begin(115200);   // serial between Arduino and Simtools on RX pin
  SWSerial.begin(38400);  // serial between Arduino and Sabertooth on SWSerial pin
  //DIP switches 2, 4 and 5 OFF

  // stop motors at startup
  ST.motor(motLeft, 0);
  ST.motor(motRight, 0);
}

void loop() {
  Usb.Task();
  if (PS4.connected()) {

    
    if ((PS4.getAnalogHat(LeftHatY) > 155 || PS4.getAnalogHat(LeftHatY) < 100)) {
      if (PS4.getAnalogHat(LeftHatY) > 155) {
        if (PS4.getButtonPress(L1)) {


          ST.motor(motLeft, 0);
          ST.motor(motRight, 0);

          // Serial.print(F("\r\n<-Back L1 "));

          // ST.motor(motLeft, map(PS4.getAnalogHat(RightHatX), 145, 255, 0, -127));
          // ST.motor(motRight, map(PS4.getAnalogHat(LeftHatY), 145, 255, 0, 127));

          // Serial.println(map(PS4.getAnalogHat(RightHatX), 145, 255, 0, -127));
          // Serial.println(map(PS4.getAnalogHat(RightHatX), 145, 255, 0, 127));

        } else if (PS4.getButtonPress(R1)) {


          ST.motor(motLeft, 0);
          ST.motor(motRight, 0);

          // Serial.print(F("\r\nBack R1->"));

          // ST.motor(motLeft, map(PS4.getAnalogHat(RightHatX), 145, 255, 0, 127));
          // ST.motor(motRight, map(PS4.getAnalogHat(LeftHatY), 145, 255, 0, -127));

          // Serial.println(map(PS4.getAnalogHat(RightHatX), 145, 255, 0, 127));
          // Serial.println(map(PS4.getAnalogHat(RightHatX), 145, 255, 0, -127));

        } else if ((PS4.getAnalogHat(RightHatX) > 155 || PS4.getAnalogHat(RightHatX) < 100)) {
          if (PS4.getAnalogHat(RightHatX) > 155) {
            Serial.print(F("\r\nback right"));

            ST.motor(motLeft, 0);
            ST.motor(motRight, map(PS4.getAnalogHat(RightHatX), 145, 255, 0, -127));

            Serial.println(0);
            Serial.println(map(PS4.getAnalogHat(RightHatX), 145, 255, 0, -127));
          } else {
            Serial.print(F("\r\nback Left"));


            ST.motor(motLeft, map(PS4.getAnalogHat(RightHatX), 110, 0, 0, -127));
            ST.motor(motRight, 0);

            Serial.println(map(PS4.getAnalogHat(RightHatX), 110, 0, 0, -127));
            Serial.println(0);
          }
        } else {
          Serial.print(F("\r\nback "));
          ST.motor(motLeft, map(PS4.getAnalogHat(LeftHatY), 145, 255, 0, -127));
          ST.motor(motRight, map(PS4.getAnalogHat(LeftHatY), 145, 255, 0, -127));

          Serial.println(map(PS4.getAnalogHat(LeftHatY), 145, 255, 0, -127));
        }
      } else {
        if (PS4.getButtonPress(L1)) {

          ST.motor(motLeft, 0);
          ST.motor(motRight, 0);
          // Serial.print(F("\r\n<- Front L1 "));
          // ST.motor(motLeft, map(PS4.getAnalogHat(LeftHatY), 110, 0, 0, 127));
          // ST.motor(motRight, map(PS4.getAnalogHat(LeftHatY), 110, 0, 0, -127));

          // Serial.println(map(PS4.getAnalogHat(LeftHatY), 110, 0, 0, 127));
          // Serial.println(map(PS4.getAnalogHat(LeftHatY), 110, 0, 0, -127));

        } else if (PS4.getButtonPress(R1)) {
          ST.motor(motLeft, 0);
          ST.motor(motRight, 0);
          // Serial.print(F("\r\nFront R1->"));

          // ST.motor(motLeft, map(PS4.getAnalogHat(LeftHatY), 110, 0, 0, -127));
          // ST.motor(motRight, map(PS4.getAnalogHat(LeftHatY), 110, 0, 0, 127));

          // Serial.println(map(PS4.getAnalogHat(LeftHatY), 110, 0, 0, -127));
          // Serial.println(map(PS4.getAnalogHat(LeftHatY), 110, 0, 0, 127));

        } else if ((PS4.getAnalogHat(RightHatX) > 155 || PS4.getAnalogHat(RightHatX) < 100)) {
          if (PS4.getAnalogHat(RightHatX) > 155) {
            Serial.print(F("\r\nfront right"));


            ST.motor(motLeft, 0);
            ST.motor(motRight, map(PS4.getAnalogHat(RightHatX), 145, 255, 0, 127));

            Serial.println(0);
            Serial.println(map(PS4.getAnalogHat(RightHatX), 145, 255, 0, 127));
          } else {
            Serial.print(F("\r\nfront left"));

            ST.motor(motLeft, map(PS4.getAnalogHat(RightHatX), 100, 0, 0, 127));
            ST.motor(motRight, 0);

            Serial.println(map(PS4.getAnalogHat(RightHatX), 100, 0, 0, 127));
            Serial.println(0);
          }
        } else {
          Serial.print(F("\r\nfront"));

          ST.motor(motLeft, map(PS4.getAnalogHat(LeftHatY), 110, 0, 0, 127));
          ST.motor(motRight, map(PS4.getAnalogHat(LeftHatY), 110, 0, 0, 127));

          Serial.println(map(PS4.getAnalogHat(LeftHatY), 110, 0, 0, 127));
        }
      }
    }  // end LeftHatY

    else if ((PS4.getAnalogHat(RightHatX) > 155 || PS4.getAnalogHat(RightHatX) < 100)) {
      if (PS4.getAnalogHat(RightHatX) > 155) {
        Serial.print(F("\r\nRight->"));

        ST.motor(motLeft, 0);
        ST.motor(motRight, map(PS4.getAnalogHat(RightHatX), 145, 255, 0, 127));

        Serial.println(0);                                                   // for motor 1
        Serial.println(map(PS4.getAnalogHat(RightHatX), 145, 255, 0, 127));  // for motor 2
      } else {
        Serial.print(F("\r\n<-left"));

        ST.motor(motLeft, map(PS4.getAnalogHat(RightHatX), 100, 0, 0, 127));
        ST.motor(motRight, 0);

        Serial.println(map(PS4.getAnalogHat(RightHatX), 100, 0, 0, 127));  // for motor 1
        Serial.println(0);                                                 // for motor 2
      }
    }  // end RightHatX

    else if (PS4.getButtonPress(DOWN) && PS4.getButtonPress(CIRCLE)) {
      Serial.print(F("\r\ndown right->"));
      ST.motor(motLeft, 0);
      ST.motor(motRight, -127);

    } else if (PS4.getButtonPress(DOWN) && PS4.getButtonPress(SQUARE)) {
      Serial.print(F("\r\n<-down left"));

      ST.motor(motLeft, -127);
      ST.motor(motRight, 0);

    } else if (PS4.getButtonPress(UP) && PS4.getButtonPress(CIRCLE)) {
      Serial.print(F("\r\nup right->"));

      ST.motor(motLeft, 0);
      ST.motor(motRight, 127);


    } else if (PS4.getButtonPress(UP) && PS4.getButtonPress(SQUARE)) {
      Serial.print(F("\r\n<-up left"));
      ST.motor(motLeft, 127);  // zero speed
      ST.motor(motRight, 0);   // full speed
    }

    else if (PS4.getButtonPress(UP)) {
      Serial.print(F("\r\nUp"));

      ST.motor(motLeft, 127);
      ST.motor(motRight, 127);
    } else if (PS4.getButtonPress(DOWN)) {
      Serial.print(F("\r\nDown"));

      ST.motor(motLeft, -127);
      ST.motor(motRight, -127);
    } else if (PS4.getButtonPress(LEFT)) {
      Serial.print(F("\r\nLeft"));

      ST.motor(motLeft, 127);
      ST.motor(motRight, 0);
    } else if (PS4.getButtonPress(RIGHT)) {
      Serial.print(F("\r\nRight"));

      ST.motor(motLeft, 0);
      ST.motor(motRight, 127);
    } else if (PS4.getButtonPress(TRIANGLE)) {
      Serial.print(F("\r\nUp Triangle"));
      ST.motor(motLeft, 127 / 2);
      ST.motor(motRight, 127 / 2);
    } else if (PS4.getButtonPress(CIRCLE)) {
      Serial.print(F("\r\nRight Circle"));

      ST.motor(motLeft, 127 / 4);
      ST.motor(motRight, 127 / 2);
    } else if (PS4.getButtonPress(CROSS)) {
      Serial.print(F("\r\nDown Cross"));

      ST.motor(motLeft, 127 / 2);
      ST.motor(motRight, 127 / 2);
    } else if (PS4.getButtonPress(SQUARE)) {
      Serial.print(F("\r\nLeft Square"));
      ST.motor(motLeft, 127 / 2);
      ST.motor(motRight, 127 / 4);
    } else if (PS4.getButtonPress(L1)) {
      Serial.print(F("\r\nL1"));

      ST.motor(motLeft, 0);
      ST.motor(motRight, 0);
    } else if (PS4.getButtonPress(R1)) {
      Serial.print(F("\r\nR1"));


      ST.motor(motLeft, 0);
      ST.motor(motRight, 0);
    } else {
      Serial.print(F("\r\nstop"));
      ST.motor(motLeft, 0);
      ST.motor(motRight, 0);
    }
    if (PS4.getButtonClick(PS)) {
      PS4.disconnect();
      ST.motor(motLeft, 0);
      ST.motor(motRight, 0);
    }
  } else {
    Serial.print(F("\r\nstop!!!"));
    ST.motor(motLeft, 0);
    ST.motor(motRight, 0);
  }
}

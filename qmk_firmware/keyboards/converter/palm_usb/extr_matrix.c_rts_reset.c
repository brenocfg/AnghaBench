#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  PinDirectionOutput ; 
 scalar_t__ PinLevelHigh ; 
 scalar_t__ PinLevelLow ; 
 int /*<<< orphan*/  RTS_PIN ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 scalar_t__ digitalRead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digitalWrite (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pinMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint8_t rts_reset(void) {
    static uint8_t firstread ;
/* bounce RTS so device knows it is rebooted */

// On boot, we keep rts as input, then switch roles here
// on leaving sleep, we toggle the same way

    firstread=digitalRead(RTS_PIN);
   // printf("r%02X:", firstread);

    pinMode(RTS_PIN, PinDirectionOutput);

    if (firstread == PinLevelHigh) {
        digitalWrite(RTS_PIN, PinLevelLow);
    } 
     _delay_ms(10);
    digitalWrite(RTS_PIN, PinLevelHigh);  
    

/* the future is Arm 
    if (palReadPad(RTS_PIN_IOPRT) == PinLevelLow)
  {
    _delay_ms(10);
    palSetPadMode(RTS_PINn_IOPORT, PinDirectionOutput_PUSHPULL);
    palSetPad(RTS_PORT, RTS_PIN);
  }
  else
  {
    palSetPadMode(RTS_PIN_RTS_PORT, PinDirectionOutput_PUSHPULL);
    palSetPad(RTS_PORT, RTS_PIN);
    palClearPad(RTS_PORT, RTS_PIN);
    _delay_ms(10);
    palSetPad(RTS_PORT, RTS_PIN);
  }
*/


 _delay_ms(5);  
 //print("rts\n");
 return 1;
}
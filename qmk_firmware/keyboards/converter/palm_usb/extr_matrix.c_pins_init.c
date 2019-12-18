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

/* Variables and functions */
 int /*<<< orphan*/  DCD_PIN ; 
 int /*<<< orphan*/  GND_PIN ; 
 int /*<<< orphan*/  PULLDOWN_PIN ; 
 int /*<<< orphan*/  PinDirectionInput ; 
 int /*<<< orphan*/  PinDirectionOutput ; 
 int /*<<< orphan*/  PinLevelLow ; 
 int /*<<< orphan*/  RTS_PIN ; 
 int /*<<< orphan*/  VCC_PIN ; 
 int /*<<< orphan*/  digitalWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pins_init(void) {
 // set pins for pullups, Rts , power &etc. 

    //print ("pins setup\n");
    pinMode(VCC_PIN, PinDirectionOutput);
    digitalWrite(VCC_PIN, PinLevelLow);

#if ( HANDSPRING == 0)

#ifdef CY835
    pinMode(GND_PIN, PinDirectionOutput);
    digitalWrite(GND_PIN, PinLevelLow);

    pinMode(PULLDOWN_PIN, PinDirectionOutput);
    digitalWrite(PULLDOWN_PIN, PinLevelLow);
#endif

    pinMode(DCD_PIN, PinDirectionInput);
    pinMode(RTS_PIN, PinDirectionInput); 
#endif

/* check that the other side isn't powered up. 
    test=digitalRead(DCD_PIN);
    xprintf("b%02X:", test);
    test=digitalRead(RTS_PIN);
    xprintf("%02X\n", test);
*/
 
}
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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  PinLevelHigh ; 
 int /*<<< orphan*/  PinLevelLow ; 
 int /*<<< orphan*/  VCC_PIN ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  digitalWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ disconnect_counter ; 
 scalar_t__ handspring_handshake () ; 
 int /*<<< orphan*/  last_activity ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  timer_read () ; 

uint8_t handspring_reset(void) {
    digitalWrite(VCC_PIN, PinLevelLow);
    _delay_ms(5);
    digitalWrite(VCC_PIN, PinLevelHigh);

    if ( handspring_handshake() ) {
        last_activity = timer_read();
        disconnect_counter=0;
        return 1;
    } else { 
        print("-HSreset");
        return 0;   
    }
}
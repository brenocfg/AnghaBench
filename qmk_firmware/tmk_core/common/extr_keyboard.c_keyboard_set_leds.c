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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug_hex8 (int /*<<< orphan*/ ) ; 
 scalar_t__ debug_keyboard ; 
 int /*<<< orphan*/  led_set (int /*<<< orphan*/ ) ; 

void keyboard_set_leds(uint8_t leds) {
    if (debug_keyboard) {
        debug("keyboard_set_led: ");
        debug_hex8(leds);
        debug("\n");
    }
    led_set(leds);
}
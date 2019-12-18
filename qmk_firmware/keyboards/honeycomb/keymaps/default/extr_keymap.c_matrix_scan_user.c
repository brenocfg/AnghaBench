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
 int /*<<< orphan*/  KC_VOLD ; 
 int /*<<< orphan*/  KC_VOLU ; 
 scalar_t__ encoderValue ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 

void matrix_scan_user(void) {
	/* Leaving some LED stuff in here in comment form so you can see how to use it.
    if (shiftLED || capsLED){
		red_led_on;
    } else {
		red_led_off;
    }
    if (numLED){
		grn_led_on;
    } else {
		grn_led_off;
    }
    if (mouseLED){
		blu_led_on;
    } else {
		blu_led_off;
	}*/
	while (encoderValue < 0){
		tap_code(KC_VOLD);
		encoderValue++;
	}
	while (encoderValue > 0){
		tap_code(KC_VOLU);
		encoderValue--;
	}
}
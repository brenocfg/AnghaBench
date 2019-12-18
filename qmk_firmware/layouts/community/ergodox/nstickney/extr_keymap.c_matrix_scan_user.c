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
 int /*<<< orphan*/  FCTN ; 
 scalar_t__ IS_LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMP ; 
 int /*<<< orphan*/  SYMB ; 
 int /*<<< orphan*/  SYSH ; 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 

void matrix_scan_user (void) {

	if (IS_LAYER_ON(SYMB) || IS_LAYER_ON(SYSH)) {
		ergodox_right_led_1_on();
	} else {
		ergodox_right_led_1_off();
	}

	if (IS_LAYER_ON(NUMP)) {
		ergodox_right_led_2_on();
	} else {
		ergodox_right_led_2_off();
	}

	if (IS_LAYER_ON(FCTN)) {
		ergodox_right_led_3_on();
	} else {
		ergodox_right_led_3_off();
	}

}
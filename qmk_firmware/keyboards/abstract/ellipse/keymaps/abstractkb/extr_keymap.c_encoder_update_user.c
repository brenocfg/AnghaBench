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
 int /*<<< orphan*/  KC_VOLD ; 
 int /*<<< orphan*/  KC_VOLU ; 
 int /*<<< orphan*/  backlight_decrease () ; 
 int /*<<< orphan*/  backlight_increase () ; 
 int /*<<< orphan*/  rgblight_decrease_hue_noeeprom () ; 
 int /*<<< orphan*/  rgblight_increase_hue_noeeprom () ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 

void encoder_update_user(uint8_t index, bool clockwise) {
	if (index == 0) { /* First encoder */
		if (clockwise) {
			tap_code(KC_VOLU);
		} else {
			tap_code(KC_VOLD);
		}
	} else if (index == 1) { /* Second encoder */
		if (clockwise) {
			rgblight_increase_hue_noeeprom();
		} else {
			rgblight_decrease_hue_noeeprom();
		}
	} else if (index == 2) { /* Third encoder */
		if (clockwise) {
			backlight_increase();
		} else {
			backlight_decrease();
		}
	}
}
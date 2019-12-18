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
 int /*<<< orphan*/  KC_M ; 
 int /*<<< orphan*/  KC_O ; 
 int /*<<< orphan*/  KC_P ; 
 int /*<<< orphan*/  KC_R ; 
 int /*<<< orphan*/  rgblight_decrease_hue_noeeprom () ; 
 int /*<<< orphan*/  rgblight_increase_hue_noeeprom () ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 

void encoder_update_user(uint8_t index, bool clockwise) {
	if (index == 0) { /* First encoder */
		if (clockwise) {
			tap_code(KC_O);
		} else {
			tap_code(KC_P);
		}
	} else if (index == 1) { /* Second encoder */
		if (clockwise) {
			rgblight_increase_hue_noeeprom();
		} else {
			rgblight_decrease_hue_noeeprom();
		}
	} else if (index == 2) {
		if (clockwise) {
			tap_code(KC_M);
		} else {
			tap_code(KC_R);
		}
	}
}
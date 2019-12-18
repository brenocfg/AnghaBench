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
 int /*<<< orphan*/  KC_A ; 
 int /*<<< orphan*/  KC_COMM ; 
 int /*<<< orphan*/  KC_D ; 
 int /*<<< orphan*/  KC_DOT ; 
 int /*<<< orphan*/  KC_E ; 
 int /*<<< orphan*/  KC_H ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_N ; 
 int /*<<< orphan*/  KC_Q ; 
 int /*<<< orphan*/  KC_VOLD ; 
 int /*<<< orphan*/  KC_VOLU ; 
 int /*<<< orphan*/  LALT (int /*<<< orphan*/ ) ; 
 int base_mode ; 
 int flight_mode ; 
 int rcs_mode ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 

void encoder_update_user(uint8_t index, bool clockwise) {
    if(base_mode == true) {
        if (index == 0) {
            if (clockwise) {
                // Volume up
                tap_code(KC_VOLU);
            } else {
                // Volume down
                tap_code(KC_VOLD);
            }
        }
        else if (index == 1) {
            if (clockwise) {
                // Time warp faster
                tap_code(KC_DOT);
            } else {
                // Time warp slower
                tap_code(KC_COMM);
            }
        }
    }

    if(rcs_mode == true) {
        if (index == 0) {
            if (clockwise) {
                // RCS Forward
                tap_code(KC_H);
            } else {
                // RCS Backward
                tap_code(KC_N);
            }
        }
        else if (index == 1) {
            if (clockwise) {
                // RCS Rotate Left
                tap_code(KC_Q);
            } else {
                // RCS Rotate Right
                tap_code(KC_E);
            }
        }
    }

    if(flight_mode == true) {
        if (index == 0) {
            if (clockwise) {
                // Throttle up
                tap_code(KC_LSFT);
            } else {
                // Throttle down
                tap_code(KC_LCTL);
            }
        }
        else if (index == 1) {
            if (clockwise) {
                // Trim left
                tap_code16(LALT(KC_A));
            } else {
                // Trim right
                tap_code16(LALT(KC_D));
            }
        }
    }
}
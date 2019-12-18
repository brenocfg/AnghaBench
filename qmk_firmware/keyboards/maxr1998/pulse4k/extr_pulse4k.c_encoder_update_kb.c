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
 int /*<<< orphan*/  encoder_one_update (int) ; 
 int /*<<< orphan*/  encoder_two_update (int) ; 
 scalar_t__ led_adjust_active ; 
 int /*<<< orphan*/  rgblight_decrease_hue () ; 
 int /*<<< orphan*/  rgblight_decrease_val () ; 
 int /*<<< orphan*/  rgblight_increase_hue () ; 
 int /*<<< orphan*/  rgblight_increase_val () ; 

void encoder_update_kb(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (led_adjust_active) {
            if (clockwise) {
                rgblight_increase_val();
            } else {
                rgblight_decrease_val();
            }
        } else encoder_one_update(clockwise);
    } else if (index == 1) {
        if (led_adjust_active) {
            if (clockwise) {
                rgblight_increase_hue();
            } else {
                rgblight_decrease_hue();
            }
        } else encoder_two_update(clockwise);
    }
}
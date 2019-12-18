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
 int /*<<< orphan*/ * RGBLED_SPLIT ; 
 scalar_t__ isLeftHand ; 
 scalar_t__ is_keyboard_left () ; 
 scalar_t__ is_keyboard_master () ; 
 int /*<<< orphan*/  keyboard_master_setup () ; 
 int /*<<< orphan*/  keyboard_slave_setup () ; 
 int /*<<< orphan*/  rgblight_set_clipping_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void keyboard_split_setup(void) {
    isLeftHand = is_keyboard_left();

#if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
    uint8_t num_rgb_leds_split[2] = RGBLED_SPLIT;
    if (isLeftHand) {
        rgblight_set_clipping_range(0, num_rgb_leds_split[0]);
    } else {
        rgblight_set_clipping_range(num_rgb_leds_split[0], num_rgb_leds_split[1]);
    }
#endif

    if (is_keyboard_master()) {
        keyboard_master_setup();
    } else {
        keyboard_slave_setup();
    }
}
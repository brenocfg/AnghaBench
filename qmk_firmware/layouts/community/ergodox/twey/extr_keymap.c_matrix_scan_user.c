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
typedef  unsigned long uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ergodox_board_led_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 
 unsigned long layer_state ; 

void matrix_scan_user(void) {
    __attribute__ ((unused))
    uint32_t layer0 = layer_state & (1UL << 0),
             layer1 = layer_state & (1UL << 1),
             layer2 = layer_state & (1UL << 2),
             layer3 = layer_state & (1UL << 3);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    if (layer1) ergodox_right_led_1_on();
    if (layer2) ergodox_right_led_2_on();
    if (layer3) ergodox_right_led_3_on();
}
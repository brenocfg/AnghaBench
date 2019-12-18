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
 int /*<<< orphan*/  FN ; 
 int /*<<< orphan*/  MOUSE ; 
 int /*<<< orphan*/  NUM ; 
 int /*<<< orphan*/  QWERTY ; 
 int /*<<< orphan*/  default_layer_state ; 
 int /*<<< orphan*/  ergodox_board_led_off () ; 
 scalar_t__ layer_state_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_1_off () ; 
 int /*<<< orphan*/  led_1_on () ; 
 int /*<<< orphan*/  led_2_off () ; 
 int /*<<< orphan*/  led_2_on () ; 
 int /*<<< orphan*/  led_3_off () ; 
 int /*<<< orphan*/  led_3_on () ; 

void matrix_scan_user(void) {

    ergodox_board_led_off();
    led_1_off();
    led_2_off();
    led_3_off();

    if(layer_state_cmp(default_layer_state, QWERTY)) {
        led_3_on();
    }

    if(layer_state_cmp(default_layer_state, FN)) {
        led_2_on();
    }

    if(layer_state_cmp(default_layer_state, NUM)) {
        led_2_on();
        led_3_on();
    }

    if(layer_state_cmp(default_layer_state, MOUSE)) {
        led_1_on();
    }
}
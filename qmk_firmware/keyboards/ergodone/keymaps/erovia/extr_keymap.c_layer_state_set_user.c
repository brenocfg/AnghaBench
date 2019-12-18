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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ CAPS_LED ; 
#define  FN 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_layer_led_set () ; 
 int /*<<< orphan*/  ergodox_board_led_on () ; 
 int /*<<< orphan*/  ergodox_led_all_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 

uint32_t layer_state_set_user(uint32_t state) {
    ergodox_led_all_off();
    switch (biton32(state)) {
      case FN:
          // Red led on Pro Micro for Fn layer
          ergodox_board_led_on();
          break;
    };

    if (CAPS_LED) {
      ergodox_right_led_1_on();
    }

    default_layer_led_set();

    return state;
}
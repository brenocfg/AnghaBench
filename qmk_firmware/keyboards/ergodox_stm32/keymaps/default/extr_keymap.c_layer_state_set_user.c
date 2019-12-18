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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ergodox_board_led_1_off () ; 
 int /*<<< orphan*/  ergodox_board_led_1_on () ; 
 int /*<<< orphan*/  ergodox_board_led_2_off () ; 
 int /*<<< orphan*/  ergodox_board_led_2_on () ; 
 int /*<<< orphan*/  ergodox_board_led_3_off () ; 
 int /*<<< orphan*/  ergodox_board_led_3_on () ; 
 int /*<<< orphan*/  ergodox_led_all_off () ; 

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_led_all_off();
    ergodox_board_led_1_off();
    ergodox_board_led_2_off();
    ergodox_board_led_3_off();
    switch (layer) {
      case 1:
        ergodox_board_led_1_on();
        break;
      case 2:
        ergodox_board_led_2_on();
        break;
      case 3:
        ergodox_board_led_2_on();
        break;
      case 4:
        ergodox_board_led_1_on();
        ergodox_board_led_2_on();
        break;
      case 5:
        ergodox_board_led_1_on();
        ergodox_board_led_3_on();
        break;
      case 6:
        ergodox_board_led_2_on();
        ergodox_board_led_3_on();
        break;
      case 7:
        ergodox_board_led_1_on();
        ergodox_board_led_2_on();
        ergodox_board_led_3_on();
        break;
      default:
        break;
    }
    return state;

}
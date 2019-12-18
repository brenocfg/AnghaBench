#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  rgb_layer_change; } ;

/* Variables and functions */
#define  MDIA 129 
#define  SYMB 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ergodox_board_led_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_blue () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_cyan () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_green () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_orange () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_pink () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_red () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_white () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_yellow () ; 
 TYPE_1__ user_config ; 

uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (biton32(state)) {
    case SYMB:
        ergodox_right_led_1_on();
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_red(); rgblight_mode_noeeprom(1); }
        break;
    case MDIA:
        ergodox_right_led_2_on();
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_green(); rgblight_mode_noeeprom(1); }
        break;
    case 3:
        ergodox_right_led_3_on();
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_blue(); rgblight_mode_noeeprom(1); }
        break;
    case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_orange(); rgblight_mode_noeeprom(1); }
        break;
    case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_yellow(); rgblight_mode_noeeprom(1); }
        break;
    case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_pink(); rgblight_mode_noeeprom(1); }
        break;
    case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_white(); rgblight_mode_noeeprom(1); }
        break;
    default: //  for any other layers, or the default layer
        if (user_config.rgb_layer_change) { rgblight_sethsv_noeeprom_cyan(); rgblight_mode_noeeprom(1); }
        break;
    }
  return state;
}
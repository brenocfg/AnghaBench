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
#define  _APPSWITCH 138 
#define  _FUNCTION 137 
#define  _MACROS 136 
#define  _MOUSE 135 
#define  _NAV 134 
#define  _NUMPAD 133 
#define  _ONESHOT 132 
#define  _QWERTY_KIDS 131 
#define  _STREET_FIGHTER 130 
#define  _SYMBOLS 129 
#define  _TEXTNAV 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ergodox_board_led_off () ; 
 int /*<<< orphan*/  ergodox_board_led_on () ; 
 int /*<<< orphan*/  ergodox_led_all_on () ; 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 
 int /*<<< orphan*/  layer_state ; 

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_on();
    ergodox_led_all_on();

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
   //    _delay_ms(45);

    switch (layer)
    {
    case _SYMBOLS:
      ergodox_right_led_1_on();
      break;
    case _MOUSE:
      ergodox_right_led_2_on();
      break;
    case _NUMPAD:
      ergodox_right_led_3_on();
      break;
    case _NAV:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      break;
    case _MACROS:
      //layer unused right now
      break;
    case _FUNCTION:
      //layer unused right nowex
      break;
    case _APPSWITCH:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case _ONESHOT:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case _TEXTNAV:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      break;
    case _QWERTY_KIDS:
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    case _STREET_FIGHTER:
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
    default:
      break;
    }
}
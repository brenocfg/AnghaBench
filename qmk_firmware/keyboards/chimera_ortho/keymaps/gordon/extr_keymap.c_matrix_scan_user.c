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
#define  _FUNCTION 134 
#define  _MACROS 133 
#define  _MOUSE 132 
#define  _NAV 131 
#define  _NUMPAD 130 
#define  _QWERTY 129 
#define  _SYMBOLS 128 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  set_led_blue ; 
 int /*<<< orphan*/  set_led_green ; 
 int /*<<< orphan*/  set_led_magenta ; 
 int /*<<< orphan*/  set_led_red ; 
 int /*<<< orphan*/  set_led_yellow ; 

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
      case _QWERTY:
        set_led_green;
        break;
      case _MOUSE:
        set_led_yellow;
        break;
      case _NUMPAD:
        set_led_blue;
        break;
      case _SYMBOLS:
        set_led_red;
        break;
      case _NAV:
        set_led_magenta;
        break;
      case _MACROS:
        set_led_green;
        _delay_ms(45);
        set_led_red;
        _delay_ms(45);
        break;
      case _FUNCTION:
        set_led_green;
        _delay_ms(45);
        set_led_blue;
        _delay_ms(45);
        break;
      default:
        set_led_green;
        break;
    }
}
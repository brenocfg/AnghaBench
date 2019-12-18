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
#define  _CAPS 133 
#define  _MACROS 132 
#define  _NAV 131 
#define  _NUMPAD 130 
#define  _QWERTY 129 
#define  _SYMBOLS 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  set_led_blue ; 
 int /*<<< orphan*/  set_led_cyan ; 
 int /*<<< orphan*/  set_led_green ; 
 int /*<<< orphan*/  set_led_magenta ; 
 int /*<<< orphan*/  set_led_red ; 
 int /*<<< orphan*/  set_led_white ; 

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
      case _QWERTY:
          set_led_green;
          break;
        case _CAPS:
      set_led_white;
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
      set_led_cyan;
      break;
       default:
            set_led_green;
            break;
    }
}
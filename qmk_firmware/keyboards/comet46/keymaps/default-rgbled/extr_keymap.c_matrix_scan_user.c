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
#define  _ADJUST 132 
#define  _COLEMAK 131 
#define  _DVORAK 130 
#define  _LOWER 129 
#define  _RAISE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeconfig_read_default_layer () ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  set_led_blue ; 
 int /*<<< orphan*/  set_led_green ; 
 int /*<<< orphan*/  set_led_magenta ; 
 int /*<<< orphan*/  set_led_red ; 
 int /*<<< orphan*/  set_led_white ; 
 int /*<<< orphan*/  set_led_yellow ; 

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  uint8_t default_layer = biton32(eeconfig_read_default_layer());
  switch (layer) {
    case _LOWER:
      set_led_red;
      break;
    case _RAISE:
      set_led_blue;
      break;
    case _ADJUST:
      set_led_magenta;
      break;
    default:
      switch (default_layer) {
        case _COLEMAK:
          set_led_white;
          break;
        case _DVORAK:
          set_led_yellow;
          break;
        default:
          set_led_green;
          break;
      }
      break;
  }
}
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
typedef  unsigned long uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  _ADJUST 130 
 unsigned long _COLEMAK ; 
 unsigned long _DVORAK ; 
#define  _LOWER 129 
#define  _RAISE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 unsigned long eeconfig_read_default_layer () ; 
 scalar_t__ rgb_layer_change ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_set_blue ; 
 int /*<<< orphan*/  rgblight_set_green ; 
 int /*<<< orphan*/  rgblight_set_magenta ; 
 int /*<<< orphan*/  rgblight_set_orange ; 
 int /*<<< orphan*/  rgblight_set_purple ; 
 int /*<<< orphan*/  rgblight_set_teal ; 

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
  uint8_t default_layer = eeconfig_read_default_layer();
  if (rgb_layer_change) {
    switch (biton32(state)) {
    case _RAISE:
      rgblight_set_orange;
      rgblight_mode(5);
      break;
    case _LOWER:
      rgblight_set_teal;
      rgblight_mode(5);
      break;
    case _ADJUST:
      rgblight_set_purple;
      rgblight_mode(23);
      break;
    default:
      if (default_layer & (1UL << _COLEMAK)) {
        rgblight_set_magenta;
      }
      else if (default_layer & (1UL << _DVORAK)) {
        rgblight_set_green;
      }
      else {
        rgblight_set_blue;
      }
      rgblight_mode(1);
      break;
    }
  }
#endif
  return state;
}
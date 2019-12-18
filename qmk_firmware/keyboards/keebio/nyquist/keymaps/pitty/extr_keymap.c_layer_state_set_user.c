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
#define  _GAME 130 
#define  _LOWER 129 
#define  _VIM 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 unsigned long eeconfig_read_default_layer () ; 
 scalar_t__ rgb_layer_change ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_set_green ; 
 int /*<<< orphan*/  rgblight_set_purple ; 

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
  uint8_t default_layer = eeconfig_read_default_layer();
  if (rgb_layer_change) {
    switch (biton32(state)) {
    case _LOWER:
      rgblight_set_purple;
      rgblight_mode(5);
      break;
    case _VIM:
	  rgblight_set_green;
      rgblight_mode(23);
      break;
	case _GAME:
      rgblight_mode(8);
      break;
    default:
      if (default_layer & (1UL << _GAME)) {
      }
      else
      rgblight_mode(14);
      break;
    }
  }
#endif
  return state;
}
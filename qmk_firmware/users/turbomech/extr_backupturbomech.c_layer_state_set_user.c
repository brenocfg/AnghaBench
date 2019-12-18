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
#define  _FUNCTION 129 
#define  _QWERTY 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 unsigned long eeconfig_read_default_layer () ; 
 int /*<<< orphan*/  is_capslocked ; 
 scalar_t__ rgb_layer_change ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_set_blue ; 
 int /*<<< orphan*/  rgblight_set_cyan ; 
 int /*<<< orphan*/  rgblight_set_orange ; 
 int /*<<< orphan*/  rgblight_set_red ; 

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
  uint8_t default_layer = eeconfig_read_default_layer();
  if (rgb_layer_change) {
    switch (biton32(state)) {
    case _FUNCTION:
      rgblight_set_blue;
     rgblight_mode(1);
     break;
    case _QWERTY:

      rgblight_mode(11);
      break;
  // case _MOUS:
    //  rgblight_set_yellow;
    //  rgblight_mode(1);
   //   break;
    //case _MACROS:
      //rgblight_set_orange;
      //is_overwatch ? rgblight_mode(17) : rgblight_mode(18);
      //break;
    //case _MEDIA:
      //rgblight_set_green;
      //rgblight_mode(22);
      //break;
    default:
      if (is_capslocked) {
        rgblight_mode(1);
        rgblight_set_red;
      }
        else { if (default_layer & (1UL << _QWERTY)) {
        rgblight_mode(11);
        }

        else if (default_layer & (1UL << _FUNCTION)) {
         rgblight_set_cyan;
        }
        //else if (default_layer & (1UL << _WORKMAN)) {
        //  rgblight_set_purple;
       // }
        else {
          rgblight_set_orange;
        }
      }
      rgblight_mode(1);
      break;
    }
  }
#endif
  return state;
}
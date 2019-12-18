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
typedef  int /*<<< orphan*/  layer_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  HSV_AZURE ; 
 int /*<<< orphan*/  RGBLIGHT_MODE_STATIC_LIGHT ; 
 int /*<<< orphan*/  RGB_CLEAR ; 
#define  _NAVI 132 
#define  _NUMP 131 
#define  _OVERWATCH 130 
#define  _QWERTY 129 
#define  _SYMB 128 
 int get_highest_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_blue () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_green () ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom_red () ; 

layer_state_t layer_state_set_rgb(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _QWERTY:
      rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv_noeeprom(RGB_CLEAR);
      break;
    case _SYMB:
      rgblight_sethsv_noeeprom_red();
      break;
    case _NUMP:
      rgblight_sethsv_noeeprom_green();
      break;
    case _OVERWATCH:
      rgblight_sethsv_noeeprom_blue();
      // TODO set up animated rainbow swirl with overwatch colors.
      // rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
      // rgblight_effect_breathing(&animation_status);
      // rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
      break;
    case _NAVI:
      rgblight_sethsv_noeeprom(HSV_AZURE);
      break;
    default: //  for any other layers, or the default layer
      break;
    }
  return state;
}
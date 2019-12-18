#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_7__ {int mode; int /*<<< orphan*/  val; int /*<<< orphan*/  sat; int /*<<< orphan*/  hue; } ;

/* Variables and functions */
#define  ADJUST 133 
#define  COLEMAK 132 
#define  DVORAK 131 
 int /*<<< orphan*/  IS_LAYER_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_LAYER_ON (int /*<<< orphan*/ ) ; 
#define  LOWER 130 
#define  QWERTY 129 
#define  RAISE 128 
 int /*<<< orphan*/  RGB_current_hue ; 
 int RGB_current_mode ; 
 int /*<<< orphan*/  _ADJUST ; 
 unsigned long _COLEMAK ; 
 unsigned long _DVORAK ; 
 int /*<<< orphan*/  _LOWER ; 
 unsigned long _QWERTY ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 TYPE_3__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {

        if (IS_LAYER_OFF(_RAISE) && IS_LAYER_OFF(_ADJUST)) {
          // Save current RGB info
          RGB_current_mode = rgblight_config.mode;
          RGB_current_hue = rgblight_config.hue;

          // Set RGB to Blue
          rgblight_mode(1);
          rgblight_setrgb(0, 0, 255);
        }

        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (IS_LAYER_ON(_ADJUST)){
          // Set RGB to cyan
          rgblight_setrgb(0, 255, 255);
        }
      } else {

        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (IS_LAYER_OFF(_RAISE) && IS_LAYER_OFF(_ADJUST)) {
          // Reset RGB
          rgblight_mode(RGB_current_mode);
          rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
        } else if (IS_LAYER_ON(_RAISE)){
          // Set RGB to Red
          rgblight_setrgb(0, 255, 0);
        }
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {

        if (IS_LAYER_OFF(_LOWER) && IS_LAYER_OFF(_ADJUST)) {
          // Save current RGB info
          RGB_current_mode = rgblight_config.mode;
          RGB_current_hue = rgblight_config.hue;

          // Set RGB to Green
          rgblight_mode(1);
          rgblight_setrgb(0, 255, 0);
        }

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (IS_LAYER_ON(_ADJUST)){
          // Set RGB to cyan
          rgblight_setrgb(0, 255, 255);
        }
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (IS_LAYER_OFF(_LOWER) && IS_LAYER_OFF(_ADJUST)) {
          // Reset RGB
          rgblight_mode(RGB_current_mode);
          rgblight_sethsv(RGB_current_hue, rgblight_config.sat, rgblight_config.val);
        } else if (IS_LAYER_ON(_LOWER)){
          // Set RGB to Blue
          rgblight_setrgb(0, 0, 255);
        }
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
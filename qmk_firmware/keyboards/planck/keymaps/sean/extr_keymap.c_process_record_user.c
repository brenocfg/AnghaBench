#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  BACKLIT 138 
#define  BACKTOG 137 
#define  COPY 136 
#define  CUT 135 
 int /*<<< orphan*/  DOWN (int /*<<< orphan*/ ) ; 
#define  DVRK 134 
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  KC_C ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int /*<<< orphan*/  KC_V ; 
 int /*<<< orphan*/  KC_X ; 
#define  LOWER 133 
 int MACRODOWN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PASTE 132 
#define  RAISE 131 
#define  SDRK 130 
#define  SLWER 129 
#define  SRAIS 128 
 int /*<<< orphan*/  TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ADJUST ; 
 unsigned long _DVRK ; 
 unsigned long _LOWER ; 
 unsigned long _RAISE ; 
 unsigned long _SDRK ; 
 unsigned long _SLWER ; 
 unsigned long _SRAIS ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  backlight_toggle () ; 
 int /*<<< orphan*/  layer_off (unsigned long) ; 
 int /*<<< orphan*/  layer_on (unsigned long) ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVRK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVRK);
        layer_on(_DVRK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case SDRK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_SDRK);
        layer_on(_SDRK);
      }
      return false;
      break;
    case SLWER:
      if (record->event.pressed) {
        layer_on(_SLWER);
        update_tri_layer(_SLWER, _SRAIS, _ADJUST);
      } else {
        layer_off(_SLWER);
        update_tri_layer(_SLWER, _SRAIS, _ADJUST);
      }
      return false;
      break;
    case SRAIS:
      if (record->event.pressed) {
        layer_on(_SRAIS);
        update_tri_layer(_SLWER, _SRAIS, _ADJUST);
      } else {
        layer_off(_SRAIS);
        update_tri_layer(_SLWER, _SRAIS, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case BACKTOG:
      if (record->event.pressed) {
        #ifdef BACKLIGHT_ENABLE
          backlight_toggle();
        #endif
      }
      return false;
      break;
    case CUT: //cut macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_X), UP(KC_LCTL), END );
    case COPY: // copy macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_C), UP(KC_LCTL), END );
    case PASTE: // paste macro
	    return MACRODOWN( DOWN(KC_LCTL), TYPE(KC_V), UP(KC_LCTL), END );
  }
  return true;
}
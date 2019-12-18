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
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  COLEMAK 134 
#define  DESTINY 133 
#define  DVORAK 132 
 int MOD_MASK_SHIFT ; 
#define  QWERTY 131 
#define  RGBRST 130 
#define  RGB_MENU 129 
#define  RGB_TOG 128 
 int /*<<< orphan*/  _COLEMAK ; 
 int /*<<< orphan*/  _DESTINY ; 
 int /*<<< orphan*/  _DVORAK ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  eeconfig_update_rgb_matrix_default () ; 
 int /*<<< orphan*/  eeconfig_update_rgblight_default () ; 
 int get_mods () ; 
 int rgb_encoder_state ; 
 int /*<<< orphan*/  rgb_matrix_increase_flags () ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
   switch (keycode) {
    case DVORAK:
        set_single_persistent_default_layer(_DVORAK);
      return false;
    case DESTINY:
        set_single_persistent_default_layer(_DESTINY);
      return false;
    case QWERTY:
        set_single_persistent_default_layer(_QWERTY);
      return false;
    case COLEMAK:
        set_single_persistent_default_layer(_COLEMAK);
      return false;
    case RGBRST:
#if defined(RGBLIGHT_ENABLE)
        eeconfig_update_rgblight_default();
        rgblight_enable();
#elif defined(RGB_MATRIX_ENABLE)
        eeconfig_update_rgb_matrix_default();
#endif
      return false;
#if defined(RGB_MATRIX_ENABLE) && defined(KEYBOARD_rgbkb_sol_rev2)
    case RGB_TOG:
      if (record->event.pressed) {
        rgb_matrix_increase_flags();
      }
      return false;
#endif
    case RGB_MENU:
#ifdef RGB_OLED_MENU
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          rgb_encoder_state = (rgb_encoder_state - 1);
          if (rgb_encoder_state > 5) {
            rgb_encoder_state = 5;
          }
        } else {
          rgb_encoder_state = (rgb_encoder_state + 1) % 6;
        }
      }
#endif
      return false;
    }
  }
  return true;
}
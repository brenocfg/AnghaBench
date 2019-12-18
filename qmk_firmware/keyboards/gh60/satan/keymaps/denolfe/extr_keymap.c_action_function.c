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
typedef  int uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_ESC ; 
 int /*<<< orphan*/  KC_GRV ; 
 int MODS_CTRL_MASK ; 
#define  RGBLED_DECREASE_HUE 136 
#define  RGBLED_DECREASE_SAT 135 
#define  RGBLED_DECREASE_VAL 134 
#define  RGBLED_INCREASE_HUE 133 
#define  RGBLED_INCREASE_SAT 132 
#define  RGBLED_INCREASE_VAL 131 
#define  RGBLED_STEP_MODE 130 
#define  RGBLED_TOGGLE 129 
#define  SHIFT_ESC 128 
 int /*<<< orphan*/  add_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_key (int /*<<< orphan*/ ) ; 
 int get_mods () ; 
 int /*<<< orphan*/  rgblight_decrease_hue () ; 
 int /*<<< orphan*/  rgblight_decrease_sat () ; 
 int /*<<< orphan*/  rgblight_decrease_val () ; 
 int /*<<< orphan*/  rgblight_increase_hue () ; 
 int /*<<< orphan*/  rgblight_increase_sat () ; 
 int /*<<< orphan*/  rgblight_increase_val () ; 
 int /*<<< orphan*/  rgblight_step () ; 
 int /*<<< orphan*/  rgblight_toggle () ; 
 int /*<<< orphan*/  send_keyboard_report () ; 

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
    //led operations
    #ifdef RGBLIGHT_ENABLE
    case RGBLED_TOGGLE:
      if (record->event.pressed) {
        rgblight_toggle();
      }
      break;
    case RGBLED_INCREASE_HUE:
      if (record->event.pressed) {
        rgblight_increase_hue();
      }
      break;
    case RGBLED_DECREASE_HUE:
      if (record->event.pressed) {
        rgblight_decrease_hue();
      }
      break;
    case RGBLED_INCREASE_SAT:
      if (record->event.pressed) {
        rgblight_increase_sat();
      }
      break;
    case RGBLED_DECREASE_SAT:
      if (record->event.pressed) {
        rgblight_decrease_sat();
      }
      break;
    case RGBLED_INCREASE_VAL:
      if (record->event.pressed) {
        rgblight_increase_val();
      }
      break;
    case RGBLED_DECREASE_VAL:
      if (record->event.pressed) {
        rgblight_decrease_val();
      }
      break;
    case RGBLED_STEP_MODE:
      if (record->event.pressed) {
        rgblight_step();
      }
      break;
    #endif
  }
}
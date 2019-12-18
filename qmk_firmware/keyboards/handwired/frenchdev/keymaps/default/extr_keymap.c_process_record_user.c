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
 int /*<<< orphan*/  BP_C ; 
 int /*<<< orphan*/  BP_F ; 
 int /*<<< orphan*/  BP_V ; 
 int /*<<< orphan*/  BP_X ; 
 int /*<<< orphan*/  BP_Z ; 
 int /*<<< orphan*/  C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KC_BTN1 ; 
 int /*<<< orphan*/  KC_BTN2 ; 
 int /*<<< orphan*/  KC_INS ; 
 int /*<<< orphan*/  KC_SLCK ; 
 int /*<<< orphan*/  KEY_DELAY ; 
#define  L2INS 140 
#define  L2LOC 139 
#define  M_CP 138 
#define  M_CUT 137 
#define  M_L1E 136 
#define  M_LP 135 
#define  M_PS 134 
#define  M_RP 133 
#define  M_SE 132 
#define  M_SF 131 
#define  M_SFS 130 
#define  M_SFU 129 
#define  M_UN 128 
 int /*<<< orphan*/  PEDAL_DELAY ; 
 int /*<<< orphan*/  hold_shift () ; 
 int /*<<< orphan*/  key_timer_1 ; 
 int /*<<< orphan*/  key_timer_2 ; 
 int /*<<< orphan*/  key_timer_left_pedal ; 
 int /*<<< orphan*/  key_timer_right_pedal ; 
 int /*<<< orphan*/  key_timer_shift ; 
 int l2_locked ; 
 int /*<<< orphan*/  layer_off (int) ; 
 int /*<<< orphan*/  layer_on (int) ; 
 int /*<<< orphan*/  press_enter () ; 
 int /*<<< orphan*/  press_space () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_shift () ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case M_LP: //left pedal
      if (record->event.pressed) {
        layer_on(1);
        register_code (KC_SLCK);
        key_timer_left_pedal = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_left_pedal) < KEY_DELAY) {
           tap_code (KC_BTN2);
        }
        unregister_code (KC_SLCK);
        layer_off(1);
      }
      break;
    case M_RP: //right pedal
      if (record->event.pressed) {
        layer_on(2);
        key_timer_right_pedal = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_right_pedal) < PEDAL_DELAY) {
           tap_code (KC_BTN1);
        }
        layer_off(2);
      }
      break;
    case M_SF: // shift, using macro to keep track of shift state and avoid inserting nbsp by mistake
      if (record->event.pressed) {
        hold_shift();
      } else {
        release_shift();
      }
      break;
    case M_SFS: // shift when held, space when tapped
      if (record->event.pressed) {
        hold_shift();
        key_timer_shift = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_shift) < KEY_DELAY) {
          press_space();
        }
        release_shift();
      }
      break;
    case M_SFU: // shift when held, _ when tapped
      if (record->event.pressed) {
        hold_shift();
        key_timer_shift = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_shift) < KEY_DELAY) {
          press_space();
        }
        release_shift();
      }
      break;
    case M_L1E: // L1 when held, space when tapped
      if (record->event.pressed) {
        layer_on(1);
        key_timer_1 = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_1) < KEY_DELAY) {
          press_enter();
        }
        layer_off(1);
      }
      break;
    case L2INS: //activate layer 2, if released before 100ms trigger INS. basicaly equivalent to LT(2, KC_INS) but without delay for activation of layer 2
      if (record->event.pressed) {
        layer_on(2);
        key_timer_2 = timer_read(); // if the key is being pressed, we start the timer.
      } else {
        if (timer_elapsed(key_timer_2) < KEY_DELAY) {
           tap_code (KC_INS);
        }
        l2_locked = 0;
        layer_off(2);
      }
      break;
    case L2LOC: //lock L2
      if (record->event.pressed) {
        key_timer_2 = timer_read(); // if the key is being pressed, we start the timer.
        layer_on(2);
      } else {
        if (timer_elapsed(key_timer_2) < KEY_DELAY && l2_locked == 0) {
          l2_locked = 1;
          layer_on(2);
        } else {
          l2_locked = 0;
          layer_off(2);
        }
      }
      break;
    case M_UN: // undo
      if (record->event.pressed) {
        tap_code16(C(BP_Z));
      }
      break;
    case M_CUT: // cut
      if (record->event.pressed) {
        tap_code16(C(BP_X));
      }
      break;
    case M_CP: // copy
      if (record->event.pressed) {
        tap_code16(C(BP_C));
      }
      break;
    case M_PS: // paste
      if (record->event.pressed) {
        tap_code16(C(BP_V));
      }
      break;
    case M_SE: // search
      if (record->event.pressed) {
        tap_code16(C(BP_F));
      }
      break;
  }
  return true;
}
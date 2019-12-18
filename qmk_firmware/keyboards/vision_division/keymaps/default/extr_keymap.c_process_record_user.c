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
struct TYPE_6__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {int count; } ;
struct TYPE_7__ {TYPE_2__ event; TYPE_1__ tap; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_C ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_X ; 
 int /*<<< orphan*/  LAYER_ADJUST ; 
 int /*<<< orphan*/  LAYER_LOWER ; 
 int /*<<< orphan*/  LAYER_MOUSE ; 
 int /*<<< orphan*/  LAYER_UPPER ; 
#define  M_CP_CT 138 
#define  M_LOWER 137 
#define  M_MOUSE 136 
#define  M_UPPER 135 
 int /*<<< orphan*/  TEMPO_DEFAULT ; 
 int /*<<< orphan*/  TIMBRE_12 ; 
 int /*<<< orphan*/  TIMBRE_25 ; 
 int /*<<< orphan*/  TIMBRE_50 ; 
 int /*<<< orphan*/  TIMBRE_75 ; 
 int /*<<< orphan*/  TIMBRE_DEFAULT ; 
#define  TIMBR_1 134 
#define  TIMBR_2 133 
#define  TIMBR_3 132 
#define  TIMBR_4 131 
#define  TMPO_DF 130 
#define  TMPO_DN 129 
#define  TMPO_UP 128 
 int /*<<< orphan*/  breathing_period_set (int) ; 
 int /*<<< orphan*/  breathing_pulse () ; 
 int /*<<< orphan*/  decrease_tempo (int) ; 
 int /*<<< orphan*/  increase_tempo (int) ; 
 int /*<<< orphan*/  layer_invert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tempo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_timbre (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case M_CP_CT:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            if (record->tap.count == 1) {
                register_code(KC_C);
                unregister_code(KC_C);
            } else if (record->tap.count == 2) {
                register_code(KC_X);
                unregister_code(KC_X);
            }
            unregister_code(KC_LCTL);
        }
        return false;

  case M_UPPER:
    if (record->event.pressed) {
      layer_on(LAYER_UPPER);
      breathing_period_set(2);
      breathing_pulse();
      update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
    } else {
      layer_off(LAYER_UPPER);
      update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
    }
    return false;

  case M_LOWER:
    if (record->event.pressed) {
      layer_on(LAYER_LOWER);
      breathing_period_set(2);
      breathing_pulse();
      update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
    } else {
      layer_off(LAYER_LOWER);
      update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
    }
    return false;

#ifdef MOUSEKEY_ENABLE
  case M_MOUSE:
    if (record->event.pressed) {
      layer_invert(LAYER_MOUSE);
    }
    return false;
#endif /* MOUSEKEY_ENABLE */

#ifdef AUDIO_ENABLE
  case TIMBR_1:
    if (record->event.pressed) set_timbre(TIMBRE_12);
    return false;
  case TIMBR_2:
    if (record->event.pressed) set_timbre(TIMBRE_25);
    return false;
  case TIMBR_3:
    if (record->event.pressed) set_timbre(TIMBRE_50);
    return false;
  case TIMBR_4:
    if (record->event.pressed) set_timbre(TIMBRE_75);
    return false;
  case TMPO_UP:
    if (record->event.pressed) increase_tempo(10);
    return false;
  case TMPO_DN:
    if (record->event.pressed) decrease_tempo(10);
    return false;
  case TMPO_DF:
    if (record->event.pressed) {
      set_timbre(TIMBRE_DEFAULT);
      set_tempo(TEMPO_DEFAULT);
    }
    return false;
#endif /* AUDIO_ENABLE */

  default:
    return true;
  }
  return true;
}
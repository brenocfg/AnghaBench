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
#define  ADJUST 136 
#define  LOWER 135 
#define  QWERTY 134 
#define  RAISE 133 
#define  SOLENOID_BUZZ_OFF 132 
#define  SOLENOID_BUZZ_ON 131 
#define  SOLENOID_DWELL_MINUS 130 
#define  SOLENOID_DWELL_PLUS 129 
#define  SOLENOID_TOG 128 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solenoid_buzz_off () ; 
 int /*<<< orphan*/  solenoid_buzz_on () ; 
 int /*<<< orphan*/  solenoid_dwell_minus () ; 
 int /*<<< orphan*/  solenoid_dwell_plus () ; 
 int /*<<< orphan*/  solenoid_fire () ; 
 int /*<<< orphan*/  solenoid_toggle () ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef SOLENOID_ENABLE
    if (record->event.pressed) {
      solenoid_fire();
    }
  #endif
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
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
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_ADJUST);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case SOLENOID_TOG:
      #ifdef SOLENOID_ENABLE
        if (record->event.pressed) {
          solenoid_toggle();
        }
      #endif
      break;
    case SOLENOID_DWELL_MINUS:
      #ifdef SOLENOID_ENABLE
        if (record->event.pressed) {
          solenoid_dwell_minus();
        }
      #endif
      break;
    case SOLENOID_DWELL_PLUS:
      #ifdef SOLENOID_ENABLE
        if (record->event.pressed) {
          solenoid_dwell_plus();
        }
        #endif
      break;
    case SOLENOID_BUZZ_ON:
      #ifdef SOLENOID_ENABLE
        if (record->event.pressed) {
          solenoid_buzz_on();
        }
      #endif
      break;
    case SOLENOID_BUZZ_OFF:
      #ifdef SOLENOID_ENABLE
        if (record->event.pressed) {
          solenoid_buzz_off();
        }
      #endif
      break;
  }
  return true;
}
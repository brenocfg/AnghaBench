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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_6__ {int /*<<< orphan*/  count; int /*<<< orphan*/  interrupted; } ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_7__ {TYPE_2__ tap; TYPE_1__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  KC_GRV ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_RCTL ; 
 int /*<<< orphan*/  LCTL ; 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    case 0:
      if (record->event.pressed) {
        if (record->tap.count) {
          if (record->tap.interrupted) {
            record->tap.count = 0;
            // hold press action
            register_code(KC_LCTL);
          } else {
            // tap press action
            return MACRO( D(LCTL), T(A), U(LCTL), END  );
          }
        } else {
          // hold press action
          register_code(KC_LCTL);
        }
      } else {
        if (record->tap.count) {
          // tap release action
        } else {
          // hold release action
          unregister_code(KC_LCTL);
        }
        record->tap.count = 0;
      }
      break;
    case 1:
      if (record->event.pressed) {
        if (record->tap.count) {
          if (record->tap.interrupted) {
            record->tap.count = 0;
            // hold press action
            register_code(KC_RCTL);
          } else {
            // tap press action
            return MACRO( DOWN(KC_RCTL), TYPE(KC_GRV), UP(KC_RCTL), END  );
          }
        } else {
          // hold press action
          register_code(KC_RCTL);
        }
      } else {
        if (record->tap.count) {
          // tap release action
        } else {
          // hold release action
          unregister_code(KC_RCTL);
        }
        record->tap.count = 0;
      }
      break;
  }
  return MACRO_NONE;
}
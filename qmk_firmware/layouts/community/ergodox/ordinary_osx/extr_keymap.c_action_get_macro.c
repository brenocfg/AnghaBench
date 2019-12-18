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
struct TYPE_6__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {int /*<<< orphan*/  interrupted; int /*<<< orphan*/  count; } ;
struct TYPE_7__ {TYPE_2__ event; TYPE_1__ tap; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int COMM ; 
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int DOT ; 
#define  DeRef 141 
 int /*<<< orphan*/  END ; 
 int EQL ; 
#define  GrtEq 140 
 int /*<<< orphan*/  I (int) ; 
 int /*<<< orphan*/  KC_BSLS ; 
 int /*<<< orphan*/  KC_EQL ; 
 int /*<<< orphan*/  KC_GRV ; 
 int /*<<< orphan*/  KC_MS_DOWN ; 
 int /*<<< orphan*/  KC_MS_LEFT ; 
 int /*<<< orphan*/  KC_MS_RIGHT ; 
 int /*<<< orphan*/  KC_MS_UP ; 
 int /*<<< orphan*/  KC_QUOT ; 
 int /*<<< orphan*/  KC_TAB ; 
#define  LMdia 139 
 int /*<<< orphan*/  LSFT ; 
#define  LSpec 138 
#define  LSymb 137 
#define  LesEq 136 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  MDIA ; 
#define  MDL 135 
#define  MDR 134 
 int MINS ; 
#define  MUL 133 
#define  MUR 132 
#define  NotEq 131 
#define  RMdia 130 
#define  RSpec 129 
#define  RSymb 128 
 int /*<<< orphan*/  SPEC ; 
 int /*<<< orphan*/  SYMB ; 
 int /*<<< orphan*/  T (int) ; 
 int /*<<< orphan*/  U (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int mdia_lock ; 
 int mdia_shift ; 
 int /*<<< orphan*/  mousekey_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousekey_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousekey_send () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int spec_shift ; 
 int symb_lock ; 
 int symb_shift ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        // There are two shift keys for each layer so we increment a layer_shift var when one
        // is pressed and decrement when one is released. The shift counts are bound between 0 and 2
        // only because sometimes rapid pressing led to irregular events; this way the states
        // are self healing during use.

        case LSymb:                                               //
        if (record->event.pressed) {                              // when the LSymb button is pressed
            if(++symb_shift > 2) symb_shift = 2;                  // increment the symb shift count, max two
            if(spec_shift) symb_lock = !symb_lock;                // if the Special layer is on, toggle the shift lock
            layer_on(SYMB);                                       // in any case, turn on the Symbols layer
        } else {                                                  // when the LSymb button is released
            if(--symb_shift < 0) symb_shift = 0;                  // decrement the shift count, minimum zero
            if((!symb_shift) && (!symb_lock)) layer_off(SYMB);    // if both shifts are released and the lock is off, turn off the Symbols layer
        }
        break;

        case LMdia:
        if (record->event.pressed) {
           if (record->tap.count && (!mdia_shift) && (!mdia_lock) && (!spec_shift)) {
                register_code(KC_TAB);
            } else {
                if(spec_shift) mdia_lock = !mdia_lock;
                if(++mdia_shift > 2) mdia_shift = 2;
                layer_on(MDIA);
            }
        } else {
            if(record->tap.count && (!mdia_shift) && (!mdia_lock) && (!spec_shift)) {
                unregister_code(KC_TAB);
            } else {
                if(--mdia_shift < 0) mdia_shift = 0;
                if((!mdia_shift) && (!mdia_lock)) layer_off(MDIA);
            }
        }
        break;

        case LSpec:
        if (record->event.pressed) {                                     // when the LSpec button is pressed
            if(symb_shift) symb_lock = !symb_lock;                       // if another layer button is engaged, then
            else if(mdia_shift) mdia_lock = !mdia_lock;                  // lock that layer, be it caps or symb or mdia
            else if (record->tap.count && !record->tap.interrupted && (!spec_shift)) {
                register_code(KC_GRV);                                   // otherwise, if it's an uninterrupted tap, emit a char
            } else {
                if(++spec_shift > 2) spec_shift = 2;
                layer_on(SPEC);                                          // otherwise, turn on the Special layer
            }
        } else {
            if(record->tap.count && !record->tap.interrupted && (!spec_shift)) {
                unregister_code(KC_GRV);
            } else {
                if(--spec_shift < 0) spec_shift = 0;
                if(!spec_shift) layer_off(SPEC);
            }
        }
        break;

        case RSymb:
        if (record->event.pressed) {
            if (record->tap.count && (!symb_shift) && (!symb_lock) && (!spec_shift)) {
                register_code(KC_QUOT);
            } else {
                if(++symb_shift > 2) symb_shift = 2;
                if(spec_shift) symb_lock = !symb_lock;
                layer_on(SYMB);
            }
        } else {
            if(record->tap.count && (!symb_shift) && (!symb_lock) && (!spec_shift)) {
                unregister_code(KC_QUOT);
            } else {
                if(--symb_shift < 0) symb_shift = 0;
                if((!symb_shift) && (!symb_lock)) layer_off(SYMB);
            }
        }
        break;

        case RMdia:
        if (record->event.pressed) {
            if (record->tap.count && (!mdia_shift) && (!mdia_lock) && (!spec_shift)) {
                register_code(KC_BSLS);
            } else {
                if(++mdia_shift > 2) mdia_shift = 2;
                if(spec_shift) mdia_lock = !mdia_lock;
                layer_on(MDIA);
            }
        } else {
            if(record->tap.count && (!mdia_shift) && (!mdia_lock) && (!spec_shift)) {
                unregister_code(KC_BSLS);
            } else {
                if(--mdia_shift < 0) mdia_shift = 0;
                if((!mdia_shift) && (!mdia_lock)) layer_off(MDIA);
            }
        }
        break;

        case RSpec:
        if (record->event.pressed) {
            if(symb_shift) symb_lock = !symb_lock;
            else if(mdia_shift) mdia_lock = !mdia_lock;
            else if (record->tap.count && !record->tap.interrupted && (!spec_shift)) {
                register_code(KC_EQL);
            } else {
                if(++spec_shift > 2) spec_shift = 2;
                layer_on(SPEC);
            }
        } else {
            if(record->tap.count && !record->tap.interrupted && (!spec_shift)) {
                unregister_code(KC_EQL);
            } else {
                if(--spec_shift < 0) spec_shift = 0;
                if(!spec_shift) layer_off(SPEC);
            }
        }
        break;

        case NotEq:
        if (record->event.pressed) {
            return MACRO( I(10), D(LSFT), T(1), U(LSFT), T(EQL), END  ); // !=
        }
        break;

        case GrtEq:
        if (record->event.pressed) {
            return MACRO( I(10), D(LSFT), T(COMM), U(LSFT), T(EQL), END  ); // <=
        }
        break;

        case LesEq:
        if (record->event.pressed) {
            return MACRO( I(10), D(LSFT), T(DOT), U(LSFT), T(EQL), END  ); // >=
        }
        break;

        case DeRef:
        if (record->event.pressed) {
            return MACRO( I(10), T(MINS), D(LSFT), T(DOT), U(LSFT), END  ); // ->
        }
        break;

        // mouse diagonals

        case MUL: // mouse up left
        if (record->event.pressed) {
            mousekey_on(KC_MS_UP);
            mousekey_on(KC_MS_LEFT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_UP);
            mousekey_off(KC_MS_LEFT);
            mousekey_send();
        }
        break;

        case MUR: // mouse up right
        if (record->event.pressed) {
            mousekey_on(KC_MS_UP);
            mousekey_on(KC_MS_RIGHT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_UP);
            mousekey_off(KC_MS_RIGHT);
            mousekey_send();
        }
        break;

        case MDL: // mouse down left
        if (record->event.pressed) {
            mousekey_on(KC_MS_DOWN);
            mousekey_on(KC_MS_LEFT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_DOWN);
            mousekey_off(KC_MS_LEFT);
            mousekey_send();
        }
        break;

        case MDR: // mouse down right
        if (record->event.pressed) {
            mousekey_on(KC_MS_DOWN);
            mousekey_on(KC_MS_RIGHT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_DOWN);
            mousekey_off(KC_MS_RIGHT);
            mousekey_send();
        }
        break;

        default:
            // none
            break;
    }

    return MACRO_NONE;
}
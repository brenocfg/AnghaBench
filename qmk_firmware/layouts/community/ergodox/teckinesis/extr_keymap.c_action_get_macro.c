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
 int /*<<< orphan*/  KC_BSLS ; 
 int /*<<< orphan*/  KC_CAPS ; 
 int /*<<< orphan*/  KC_EQL ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_MINS ; 
 int /*<<< orphan*/  KC_MS_DOWN ; 
 int /*<<< orphan*/  KC_MS_LEFT ; 
 int /*<<< orphan*/  KC_MS_RIGHT ; 
 int /*<<< orphan*/  KC_MS_UP ; 
 int /*<<< orphan*/  KC_QUOT ; 
 int /*<<< orphan*/  KC_TAB ; 
#define  LCaps 139 
#define  LMdia 138 
#define  LSpec 137 
#define  LSymb 136 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  MDIA ; 
#define  MDL 135 
#define  MDR 134 
#define  MUL 133 
#define  MUR 132 
#define  RCaps 131 
#define  RMdia 130 
#define  RSpec 129 
#define  RSymb 128 
 int /*<<< orphan*/  SPEC ; 
 int /*<<< orphan*/  SYMB ; 
 int caps_shift ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int mdia_lock ; 
 int mdia_shift ; 
 int /*<<< orphan*/  mousekey_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousekey_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousekey_send () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int symb_lock ; 
 int symb_shift ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        // There are two shift keys for each layer so we increment a layer_shift var when one
        // is pressed and decrement when one is released. If both are pressed at the same time
        // then the layer is locked (or unlocked). The shift counts are bound between 0 and 2
        // only because sometimes rapid pressing led to irregular events; this way the states
        // are self healing during use.

        case LCaps: // both caps-shift keys trigger Left Shift
        case RCaps: // so they don't interfere with the magic combo
        if (record->event.pressed && !record->tap.count) {
            if(++caps_shift > 2) caps_shift = 2;
            if(caps_shift == 2)  {
                register_code(KC_CAPS);
                unregister_code(KC_CAPS);
            } else if(caps_shift == 1) {
                register_code(KC_LSFT);
            }
        } else {
            if(--caps_shift < 0) caps_shift = 0;
            if(caps_shift == 0) unregister_code(KC_LSFT);
        }
        break;

        case LSymb:
        if (record->event.pressed) {
            if(++symb_shift > 2) symb_shift = 2;
            if(symb_shift == 2)  {
                symb_lock = !symb_lock;
            } else if(symb_shift == 1) {
                layer_on(SYMB);
            }
        } else {
            if(--symb_shift < 0) symb_shift = 0;
            if((symb_shift == 0) && (!symb_lock)) layer_off(SYMB);
        }
        break;

        case LMdia:
        if (record->event.pressed) {
            if (record->tap.count && (!mdia_shift) && (!mdia_lock)) {
                register_code(KC_TAB);
            } else {
                if(++mdia_shift > 2) mdia_shift = 2;
                if(mdia_shift == 2)  {
                    mdia_lock = !mdia_lock;
                } else if(mdia_shift == 1) {
                    layer_on(MDIA);
                }
            }
        } else {
            if(record->tap.count && (!mdia_shift) && (!mdia_lock)) {
                unregister_code(KC_TAB);
            } else {
                if(--mdia_shift < 0) mdia_shift = 0;
                if((!mdia_shift) && (!mdia_lock)) layer_off(MDIA);
            }
        }
        break;

        case LSpec:
        if (record->event.pressed) {
            if (record->tap.count && !record->tap.interrupted) {
                register_code(KC_EQL);
            } else {
                layer_on(SPEC);
            }
        } else {
            if(record->tap.count && !record->tap.interrupted) {
                unregister_code(KC_EQL);
            } else {
                layer_off(SPEC);
            }
        }
        break;

        case RSymb:
        if (record->event.pressed) {
            if (record->tap.count && (!symb_shift) && (!symb_lock)) {
                register_code(KC_QUOT);
            } else {
                if(++symb_shift > 2) symb_shift = 2;
                if(symb_shift == 2)  {
                    symb_lock = !symb_lock;
                } else if(symb_shift == 1) {
                    layer_on(SYMB);
                }
            }
        } else {
            if(record->tap.count && symb_shift == 0) {
                unregister_code(KC_QUOT);
            } else {
                if(--symb_shift < 0) symb_shift = 0;
                if((!symb_shift) && (!symb_lock)) layer_off(SYMB);
            }
        }
        break;

        case RMdia:
        if (record->event.pressed) {
            if (record->tap.count && (!mdia_shift) && (!mdia_lock)) {
                register_code(KC_BSLS);
            } else {
                if(++mdia_shift > 2) mdia_shift = 2;
                if(mdia_shift == 2)  {
                    mdia_lock = !mdia_lock;
                } else if(mdia_shift == 1) {
                    layer_on(MDIA);
                }
            }
        } else {
            if(record->tap.count && (!mdia_shift) && (!mdia_lock)) {
                unregister_code(KC_BSLS);
            } else {
                if(--mdia_shift < 0) mdia_shift = 0;
                if((!mdia_shift) && (!mdia_lock)) layer_off(MDIA);
            }
        }
        break;

        case RSpec:
        if (record->event.pressed) {
            if (record->tap.count && !record->tap.interrupted) {
                register_code(KC_MINS);
            } else {
                layer_on(SPEC);
            }
        } else {
            if(record->tap.count && !record->tap.interrupted) {
                unregister_code(KC_MINS);
            } else {
                layer_off(SPEC);
            }
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
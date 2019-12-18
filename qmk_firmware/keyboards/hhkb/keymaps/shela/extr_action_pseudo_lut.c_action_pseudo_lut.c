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
typedef  int uint16_t ;
struct TYPE_5__ {scalar_t__ pressed; int /*<<< orphan*/  key; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_7__ {int mods; } ;

/* Variables and functions */
 scalar_t__ IS_COMMAND () ; 
 scalar_t__ IS_LSFT (int) ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int QK_LSFT ; 
 int /*<<< orphan*/  add_mods (int) ; 
 int /*<<< orphan*/  add_shift_bit (int) ; 
 int /*<<< orphan*/  add_weak_mods (int) ; 
 int convert_keycode (int const**,int,int) ; 
 int /*<<< orphan*/  del_mods (int) ; 
 int /*<<< orphan*/  del_shift_bit (int) ; 
 int /*<<< orphan*/  del_weak_mods (int) ; 
 int /*<<< orphan*/  dprintf (char*,int,int) ; 
 scalar_t__ get_shift_bit (int) ; 
 TYPE_3__* keyboard_report ; 
 int keymap_key_to_keycode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int) ; 
 int /*<<< orphan*/  send_keyboard_report () ; 
 int /*<<< orphan*/  unregister_code (int) ; 

void action_pseudo_lut(keyrecord_t *record, uint8_t base_keymap_id, const uint16_t (*keymap)[2]) {
    uint8_t prev_shift;
    uint16_t keycode;
    uint16_t pseudo_keycode;

    /* get keycode from keymap you specified */
    keycode = keymap_key_to_keycode(base_keymap_id, record->event.key);

    prev_shift = keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));

    if (record->event.pressed) {
        /* when magic commands entered, keycode does not converted */
        if (IS_COMMAND()) {
            if (prev_shift) {
                add_shift_bit(keycode);
            }
            register_code(keycode);
            return;
        }

        if (prev_shift) {
            pseudo_keycode = convert_keycode(keymap, keycode, true);
            dprintf("pressed: %02X, converted: %04X\n", keycode, pseudo_keycode);
            add_shift_bit(keycode);

            if (IS_LSFT(pseudo_keycode)) {
                register_code(QK_LSFT ^ pseudo_keycode);
            } else {
                /* delete shift mod temporarily */
                del_mods(prev_shift);
                send_keyboard_report();
                register_code(pseudo_keycode);
                add_mods(prev_shift);
                send_keyboard_report();
            }
        } else {
            pseudo_keycode = convert_keycode(keymap, keycode, false);
            dprintf("pressed: %02X, converted: %04X\n", keycode, pseudo_keycode);

            if (IS_LSFT(pseudo_keycode)) {
                add_weak_mods(MOD_BIT(KC_LSFT));
                send_keyboard_report();
                register_code(QK_LSFT ^ pseudo_keycode);
                /* on Windows, prevent key repeat to avoid unintended output */
                unregister_code(QK_LSFT ^ pseudo_keycode);
                del_weak_mods(MOD_BIT(KC_LSFT));
                send_keyboard_report();
            } else {
                register_code(pseudo_keycode);
            }
        }
    } else {
        if (get_shift_bit(keycode)) {
            del_shift_bit(keycode);
            pseudo_keycode = convert_keycode(keymap, keycode, true);
        } else {
            pseudo_keycode = convert_keycode(keymap, keycode, false);
        }
        dprintf("released: %02X, converted: %04X\n", keycode, pseudo_keycode);

        if (IS_LSFT(pseudo_keycode)) {
            unregister_code(QK_LSFT ^ pseudo_keycode);
        } else {
            unregister_code(pseudo_keycode);
        }
    }
}
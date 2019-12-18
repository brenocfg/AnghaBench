#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  CTRL_CLICK 134 
 int /*<<< orphan*/  KC_0 ; 
 int /*<<< orphan*/  KC_7 ; 
 int /*<<< orphan*/  KC_8 ; 
 int /*<<< orphan*/  KC_9 ; 
 int /*<<< orphan*/  KC_BTN1 ; 
 int /*<<< orphan*/  KC_LALT ; 
 int /*<<< orphan*/  KC_LCTL ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_RALT ; 
 int /*<<< orphan*/  KC_RCTL ; 
 int /*<<< orphan*/  KC_RSFT ; 
#define  LALT_CURLY 133 
#define  LCTRL_BRACKET 132 
#define  LSHFT_PAREN 131 
 int /*<<< orphan*/  MOD_BIT (int /*<<< orphan*/ ) ; 
#define  RALT_CURLY 130 
#define  RCTRL_BRACKET 129 
#define  RSHFT_PAREN 128 
 int /*<<< orphan*/  mousekey_clear () ; 
 int /*<<< orphan*/  mousekey_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousekey_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousekey_send () ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_keyboard_report () ; 
 int /*<<< orphan*/  tap_helper (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    // The code is copied from keymap_hasu.c in the tmk keyboards hhkb folder
    switch (id) {
        case LCTRL_BRACKET:
            tap_helper(record, KC_LCTL, KC_RALT, KC_8);
            break;
        case RCTRL_BRACKET:
            tap_helper(record, KC_RCTL, KC_RALT, KC_9);
            break;
        case LALT_CURLY:
            tap_helper(record, KC_LALT, KC_RALT, KC_7);
            break;
        case RALT_CURLY:
            tap_helper(record, KC_RALT, KC_RALT, KC_0);
            break;
        case LSHFT_PAREN:
            tap_helper(record, KC_LSFT, KC_LSFT, KC_8);
            break;
        case RSHFT_PAREN:
            tap_helper(record, KC_RSFT, KC_LSFT, KC_9);
            break;
        case CTRL_CLICK:
            if (record->event.pressed) {
                mousekey_clear();
                register_mods(MOD_BIT(KC_LCTL));
                send_keyboard_report();
                wait_ms(5);
                mousekey_on(KC_BTN1);
                mousekey_send();
                wait_ms(10);
                mousekey_off(KC_BTN1);
                mousekey_send();
                wait_ms(5);
                unregister_mods(MOD_BIT(KC_LCTL));
                send_keyboard_report();
            }
            break;
    }
}
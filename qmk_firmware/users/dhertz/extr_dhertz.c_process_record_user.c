#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_6__ {scalar_t__ pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  CMD_ALT_C 134 
#define  CMD_GRV_CMD 133 
#define  CMD_SFT_L 132 
#define  CMD_TAB_CMD 131 
#define  CTRL_A 130 
#define  HSH_TLD 129 
#define  ISO_COUNTRY_CODE 128 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_LSFT ; 
 int /*<<< orphan*/  KC_RGUI ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 char* SS_LALT (char*) ; 
 char* SS_LCTRL (char*) ; 
 char* SS_LGUI (char*) ; 
 char* SS_TAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_GRAVE ; 
 int /*<<< orphan*/  X_NONUS_BSLASH ; 
 int /*<<< orphan*/  X_TAB ; 
 int get_mods () ; 
 int /*<<< orphan*/  mod_or_mod_with_macro (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int process_record_keymap (int,TYPE_2__*) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case CMD_TAB_CMD:
            mod_or_mod_with_macro(record, KC_LGUI, SS_TAP(X_TAB));
            return false;
        case CMD_GRV_CMD:
            mod_or_mod_with_macro(record, KC_RGUI, SS_TAP(X_GRAVE));
            return false;
    }

    if (record->event.pressed) {
        switch(keycode) {
            case HSH_TLD:
                if (get_mods()&(MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))) {
                    SEND_STRING(SS_TAP(X_NONUS_BSLASH));
                } else {
                    SEND_STRING(SS_LALT("3"));
                }
                break;
            case CTRL_A:
                SEND_STRING(SS_LCTRL("a"));
                break;
            case CMD_ALT_C:
                SEND_STRING(SS_LGUI(SS_LALT("c")));
                break;
            case CMD_SFT_L:
                SEND_STRING(SS_LGUI("L"));
                break;
            case ISO_COUNTRY_CODE:
                SEND_STRING("country_iso_alpha2_code");
                break;
            default:
                return process_record_keymap(keycode, record);
        }
        return false;
    }
    return process_record_keymap(keycode, record);
}
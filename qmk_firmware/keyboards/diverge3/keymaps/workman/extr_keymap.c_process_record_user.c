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
typedef  int uint16_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  LO_0 138 
#define  LO_1 137 
#define  LO_2 136 
#define  LO_3 135 
#define  LO_4 134 
#define  LO_5 133 
#define  LO_6 132 
#define  LO_7 131 
#define  LO_8 130 
#define  LO_9 129 
#define  LO_BSPC 128 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int SHIFT_MOD ; 
 char* SS_TAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_BSPACE ; 
 int /*<<< orphan*/  X_DELETE ; 
 int /*<<< orphan*/  clear_mods () ; 
 int get_mods () ; 
 int /*<<< orphan*/  set_mods (int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    if (record->event.pressed) {
        switch (keycode) {
            case LO_BSPC:
                if (record->event.pressed) {
                    if (get_mods() & SHIFT_MOD) {
                        uint8_t current_mods = get_mods();
                        clear_mods();
                        SEND_STRING(SS_TAP(X_DELETE));
                        set_mods(current_mods);
                    } else {
                        SEND_STRING(SS_TAP(X_BSPACE));
                    }
                }
                return false;
            case LO_1:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("1");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("!");
                    }
                }
                return false;
            case LO_2:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("2");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("@");
                    }
                }
                return false;
            case LO_3:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("3");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("#");
                    }
                }
                return false;
            case LO_4:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("4");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("$");
                    }
                }
                return false;
            case LO_5:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("5");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("%");
                    }
                }
                return false;
            case LO_6:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("6");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("^");
                    }
                }
                return false;
            case LO_7:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("7");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("&");
                    }
                }
                return false;
            case LO_8:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("8");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("*");
                    }
                }
                return false;
            case LO_9:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("9");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING("(");
                    }
                }
                return false;
            case LO_0:
                if (record->event.pressed) {
                    uint8_t current_mods = get_mods();
                    if (current_mods & SHIFT_MOD) {
                        clear_mods();
                        SEND_STRING("0");
                        set_mods(current_mods);
                    } else {
                        SEND_STRING(")");
                    }
                }
                return false;
        }
    }
    return true;
}
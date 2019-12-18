#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {scalar_t__ pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_8__ {int mods; } ;

/* Variables and functions */
 scalar_t__ KC_6 ; 
 scalar_t__ KC_GRV ; 
 int /*<<< orphan*/  KC_LSFT ; 
 scalar_t__ KC_QUOT ; 
 int /*<<< orphan*/  KC_RALT ; 
 scalar_t__ KC_SPACE ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 TYPE_5__* keyboard_report ; 
 int process_german (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  register_code (scalar_t__) ; 
 int /*<<< orphan*/  unregister_code (scalar_t__) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //revive dead keys
#ifndef DONT_REVIVE_DEADKEYS
    bool shift_active = keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_LSFT));
    bool altgr_active = keyboard_report->mods & (MOD_BIT(KC_RALT));
    if ((keycode == KC_QUOT && !altgr_active) ||
        keycode == KC_GRV ||
        (keycode == KC_6 && shift_active))
    {
        if (record->event.pressed) {
            register_code(keycode);
            unregister_code(keycode);
            register_code(KC_SPACE);
            unregister_code(KC_SPACE);
        }
        return false;
    }
#endif
#if LANGUAGE == GERMAN
    return process_german(keycode, record);
#else
    return true;
#endif
}
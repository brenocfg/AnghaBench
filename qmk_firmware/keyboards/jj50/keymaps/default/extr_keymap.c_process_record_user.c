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
#define  P_MACRO 128 
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_TAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_UP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_KP_1 ; 
 int /*<<< orphan*/  X_KP_5 ; 
 int /*<<< orphan*/  X_KP_6 ; 
 int /*<<< orphan*/  X_LALT ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case P_MACRO:
                SEND_STRING(SS_DOWN(X_LALT));
                SEND_STRING(SS_TAP(X_KP_1));
                SEND_STRING(SS_TAP(X_KP_5));
                SEND_STRING(SS_TAP(X_KP_6));
                SEND_STRING(SS_UP(X_LALT));
                return false; break;
        }
    }
    return true;
}
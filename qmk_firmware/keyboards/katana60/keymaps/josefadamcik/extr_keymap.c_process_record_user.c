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
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  M_COLEMAK 131 
#define  M_QWERTY 130 
#define  W_COLEMAK 129 
#define  W_QWERTY 128 
 int /*<<< orphan*/  _M_COLEMAK ; 
 int /*<<< orphan*/  _M_QWERTY ; 
 int /*<<< orphan*/  _W_COLEMAK ; 
 int /*<<< orphan*/  _W_QWERTY ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_M_QWERTY);
            }
            return false;
            break;
        case M_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_M_COLEMAK);
            }
            return false;
            break;
        case W_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_W_QWERTY);
            }
            return false;
            break;
        case W_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_W_COLEMAK);
            }
            return false;
            break;
    }
    return true;
}
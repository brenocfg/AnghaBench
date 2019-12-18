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
#define  GAMING 133 
#define  QWERTY 132 
#define  QWERTZ 131 
 int /*<<< orphan*/  UC_LNX ; 
 int /*<<< orphan*/  UC_OSX ; 
 int /*<<< orphan*/  UC_WINC ; 
#define  UNI_LNX 130 
#define  UNI_MAC 129 
#define  UNI_WIN 128 
 int /*<<< orphan*/  _GAM ; 
 int /*<<< orphan*/  _QWY ; 
 int /*<<< orphan*/  _QWZ ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_unicode_input_mode (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case QWERTZ:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWZ);
            }
            return false;
            break;
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWY);
            }
            return false;
            break;
        case GAMING:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GAM);
            }
            return false;
            break;
        case UNI_LNX:
            set_unicode_input_mode(UC_LNX);
            return false;
            break;
        case UNI_WIN:
            set_unicode_input_mode(UC_WINC);
            return false;
            break;
        case UNI_MAC:
            set_unicode_input_mode(UC_OSX);
            return false;
            break;
    }
    return true;
}
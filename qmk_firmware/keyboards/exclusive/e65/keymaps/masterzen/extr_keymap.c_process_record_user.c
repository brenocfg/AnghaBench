#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_9__ {int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE ; 
#define  LAY_LIN 130 
#define  LAY_OSX 129 
 int /*<<< orphan*/  OSX ; 
#define  RGB_MOD 128 
 TYPE_4__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_step () ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 TYPE_3__ temp_config ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* layout switcher */
        case LAY_LIN:
            if (record->event.pressed) {
                set_single_persistent_default_layer(BASE);
            }
            return false;
            break;
        case LAY_OSX:
            if (record->event.pressed) {
                set_single_persistent_default_layer(OSX);
            }
            return false;
            break;
        case RGB_MOD:
            // allows to set the rgb mode while in the ADJUST layer which uses
            // its own mode
            if (record->event.pressed) {
                rgblight_mode(temp_config.mode);
                rgblight_step();
                temp_config.mode = rgblight_config.mode;
            }
            return false;
            break;
    }
    return true;
}
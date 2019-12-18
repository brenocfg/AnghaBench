#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */
#define  KC_CAPS 129 
#define  RESET 128 
 int /*<<< orphan*/  on_reset () ; 
 int /*<<< orphan*/  set_lights_default () ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS:
            #ifdef RGBLIGHT_ENABLE
            set_lights_default();
            #endif
            return true;
        case RESET:
            on_reset();
            return true;
        default:
            return true;
    }
}
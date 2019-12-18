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
 int /*<<< orphan*/  KC_ENTER ; 
 int /*<<< orphan*/  KC_F4 ; 
 int /*<<< orphan*/  LALT (int /*<<< orphan*/ ) ; 
#define  SUPER_ALT_F4 128 
 int /*<<< orphan*/  alt_f4_timer ; 
 int is_alt_f4_active ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {  // This will do most of the grunt work with the keycodes.
        case SUPER_ALT_F4:
            if (record->event.pressed) {
                if (!is_alt_f4_active) {
                    is_alt_f4_active = true;
                    tap_code16(LALT(KC_F4));  // Alt-F4
                } else {
                    tap_code(KC_ENTER);  // Tap enter
                }
            }
            alt_f4_timer = timer_read();
            break;
    }
    return true;
}
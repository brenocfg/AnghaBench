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
 int /*<<< orphan*/  KC_QUOT ; 
 int /*<<< orphan*/  KC_RGUI ; 
 int /*<<< orphan*/  MOD_BIT (int /*<<< orphan*/ ) ; 
#define  RG_QUOT 128 
 int /*<<< orphan*/  TAPPING_TERM ; 
 int /*<<< orphan*/  _NUMBER ; 
 int /*<<< orphan*/  key_timer ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_mods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  unregister_mods (int /*<<< orphan*/ ) ; 

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case RG_QUOT:   
            if (record->event.pressed) {
                key_timer = timer_read();
                layer_on(_NUMBER);
                register_mods(MOD_BIT(KC_RGUI));
            } else {
                unregister_mods(MOD_BIT(KC_RGUI));
                layer_off(_NUMBER);
                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    tap_code(KC_QUOT);
                }
            }
            return false; break;
    }
    return true;
}
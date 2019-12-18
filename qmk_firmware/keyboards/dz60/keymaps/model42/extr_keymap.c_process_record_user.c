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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_R ; 
 int /*<<< orphan*/  KC_RSHIFT ; 
 scalar_t__ LT_1_OR_RELOAD_CHROME ; 
 int /*<<< orphan*/  custom_lt_timer ; 
 int /*<<< orphan*/  layer_off (int) ; 
 int /*<<< orphan*/  layer_on (int) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if(LT_1_OR_RELOAD_CHROME == keycode) {
		if(record->event.pressed) {
			custom_lt_timer = timer_read();
			layer_on(1);
		} else {
			layer_off(1);
			if (timer_elapsed(custom_lt_timer) < 200) {
				register_code(KC_LGUI);
				register_code(KC_RSHIFT);
				register_code(KC_R);
				unregister_code(KC_R);
				unregister_code(KC_RSHIFT);
				unregister_code(KC_LGUI);
			}
		}
	}
	return true;
}
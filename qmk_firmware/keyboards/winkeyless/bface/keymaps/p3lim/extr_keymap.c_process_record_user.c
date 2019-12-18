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
#define  C_ESC0 129 
#define  C_ESC1 128 
 int /*<<< orphan*/  KC_ESCAPE ; 
 int /*<<< orphan*/  KC_GRAVE ; 
 int MOD_MASK_SHIFT ; 
 int get_mods () ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record){
	switch(keycode){
		case C_ESC0: // layer 0
			if(record->event.pressed){
				if(get_mods() & MOD_MASK_SHIFT)
					register_code(KC_GRAVE);
				else
					register_code(KC_ESCAPE);
			} else {
				if(get_mods() & MOD_MASK_SHIFT)
					unregister_code(KC_GRAVE);
				else
					unregister_code(KC_ESCAPE);
			}
			return false;
		case C_ESC1: // layer 1
			if(record->event.pressed){
				if(get_mods() & MOD_MASK_SHIFT)
					register_code(KC_ESCAPE);
				else
					register_code(KC_GRAVE);
			} else {
				if(get_mods() & MOD_MASK_SHIFT)
					unregister_code(KC_ESCAPE);
				else
					unregister_code(KC_GRAVE);
			}
			return false;
	}
	return true;
}
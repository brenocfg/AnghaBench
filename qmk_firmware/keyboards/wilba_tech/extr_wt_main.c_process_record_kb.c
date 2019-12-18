#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {scalar_t__ pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  FN_MO13 129 
#define  FN_MO23 128 
 int MACRO00 ; 
 int MACRO15 ; 
 int /*<<< orphan*/  dynamic_keymap_macro_send (int) ; 
 int /*<<< orphan*/  layer_off (int) ; 
 int /*<<< orphan*/  layer_on (int) ; 
 int /*<<< orphan*/  process_record_backlight (int,TYPE_2__*) ; 
 int process_record_user (int,TYPE_2__*) ; 
 int /*<<< orphan*/  update_tri_layer (int,int,int) ; 

bool process_record_kb(uint16_t keycode, keyrecord_t *record)
{
#if RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED
	process_record_backlight(keycode, record);
#endif // RGB_BACKLIGHT_ENABLED || MONO_BACKLIGHT_ENABLED

	switch(keycode) {
		case FN_MO13:
			if (record->event.pressed) {
				layer_on(1);
				update_tri_layer(1, 2, 3);
			} else {
				layer_off(1);
				update_tri_layer(1, 2, 3);
			}
			return false;
			break;
		case FN_MO23:
			if (record->event.pressed) {
				layer_on(2);
				update_tri_layer(1, 2, 3);
			} else {
				layer_off(2);
				update_tri_layer(1, 2, 3);
			}
			return false;
			break;
	}

#ifdef DYNAMIC_KEYMAP_ENABLE
	// Handle macros
	if (record->event.pressed) {
		if ( keycode >= MACRO00 && keycode <= MACRO15 )
		{
			uint8_t id = keycode - MACRO00;
			dynamic_keymap_macro_send(id);
			return false;
		}
	}
#endif //DYNAMIC_KEYMAP_ENABLE

	return process_record_user(keycode, record);
}
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
#define  BL_OFF 134 
#define  BL_ON 133 
#define  BL_TOGG 132 
#define  COLEMAK 131 
#define  DVORAK 130 
#define  QWERTY 129 
#define  QWERTZ 128 
 int /*<<< orphan*/  _COLEMA_LAYER ; 
 int /*<<< orphan*/  _DVORAK_LAYER ; 
 int /*<<< orphan*/  _QWERTY_LAYER ; 
 int /*<<< orphan*/  _QWERTZ_LAYER ; 
 int /*<<< orphan*/  cospad_bl_led_off () ; 
 int /*<<< orphan*/  cospad_bl_led_on () ; 
 int /*<<< orphan*/  cospad_bl_led_togg () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case BL_TOGG:
			if (record->event.pressed) {
				cospad_bl_led_togg();
			}
			return false;
		case BL_ON:
			if (record->event.pressed) {
				cospad_bl_led_on();
			}
			return false;
		case BL_OFF:
			if (record->event.pressed) {
				cospad_bl_led_off();
			}
			return false;
		case QWERTY:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_QWERTY_LAYER);
				print("switched to QWERTY layout\n");
			}
			return false;
			break;
		case QWERTZ:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_QWERTZ_LAYER);
			}
			return false;
			break;
		case COLEMAK:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_COLEMA_LAYER);
			}
			return false;
			break;
		case DVORAK:
			if (record->event.pressed) {
				set_single_persistent_default_layer(_DVORAK_LAYER);
			}
			return false;
			break;
		default:
			return true;
	}
}
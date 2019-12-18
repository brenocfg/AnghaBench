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
#define  COPY 130 
#define  HW 129 
 int /*<<< orphan*/  KC_C ; 
 int /*<<< orphan*/  KC_V ; 
 int /*<<< orphan*/  LCTL (int /*<<< orphan*/ ) ; 
#define  PASTA 128 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	//uint8_t layer = biton32(layer_state);  // get the current layer

	// Basic example functions
	switch (keycode) {
		case HW:
			if (record->event.pressed) {
					SEND_STRING("Hello, world!");
				} else {
					SEND_STRING("Goodbye, cruel world!");
				}
			break;
			case COPY:
				if (record->event.pressed) {
					tap_code16(LCTL(KC_C)); // Replace with tap_code16(LCMD(KC_C)) to enable for Mac
				}
			break;
			case PASTA:
				if (record->event.pressed) {
					tap_code16(LCTL(KC_V)); // Replace with tap_code16(LCMD(KC_V)) to enable for Mac
				}
			break;
		return false;
	}
	return true;
}
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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  MAS_BLU 139 
#define  MAS_CRM 138 
#define  MAS_CYN 137 
#define  MAS_GRN 136 
#define  MAS_KEY 135 
#define  MAS_MGT 134 
#define  MAS_PRP 133 
#define  MAS_RED 132 
#define  MAS_WHT 131 
#define  MAS_YEL 130 
#define  REBOOT 129 
#define  REEPROM 128 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  reset_keyboard () ; 
 int /*<<< orphan*/  rgb_matrix_sethsv (int,int,int) ; 
 int timer_elapsed32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read32 () ; 

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
	static uint32_t key_timer;

	switch (keycode) {
	case REBOOT:
		if (record->event.pressed) {
			key_timer = timer_read32();
		} else {
			if (timer_elapsed32(key_timer) >= 500) {
				reset_keyboard();
			}
		}

		return false;

	case REEPROM:
		if (record->event.pressed) {
			key_timer = timer_read32();
		} else {
			if (timer_elapsed32(key_timer) >= 500) {
				eeconfig_init();
			}
		}

		return false;

	case MAS_CRM:
		if (record->event.pressed) {
			rgb_matrix_sethsv(32, 160, 255);
		}

		return false;

	case MAS_PRP:
		if (record->event.pressed) {
			rgb_matrix_sethsv(192, 112, 255);
		}

		return false;

	case MAS_RED:
		if (record->event.pressed) {
			rgb_matrix_sethsv(0, 255, 255);
		}

		return false;

	case MAS_GRN:
		if (record->event.pressed) {
			rgb_matrix_sethsv(88, 255, 255);
		}

		return false;

	case MAS_BLU:
		if (record->event.pressed) {
			rgb_matrix_sethsv(168, 255, 255);
		}

		return false;

	case MAS_CYN:
		if (record->event.pressed) {
			rgb_matrix_sethsv(128, 255, 255);
		}

		return false;

	case MAS_MGT:
		if (record->event.pressed) {
			rgb_matrix_sethsv(216, 255, 255);
		}

		return false;

	case MAS_YEL:
		if (record->event.pressed) {
			rgb_matrix_sethsv(40, 255, 255);
		}

		return false;

	case MAS_KEY:
		if (record->event.pressed) {
			rgb_matrix_sethsv(0, 0, 0);
		}

		return false;

	case MAS_WHT:
		if (record->event.pressed) {
			rgb_matrix_sethsv(128, 0, 255);
		}

		return false;

	default:
		return true;
	}
}
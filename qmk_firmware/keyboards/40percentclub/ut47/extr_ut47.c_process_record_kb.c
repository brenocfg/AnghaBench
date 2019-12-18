#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int row; scalar_t__ col; } ;
struct TYPE_7__ {TYPE_1__ key; scalar_t__ pressed; } ;
struct TYPE_8__ {TYPE_2__ event; } ;
typedef  TYPE_3__ keyrecord_t ;

/* Variables and functions */
 int process_record_user (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  serial_send (scalar_t__) ; 

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	// put your per-action keyboard code here
	// runs for every action, just before processing by the firmware
  if (record->event.pressed) {
    #ifdef LED_ENABLE
      serial_send((record->event.key.row*16)+record->event.key.col);
    #endif
  }
	return process_record_user(keycode, record);
}
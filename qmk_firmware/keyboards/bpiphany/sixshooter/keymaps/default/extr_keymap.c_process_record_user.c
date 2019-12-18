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
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  SS_LOFF 129 
#define  SS_LON 128 
 int /*<<< orphan*/  sixshooter_led_all_off () ; 
 int /*<<< orphan*/  sixshooter_led_all_on () ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	// Put your per-action keyboard code here.
	// Runs for every action, just before processing by the firmware.
  if (record->event.pressed) {

    // Check for custom keycodes for turning on and off LEDs
    switch(keycode) {
      case SS_LON:
        sixshooter_led_all_on();
        return false;
      case SS_LOFF:
        sixshooter_led_all_off();
        return false;
    }
  }
  return true;
}
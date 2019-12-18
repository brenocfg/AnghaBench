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
 int PORTE ; 
#define  YD68_BT_PWR 129 
#define  YD68_RGB_PWR 128 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case YD68_BT_PWR:
      if (record->event.pressed) {
        // when keycode YD68_BT_PWR is pressed
      } else {
        // when keycode YD68_BT_PWR is released
      }
      break;
    case YD68_RGB_PWR:
      if (record->event.pressed) {
        // when keycode YD68_RGB_PWR is pressed
		PORTE ^= (1<<2);
      } else {
        // when keycode YD68_RGB_PWR is released
      }
      break;
  }
  return true;
}
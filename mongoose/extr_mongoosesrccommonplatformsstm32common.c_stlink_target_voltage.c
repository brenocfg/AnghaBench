#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  stlink_t ;

/* Variables and functions */
 int _stlink_usb_target_voltage (int /*<<< orphan*/ *) ; 

int stlink_target_voltage(stlink_t *sl) {
  return _stlink_usb_target_voltage(sl);
}
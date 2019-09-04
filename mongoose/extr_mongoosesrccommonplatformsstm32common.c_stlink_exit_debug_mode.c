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
 int /*<<< orphan*/  STLINK_REG_DHCSR ; 
 int /*<<< orphan*/  STLINK_REG_DHCSR_DBGKEY ; 
 int _stlink_usb_exit_debug_mode (int /*<<< orphan*/ *) ; 
 int stlink_write_debug32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int stlink_exit_debug_mode(stlink_t *sl) {
  int ret;

  ret = stlink_write_debug32(sl, STLINK_REG_DHCSR, STLINK_REG_DHCSR_DBGKEY);
  if (ret == -1) return ret;

  return _stlink_usb_exit_debug_mode(sl);
}
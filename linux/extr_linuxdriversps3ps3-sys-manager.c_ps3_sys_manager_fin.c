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
struct ps3_system_bus_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lv1_pause (int) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 scalar_t__ ps3_sys_manager_handle_msg (struct ps3_system_bus_device*) ; 
 int /*<<< orphan*/  ps3_sys_manager_send_request_shutdown (struct ps3_system_bus_device*) ; 

__attribute__((used)) static void ps3_sys_manager_fin(struct ps3_system_bus_device *dev)
{
	ps3_sys_manager_send_request_shutdown(dev);

	pr_emerg("System Halted, OK to turn off power\n");

	while (ps3_sys_manager_handle_msg(dev)) {
		/* pause until next DEC interrupt */
		lv1_pause(0);
	}

	while (1) {
		/* pause, ignoring DEC interrupt */
		lv1_pause(1);
	}
}
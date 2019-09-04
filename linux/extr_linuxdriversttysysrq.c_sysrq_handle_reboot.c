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

/* Variables and functions */
 int /*<<< orphan*/  emergency_restart () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  lockdep_off () ; 

__attribute__((used)) static void sysrq_handle_reboot(int key)
{
	lockdep_off();
	local_irq_enable();
	emergency_restart();
}
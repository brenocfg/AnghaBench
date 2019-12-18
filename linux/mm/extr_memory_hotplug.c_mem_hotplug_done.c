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
 int /*<<< orphan*/  cpus_read_unlock () ; 
 int /*<<< orphan*/  mem_hotplug_lock ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 

void mem_hotplug_done(void)
{
	percpu_up_write(&mem_hotplug_lock);
	cpus_read_unlock();
}
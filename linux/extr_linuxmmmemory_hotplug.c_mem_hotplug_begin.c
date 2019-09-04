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
 int /*<<< orphan*/  cpus_read_lock () ; 
 int /*<<< orphan*/  mem_hotplug_lock ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 

void mem_hotplug_begin(void)
{
	cpus_read_lock();
	percpu_down_write(&mem_hotplug_lock);
}
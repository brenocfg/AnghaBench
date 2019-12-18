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
 int /*<<< orphan*/  cpuset_rwsem ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  rebuild_sched_domains_locked () ; 

void rebuild_sched_domains(void)
{
	get_online_cpus();
	percpu_down_write(&cpuset_rwsem);
	rebuild_sched_domains_locked();
	percpu_up_write(&cpuset_rwsem);
	put_online_cpus();
}
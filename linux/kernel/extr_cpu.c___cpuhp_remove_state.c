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
typedef  enum cpuhp_state { ____Placeholder_cpuhp_state } cpuhp_state ;

/* Variables and functions */
 int /*<<< orphan*/  __cpuhp_remove_state_cpuslocked (int,int) ; 
 int /*<<< orphan*/  cpus_read_lock () ; 
 int /*<<< orphan*/  cpus_read_unlock () ; 

void __cpuhp_remove_state(enum cpuhp_state state, bool invoke)
{
	cpus_read_lock();
	__cpuhp_remove_state_cpuslocked(state, invoke);
	cpus_read_unlock();
}
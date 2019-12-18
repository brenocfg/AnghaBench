#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int hw_states_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cpu_count ; 
 int /*<<< orphan*/  cpuidle_state_time (int,int) ; 
 TYPE_1__ cpuidle_sysfs_monitor ; 
 int /*<<< orphan*/  dprint (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** previous_count ; 
 int /*<<< orphan*/  start_time ; 

__attribute__((used)) static int cpuidle_start(void)
{
	int cpu, state;
	clock_gettime(CLOCK_REALTIME, &start_time);
	for (cpu = 0; cpu < cpu_count; cpu++) {
		for (state = 0; state < cpuidle_sysfs_monitor.hw_states_num;
		     state++) {
			previous_count[cpu][state] =
				cpuidle_state_time(cpu, state);
			dprint("CPU %d - State: %d - Val: %llu\n",
			       cpu, state, previous_count[cpu][state]);
		}
	};
	return 0;
}
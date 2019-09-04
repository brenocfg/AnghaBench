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
struct timespec {int dummy; } ;
struct TYPE_2__ {int hw_states_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int cpu_count ; 
 int /*<<< orphan*/  cpuidle_state_time (int,int) ; 
 TYPE_1__ cpuidle_sysfs_monitor ; 
 int /*<<< orphan*/ ** current_count ; 
 int /*<<< orphan*/  dprint (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** previous_count ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  timediff ; 
 int /*<<< orphan*/  timespec_diff_us (int /*<<< orphan*/ ,struct timespec) ; 

__attribute__((used)) static int cpuidle_stop(void)
{
	int cpu, state;
	struct timespec end_time;
	clock_gettime(CLOCK_REALTIME, &end_time);
	timediff = timespec_diff_us(start_time, end_time);

	for (cpu = 0; cpu < cpu_count; cpu++) {
		for (state = 0; state < cpuidle_sysfs_monitor.hw_states_num;
		     state++) {
			current_count[cpu][state] =
				cpuidle_state_time(cpu, state);
			dprint("CPU %d - State: %d - Val: %llu\n",
			       cpu, state, previous_count[cpu][state]);
		}
	};
	return 0;
}
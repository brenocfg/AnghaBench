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
struct cpuidle_monitor {int hw_states_num; int /*<<< orphan*/  name; int /*<<< orphan*/  name_len; } ;
struct TYPE_2__ {int id; int /*<<< orphan*/  get_count_percent; int /*<<< orphan*/  range; int /*<<< orphan*/  desc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ CSTATE_DESC_LEN ; 
 scalar_t__ CSTATE_NAME_LEN ; 
 int /*<<< orphan*/  RANGE_THREAD ; 
 int cpu_count ; 
 TYPE_1__* cpuidle_cstates ; 
 int /*<<< orphan*/  cpuidle_get_count_percent ; 
 int cpuidle_state_count (int) ; 
 char* cpuidle_state_desc (int,int) ; 
 char* cpuidle_state_name (int,int) ; 
 struct cpuidle_monitor cpuidle_sysfs_monitor ; 
 void** current_count ; 
 int /*<<< orphan*/  fix_up_intel_idle_driver_name (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  map_power_idle_state_name (char*) ; 
 void** previous_count ; 
 int sched_getcpu () ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static struct cpuidle_monitor *cpuidle_register(void)
{
	int num;
	char *tmp;
	int this_cpu;

	this_cpu = sched_getcpu();

	/* Assume idle state count is the same for all CPUs */
	cpuidle_sysfs_monitor.hw_states_num = cpuidle_state_count(this_cpu);

	if (cpuidle_sysfs_monitor.hw_states_num <= 0)
		return NULL;

	for (num = 0; num < cpuidle_sysfs_monitor.hw_states_num; num++) {
		tmp = cpuidle_state_name(this_cpu, num);
		if (tmp == NULL)
			continue;

		map_power_idle_state_name(tmp);
		fix_up_intel_idle_driver_name(tmp, num);
		strncpy(cpuidle_cstates[num].name, tmp, CSTATE_NAME_LEN - 1);
		free(tmp);

		tmp = cpuidle_state_desc(this_cpu, num);
		if (tmp == NULL)
			continue;
		strncpy(cpuidle_cstates[num].desc, tmp,	CSTATE_DESC_LEN - 1);
		free(tmp);

		cpuidle_cstates[num].range = RANGE_THREAD;
		cpuidle_cstates[num].id = num;
		cpuidle_cstates[num].get_count_percent =
			cpuidle_get_count_percent;
	};

	/* Free this at program termination */
	previous_count = malloc(sizeof(long long *) * cpu_count);
	current_count = malloc(sizeof(long long *) * cpu_count);
	for (num = 0; num < cpu_count; num++) {
		previous_count[num] = malloc(sizeof(long long) *
					cpuidle_sysfs_monitor.hw_states_num);
		current_count[num] = malloc(sizeof(long long) *
					cpuidle_sysfs_monitor.hw_states_num);
	}

	cpuidle_sysfs_monitor.name_len = strlen(cpuidle_sysfs_monitor.name);
	return &cpuidle_sysfs_monitor;
}
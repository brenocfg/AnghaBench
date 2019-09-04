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
 int SNB_CSTATE_COUNT ; 
 int TSC ; 
 int base_cpu ; 
 int cpu_count ; 
 unsigned long long** current_count ; 
 int* is_valid ; 
 int /*<<< orphan*/  snb_get_count (int,unsigned long long*,int) ; 
 unsigned long long tsc_at_measure_end ; 

__attribute__((used)) static int snb_stop(void)
{
	unsigned long long val;
	int num, cpu;

	snb_get_count(TSC, &tsc_at_measure_end, base_cpu);

	for (num = 0; num < SNB_CSTATE_COUNT; num++) {
		for (cpu = 0; cpu < cpu_count; cpu++) {
			is_valid[cpu] = !snb_get_count(num, &val, cpu);
			current_count[num][cpu] = val;
		}
	}
	return 0;
}
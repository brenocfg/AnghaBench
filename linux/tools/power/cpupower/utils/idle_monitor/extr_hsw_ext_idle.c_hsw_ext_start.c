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
 int HSW_EXT_CSTATE_COUNT ; 
 int TSC ; 
 int base_cpu ; 
 int cpu_count ; 
 int /*<<< orphan*/  hsw_ext_get_count (int,unsigned long long*,int) ; 
 unsigned long long** previous_count ; 
 unsigned long long tsc_at_measure_start ; 

__attribute__((used)) static int hsw_ext_start(void)
{
	int num, cpu;
	unsigned long long val;

	for (num = 0; num < HSW_EXT_CSTATE_COUNT; num++) {
		for (cpu = 0; cpu < cpu_count; cpu++) {
			hsw_ext_get_count(num, &val, cpu);
			previous_count[num][cpu] = val;
		}
	}
	hsw_ext_get_count(TSC, &tsc_at_measure_start, base_cpu);
	return 0;
}
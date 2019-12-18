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
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cpu_count ; 
 int /*<<< orphan*/  dprint (char*,unsigned long long) ; 
 int /*<<< orphan*/  mperf_get_tsc (unsigned long long*) ; 
 int /*<<< orphan*/  mperf_measure_stats (int) ; 
 int /*<<< orphan*/  time_end ; 
 unsigned long long tsc_at_measure_end ; 

__attribute__((used)) static int mperf_stop(void)
{
	unsigned long long dbg;
	int cpu;

	for (cpu = 0; cpu < cpu_count; cpu++)
		mperf_measure_stats(cpu);

	mperf_get_tsc(&tsc_at_measure_end);
	clock_gettime(CLOCK_REALTIME, &time_end);

	mperf_get_tsc(&dbg);
	dprint("TSC diff: %llu\n", dbg - tsc_at_measure_end);

	return 0;
}
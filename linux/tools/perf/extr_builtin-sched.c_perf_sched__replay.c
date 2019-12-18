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
struct perf_sched {unsigned long replay_repeat; scalar_t__ nr_run_events_optimized; scalar_t__ multitarget_wakeups; scalar_t__ targetless_wakeups; int /*<<< orphan*/  nr_wakeup_events; int /*<<< orphan*/  nr_sleep_events; int /*<<< orphan*/  nr_run_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_cross_task_wakeups (struct perf_sched*) ; 
 int /*<<< orphan*/  calibrate_run_measurement_overhead (struct perf_sched*) ; 
 int /*<<< orphan*/  calibrate_sleep_measurement_overhead (struct perf_sched*) ; 
 int /*<<< orphan*/  create_tasks (struct perf_sched*) ; 
 scalar_t__ perf_sched__read_events (struct perf_sched*) ; 
 int /*<<< orphan*/  print_task_traces (struct perf_sched*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  run_one_test (struct perf_sched*) ; 
 int /*<<< orphan*/  test_calibrations (struct perf_sched*) ; 

__attribute__((used)) static int perf_sched__replay(struct perf_sched *sched)
{
	unsigned long i;

	calibrate_run_measurement_overhead(sched);
	calibrate_sleep_measurement_overhead(sched);

	test_calibrations(sched);

	if (perf_sched__read_events(sched))
		return -1;

	printf("nr_run_events:        %ld\n", sched->nr_run_events);
	printf("nr_sleep_events:      %ld\n", sched->nr_sleep_events);
	printf("nr_wakeup_events:     %ld\n", sched->nr_wakeup_events);

	if (sched->targetless_wakeups)
		printf("target-less wakeups:  %ld\n", sched->targetless_wakeups);
	if (sched->multitarget_wakeups)
		printf("multi-target wakeups: %ld\n", sched->multitarget_wakeups);
	if (sched->nr_run_events_optimized)
		printf("run atoms optimized: %ld\n",
			sched->nr_run_events_optimized);

	print_task_traces(sched);
	add_cross_task_wakeups(sched);

	create_tasks(sched);
	printf("------------------------------------------------------------\n");
	for (i = 0; i < sched->replay_repeat; i++)
		run_one_test(sched);

	return 0;
}
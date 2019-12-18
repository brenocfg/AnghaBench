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
struct perf_sched {int dummy; } ;

/* Variables and functions */
 scalar_t__ perf_sched__read_events (struct perf_sched*) ; 
 int /*<<< orphan*/  print_bad_events (struct perf_sched*) ; 
 scalar_t__ setup_color_cpus (struct perf_sched*) ; 
 scalar_t__ setup_color_pids (struct perf_sched*) ; 
 scalar_t__ setup_map_cpus (struct perf_sched*) ; 
 int /*<<< orphan*/  setup_pager () ; 

__attribute__((used)) static int perf_sched__map(struct perf_sched *sched)
{
	if (setup_map_cpus(sched))
		return -1;

	if (setup_color_pids(sched))
		return -1;

	if (setup_color_cpus(sched))
		return -1;

	setup_pager();
	if (perf_sched__read_events(sched))
		return -1;
	print_bad_events(sched);
	return 0;
}
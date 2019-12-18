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
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dead_event ; 
 int /*<<< orphan*/  dead_events_mask ; 
 int /*<<< orphan*/  perf_event_disable (struct perf_event*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct perf_event* this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  watchdog_cpus ; 
 int /*<<< orphan*/  watchdog_ev ; 

void hardlockup_detector_perf_disable(void)
{
	struct perf_event *event = this_cpu_read(watchdog_ev);

	if (event) {
		perf_event_disable(event);
		this_cpu_write(watchdog_ev, NULL);
		this_cpu_write(dead_event, event);
		cpumask_set_cpu(smp_processor_id(), &dead_events_mask);
		atomic_dec(&watchdog_cpus);
	}
}
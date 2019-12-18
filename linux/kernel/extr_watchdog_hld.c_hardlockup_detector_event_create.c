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
struct perf_event_attr {int /*<<< orphan*/  sample_period; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct perf_event*) ; 
 int PTR_ERR (struct perf_event*) ; 
 int /*<<< orphan*/  hw_nmi_get_sample_period (int /*<<< orphan*/ ) ; 
 struct perf_event* perf_event_create_kernel_counter (struct perf_event_attr*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  watchdog_ev ; 
 int /*<<< orphan*/  watchdog_overflow_callback ; 
 int /*<<< orphan*/  watchdog_thresh ; 
 struct perf_event_attr wd_hw_attr ; 

__attribute__((used)) static int hardlockup_detector_event_create(void)
{
	unsigned int cpu = smp_processor_id();
	struct perf_event_attr *wd_attr;
	struct perf_event *evt;

	wd_attr = &wd_hw_attr;
	wd_attr->sample_period = hw_nmi_get_sample_period(watchdog_thresh);

	/* Try to register using hardware perf events */
	evt = perf_event_create_kernel_counter(wd_attr, cpu, NULL,
					       watchdog_overflow_callback, NULL);
	if (IS_ERR(evt)) {
		pr_debug("Perf event create on CPU %d failed with %ld\n", cpu,
			 PTR_ERR(evt));
		return PTR_ERR(evt);
	}
	this_cpu_write(watchdog_ev, evt);
	return 0;
}
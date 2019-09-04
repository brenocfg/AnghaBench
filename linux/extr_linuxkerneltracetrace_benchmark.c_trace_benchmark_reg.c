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
 int EBUSY ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  benchmark_event_kthread ; 
 int /*<<< orphan*/  bm_event_thread ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ok_to_run ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

int trace_benchmark_reg(void)
{
	if (!ok_to_run) {
		pr_warning("trace benchmark cannot be started via kernel command line\n");
		return -EBUSY;
	}

	bm_event_thread = kthread_run(benchmark_event_kthread,
				      NULL, "event_benchmark");
	if (IS_ERR(bm_event_thread)) {
		pr_warning("trace benchmark failed to create kernel thread\n");
		return PTR_ERR(bm_event_thread);
	}

	return 0;
}
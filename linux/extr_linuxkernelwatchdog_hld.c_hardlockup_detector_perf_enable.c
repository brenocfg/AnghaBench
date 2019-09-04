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
 int /*<<< orphan*/  atomic_fetch_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ hardlockup_detector_event_create () ; 
 int /*<<< orphan*/  perf_event_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_cpus ; 
 int /*<<< orphan*/  watchdog_ev ; 

void hardlockup_detector_perf_enable(void)
{
	if (hardlockup_detector_event_create())
		return;

	/* use original value for check */
	if (!atomic_fetch_inc(&watchdog_cpus))
		pr_info("Enabled. Permanently consumes one hw-PMU counter.\n");

	perf_event_enable(this_cpu_read(watchdog_ev));
}
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
 int /*<<< orphan*/  CONFIG_GENERIC_SCHED_CLOCK ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nmi_count ; 
 scalar_t__ nmi_cpu ; 
 int /*<<< orphan*/  nmi_total_ts ; 
 scalar_t__ nmi_ts_start ; 
 scalar_t__ smp_processor_id () ; 
 scalar_t__ time_get () ; 

void trace_hwlat_callback(bool enter)
{
	if (smp_processor_id() != nmi_cpu)
		return;

	/*
	 * Currently trace_clock_local() calls sched_clock() and the
	 * generic version is not NMI safe.
	 */
	if (!IS_ENABLED(CONFIG_GENERIC_SCHED_CLOCK)) {
		if (enter)
			nmi_ts_start = time_get();
		else
			nmi_total_ts += time_get() - nmi_ts_start;
	}

	if (enter)
		nmi_count++;
}
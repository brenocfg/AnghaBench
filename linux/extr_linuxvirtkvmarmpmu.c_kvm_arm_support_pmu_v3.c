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
 scalar_t__ perf_num_counters () ; 

bool kvm_arm_support_pmu_v3(void)
{
	/*
	 * Check if HW_PERF_EVENTS are supported by checking the number of
	 * hardware performance counters. This could ensure the presence of
	 * a physical PMU and CONFIG_PERF_EVENT is selected.
	 */
	return (perf_num_counters() > 0);
}
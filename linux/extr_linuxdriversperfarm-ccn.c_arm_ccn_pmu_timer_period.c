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
typedef  int u64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ arm_ccn_pmu_poll_period_us ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 

__attribute__((used)) static ktime_t arm_ccn_pmu_timer_period(void)
{
	return ns_to_ktime((u64)arm_ccn_pmu_poll_period_us * 1000);
}
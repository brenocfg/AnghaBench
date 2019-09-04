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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct hw_perf_event {scalar_t__ idx; int /*<<< orphan*/  prev_count; } ;
struct cluster_pmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2_COUNTER_RELOAD ; 
 int /*<<< orphan*/  L2_CYCLE_COUNTER_RELOAD ; 
 int /*<<< orphan*/  cluster_pmu_counter_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ l2_cycle_ctr_idx ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2_cache_cluster_set_period(struct cluster_pmu *cluster,
				       struct hw_perf_event *hwc)
{
	u32 idx = hwc->idx;
	u64 new;

	/*
	 * We limit the max period to half the max counter value so
	 * that even in the case of extreme interrupt latency the
	 * counter will (hopefully) not wrap past its initial value.
	 */
	if (idx == l2_cycle_ctr_idx)
		new = L2_CYCLE_COUNTER_RELOAD;
	else
		new = L2_COUNTER_RELOAD;

	local64_set(&hwc->prev_count, new);
	cluster_pmu_counter_set_value(idx, new);
}
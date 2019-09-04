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
struct hw_perf_event {int sample_period; int last_period; int /*<<< orphan*/  prev_count; int /*<<< orphan*/  period_left; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct arm_pmu {int /*<<< orphan*/  (* write_counter ) (struct perf_event*,int) ;} ;
typedef  int s64 ;

/* Variables and functions */
 int arm_pmu_event_max_period (struct perf_event*) ; 
 int local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*,int) ; 
 struct arm_pmu* to_arm_pmu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int armpmu_event_set_period(struct perf_event *event)
{
	struct arm_pmu *armpmu = to_arm_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;
	s64 left = local64_read(&hwc->period_left);
	s64 period = hwc->sample_period;
	u64 max_period;
	int ret = 0;

	max_period = arm_pmu_event_max_period(event);
	if (unlikely(left <= -period)) {
		left = period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	}

	if (unlikely(left <= 0)) {
		left += period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	}

	/*
	 * Limit the maximum period to prevent the counter value
	 * from overtaking the one we are about to program. In
	 * effect we are reducing max_period to account for
	 * interrupt latency (and we are being very conservative).
	 */
	if (left > (max_period >> 1))
		left = (max_period >> 1);

	local64_set(&hwc->prev_count, (u64)-left);

	armpmu->write_counter(event, (u64)(-left) & max_period);

	perf_event_update_userpage(event);

	return ret;
}
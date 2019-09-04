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
struct pmu_hw_events {int /*<<< orphan*/ ** events; } ;
struct hw_perf_event {int idx; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct arm_pmu {int /*<<< orphan*/  (* clear_event_idx ) (struct pmu_hw_events*,struct perf_event*) ;int /*<<< orphan*/  hw_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  armpmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct pmu_hw_events*,struct perf_event*) ; 
 struct pmu_hw_events* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct arm_pmu* to_arm_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
armpmu_del(struct perf_event *event, int flags)
{
	struct arm_pmu *armpmu = to_arm_pmu(event->pmu);
	struct pmu_hw_events *hw_events = this_cpu_ptr(armpmu->hw_events);
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	armpmu_stop(event, PERF_EF_UPDATE);
	hw_events->events[idx] = NULL;
	armpmu->clear_event_idx(hw_events, event);
	perf_event_update_userpage(event);
	/* Clear the allocated counter */
	hwc->idx = -1;
}
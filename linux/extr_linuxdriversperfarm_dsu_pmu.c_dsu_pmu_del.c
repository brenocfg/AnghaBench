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
struct hw_perf_event {int idx; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct dsu_hw_events {int /*<<< orphan*/  used_mask; int /*<<< orphan*/ ** events; } ;
struct dsu_pmu {struct dsu_hw_events hw_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsu_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct dsu_pmu* to_dsu_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsu_pmu_del(struct perf_event *event, int flags)
{
	struct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);
	struct dsu_hw_events *hw_events = &dsu_pmu->hw_events;
	struct hw_perf_event *hwc = &event->hw;
	int idx = hwc->idx;

	dsu_pmu_stop(event, PERF_EF_UPDATE);
	hw_events->events[idx] = NULL;
	clear_bit(idx, hw_events->used_mask);
	perf_event_update_userpage(event);
}
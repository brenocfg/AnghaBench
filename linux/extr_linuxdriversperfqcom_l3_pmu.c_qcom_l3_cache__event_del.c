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
struct hw_perf_event {size_t idx; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct l3cache_pmu {int /*<<< orphan*/  used_mask; int /*<<< orphan*/ ** events; } ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ event_uses_long_counter (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  qcom_l3_cache__event_stop (struct perf_event*,int) ; 
 struct l3cache_pmu* to_l3cache_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_l3_cache__event_del(struct perf_event *event, int flags)
{
	struct l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;
	int order = event_uses_long_counter(event) ? 1 : 0;

	/* Stop and clean up */
	qcom_l3_cache__event_stop(event,  flags | PERF_EF_UPDATE);
	l3pmu->events[hwc->idx] = NULL;
	bitmap_release_region(l3pmu->used_mask, hwc->idx, order);

	/* Propagate changes to the userspace mapping. */
	perf_event_update_userpage(event);
}
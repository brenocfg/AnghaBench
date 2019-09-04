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
struct hw_perf_event {int idx; int state; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct l3cache_pmu {struct perf_event** events; int /*<<< orphan*/  used_mask; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  L3_NUM_COUNTERS ; 
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int bitmap_find_free_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ event_uses_long_counter (struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  qcom_l3_cache__event_start (struct perf_event*,int /*<<< orphan*/ ) ; 
 struct l3cache_pmu* to_l3cache_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_l3_cache__event_add(struct perf_event *event, int flags)
{
	struct l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;
	int order = event_uses_long_counter(event) ? 1 : 0;
	int idx;

	/*
	 * Try to allocate a counter.
	 */
	idx = bitmap_find_free_region(l3pmu->used_mask, L3_NUM_COUNTERS, order);
	if (idx < 0)
		/* The counters are all in use. */
		return -EAGAIN;

	hwc->idx = idx;
	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	l3pmu->events[idx] = event;

	if (flags & PERF_EF_START)
		qcom_l3_cache__event_start(event, 0);

	/* Propagate changes to the userspace mapping. */
	perf_event_update_userpage(event);

	return 0;
}
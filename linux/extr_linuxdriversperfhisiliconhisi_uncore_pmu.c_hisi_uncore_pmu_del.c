#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hw_perf_event {size_t idx; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** hw_events; } ;
struct hisi_pmu {TYPE_1__ pmu_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  hisi_uncore_pmu_clear_event_idx (struct hisi_pmu*,size_t) ; 
 int /*<<< orphan*/  hisi_uncore_pmu_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct hisi_pmu* to_hisi_pmu (int /*<<< orphan*/ ) ; 

void hisi_uncore_pmu_del(struct perf_event *event, int flags)
{
	struct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;

	hisi_uncore_pmu_stop(event, PERF_EF_UPDATE);
	hisi_uncore_pmu_clear_event_idx(hisi_pmu, hwc->idx);
	perf_event_update_userpage(event);
	hisi_pmu->pmu_events.hw_events[hwc->idx] = NULL;
}
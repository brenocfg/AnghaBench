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
typedef  int /*<<< orphan*/  u64 ;
struct hw_perf_event {int state; int /*<<< orphan*/  prev_count; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct hisi_pmu {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_counter ) (struct hisi_pmu*,struct hw_perf_event*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int PERF_EF_RELOAD ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  hisi_uncore_pmu_enable_event (struct perf_event*) ; 
 int /*<<< orphan*/  hisi_uncore_pmu_set_event_period (struct perf_event*) ; 
 int /*<<< orphan*/  local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct hisi_pmu*,struct hw_perf_event*,int /*<<< orphan*/ ) ; 
 struct hisi_pmu* to_hisi_pmu (int /*<<< orphan*/ ) ; 

void hisi_uncore_pmu_start(struct perf_event *event, int flags)
{
	struct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;

	if (WARN_ON_ONCE(!(hwc->state & PERF_HES_STOPPED)))
		return;

	WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));
	hwc->state = 0;
	hisi_uncore_pmu_set_event_period(event);

	if (flags & PERF_EF_RELOAD) {
		u64 prev_raw_count =  local64_read(&hwc->prev_count);

		hisi_pmu->ops->write_counter(hisi_pmu, hwc, prev_raw_count);
	}

	hisi_uncore_pmu_enable_event(event);
	perf_event_update_userpage(event);
}
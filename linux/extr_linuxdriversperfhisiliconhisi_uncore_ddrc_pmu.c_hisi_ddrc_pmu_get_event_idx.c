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
struct hw_perf_event {int dummy; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct TYPE_2__ {unsigned long* used_mask; } ;
struct hisi_pmu {TYPE_1__ pmu_events; } ;

/* Variables and functions */
 int EAGAIN ; 
 int GET_DDRC_EVENTID (struct hw_perf_event*) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 struct hisi_pmu* to_hisi_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_ddrc_pmu_get_event_idx(struct perf_event *event)
{
	struct hisi_pmu *ddrc_pmu = to_hisi_pmu(event->pmu);
	unsigned long *used_mask = ddrc_pmu->pmu_events.used_mask;
	struct hw_perf_event *hwc = &event->hw;
	/* For DDRC PMU, we use event code as counter index */
	int idx = GET_DDRC_EVENTID(hwc);

	if (test_bit(idx, used_mask))
		return -EAGAIN;

	set_bit(idx, used_mask);

	return idx;
}
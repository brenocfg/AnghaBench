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
struct xgene_pmu_dev {int /*<<< orphan*/ ** pmu_counter_event; } ;
struct hw_perf_event {size_t idx; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CNTR (struct perf_event*) ; 
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 int /*<<< orphan*/  clear_avail_cntr (struct xgene_pmu_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 struct xgene_pmu_dev* to_pmu_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_perf_stop (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_perf_del(struct perf_event *event, int flags)
{
	struct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	struct hw_perf_event *hw = &event->hw;

	xgene_perf_stop(event, PERF_EF_UPDATE);

	/* clear the assigned counter */
	clear_avail_cntr(pmu_dev, GET_CNTR(event));

	perf_event_update_userpage(event);
	pmu_dev->pmu_counter_event[hw->idx] = NULL;
}
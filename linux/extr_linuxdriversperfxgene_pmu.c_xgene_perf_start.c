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
struct xgene_pmu_dev {struct xgene_pmu* parent; } ;
struct xgene_pmu {TYPE_1__* ops; } ;
struct hw_perf_event {int state; int /*<<< orphan*/  prev_count; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_counter ) (struct xgene_pmu_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CNTR (struct perf_event*) ; 
 int PERF_EF_RELOAD ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  local64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct xgene_pmu_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xgene_pmu_dev* to_pmu_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_perf_enable_event (struct perf_event*) ; 
 int /*<<< orphan*/  xgene_perf_event_set_period (struct perf_event*) ; 

__attribute__((used)) static void xgene_perf_start(struct perf_event *event, int flags)
{
	struct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	struct xgene_pmu *xgene_pmu = pmu_dev->parent;
	struct hw_perf_event *hw = &event->hw;

	if (WARN_ON_ONCE(!(hw->state & PERF_HES_STOPPED)))
		return;

	WARN_ON_ONCE(!(hw->state & PERF_HES_UPTODATE));
	hw->state = 0;

	xgene_perf_event_set_period(event);

	if (flags & PERF_EF_RELOAD) {
		u64 prev_raw_count =  local64_read(&hw->prev_count);

		xgene_pmu->ops->write_counter(pmu_dev, GET_CNTR(event),
					      prev_raw_count);
	}

	xgene_perf_enable_event(event);
	perf_event_update_userpage(event);
}
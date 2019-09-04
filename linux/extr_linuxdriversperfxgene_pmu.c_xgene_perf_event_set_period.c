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
typedef  unsigned long long u64 ;
struct xgene_pmu_dev {struct xgene_pmu* parent; } ;
struct xgene_pmu {TYPE_1__* ops; } ;
struct hw_perf_event {int /*<<< orphan*/  idx; int /*<<< orphan*/  prev_count; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_counter ) (struct xgene_pmu_dev*,int /*<<< orphan*/ ,unsigned long long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  stub1 (struct xgene_pmu_dev*,int /*<<< orphan*/ ,unsigned long long) ; 
 struct xgene_pmu_dev* to_pmu_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_perf_event_set_period(struct perf_event *event)
{
	struct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	struct xgene_pmu *xgene_pmu = pmu_dev->parent;
	struct hw_perf_event *hw = &event->hw;
	/*
	 * For 32 bit counter, it has a period of 2^32. To account for the
	 * possibility of extreme interrupt latency we program for a period of
	 * half that. Hopefully, we can handle the interrupt before another 2^31
	 * events occur and the counter overtakes its previous value.
	 * For 64 bit counter, we don't expect it overflow.
	 */
	u64 val = 1ULL << 31;

	local64_set(&hw->prev_count, val);
	xgene_pmu->ops->write_counter(pmu_dev, hw->idx, val);
}
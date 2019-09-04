#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int idx; int /*<<< orphan*/  config_base; } ;
struct perf_event {TYPE_2__ hw; TYPE_1__* pmu; } ;
struct dsu_pmu {int /*<<< orphan*/  pmu_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dsu_pmu_set_event (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dsu_pmu_counter_valid (struct dsu_pmu*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void dsu_pmu_set_event(struct dsu_pmu *dsu_pmu,
					struct perf_event *event)
{
	int idx = event->hw.idx;
	unsigned long flags;

	if (!dsu_pmu_counter_valid(dsu_pmu, idx)) {
		dev_err(event->pmu->dev,
			"Trying to set invalid counter %d\n", idx);
		return;
	}

	raw_spin_lock_irqsave(&dsu_pmu->pmu_lock, flags);
	__dsu_pmu_set_event(idx, event->hw.config_base);
	raw_spin_unlock_irqrestore(&dsu_pmu->pmu_lock, flags);
}
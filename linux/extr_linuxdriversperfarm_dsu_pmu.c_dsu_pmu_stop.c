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
struct TYPE_2__ {int state; int /*<<< orphan*/  idx; } ;
struct perf_event {TYPE_1__ hw; int /*<<< orphan*/  pmu; } ;
struct dsu_pmu {int dummy; } ;

/* Variables and functions */
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  dsu_pmu_disable_counter (struct dsu_pmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsu_pmu_event_update (struct perf_event*) ; 
 struct dsu_pmu* to_dsu_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsu_pmu_stop(struct perf_event *event, int pmu_flags)
{
	struct dsu_pmu *dsu_pmu = to_dsu_pmu(event->pmu);

	if (event->hw.state & PERF_HES_STOPPED)
		return;
	dsu_pmu_disable_counter(dsu_pmu, event->hw.idx);
	dsu_pmu_event_update(event);
	event->hw.state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
}
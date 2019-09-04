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
struct perf_event {int /*<<< orphan*/  pmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  hrtimer; } ;
struct arm_ccn {TYPE_1__ dt; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EF_UPDATE ; 
 scalar_t__ arm_ccn_pmu_active_counters (struct arm_ccn*) ; 
 int /*<<< orphan*/  arm_ccn_pmu_event_release (struct perf_event*) ; 
 int /*<<< orphan*/  arm_ccn_pmu_event_stop (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 struct arm_ccn* pmu_to_arm_ccn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_ccn_pmu_event_del(struct perf_event *event, int flags)
{
	struct arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);

	arm_ccn_pmu_event_stop(event, PERF_EF_UPDATE);

	arm_ccn_pmu_event_release(event);

	if (!ccn->irq && arm_ccn_pmu_active_counters(ccn) == 0)
		hrtimer_cancel(&ccn->dt.hrtimer);
}
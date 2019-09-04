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
struct hw_perf_event {int /*<<< orphan*/  state; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int /*<<< orphan*/  PERF_HES_STOPPED ; 
 int /*<<< orphan*/  arm_ccn_pmu_event_update (struct perf_event*) ; 
 int /*<<< orphan*/  arm_ccn_pmu_xp_dt_config (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_ccn_pmu_event_stop(struct perf_event *event, int flags)
{
	struct hw_perf_event *hw = &event->hw;

	/* Disable counting, setting the DT bus to pass-through mode */
	arm_ccn_pmu_xp_dt_config(event, 0);

	if (flags & PERF_EF_UPDATE)
		arm_ccn_pmu_event_update(event);

	hw->state |= PERF_HES_STOPPED;
}
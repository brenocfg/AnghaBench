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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int idx; int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_1__ hw; int /*<<< orphan*/  pmu; } ;
struct l3cache_pmu {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVSEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GANG_EN (int) ; 
 scalar_t__ L3_HML3_PM_CNTCTL (int) ; 
 scalar_t__ L3_HML3_PM_EVCNTR (int) ; 
 scalar_t__ L3_HML3_PM_EVTYPE (int) ; 
 scalar_t__ L3_M_BC_CNTENSET ; 
 scalar_t__ L3_M_BC_GANG ; 
 int /*<<< orphan*/  PMCNTENSET (int) ; 
 int /*<<< orphan*/  PMCNT_RESET ; 
 int /*<<< orphan*/  get_event_type (struct perf_event*) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct l3cache_pmu* to_l3cache_pmu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void qcom_l3_cache__64bit_counter_start(struct perf_event *event)
{
	struct l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	int idx = event->hw.idx;
	u32 evsel = get_event_type(event);
	u32 gang;

	/* Set the odd counter to count the overflows of the even counter */
	gang = readl_relaxed(l3pmu->regs + L3_M_BC_GANG);
	gang |= GANG_EN(idx + 1);
	writel_relaxed(gang, l3pmu->regs + L3_M_BC_GANG);

	/* Initialize the hardware counters and reset prev_count*/
	local64_set(&event->hw.prev_count, 0);
	writel_relaxed(0, l3pmu->regs + L3_HML3_PM_EVCNTR(idx + 1));
	writel_relaxed(0, l3pmu->regs + L3_HML3_PM_EVCNTR(idx));

	/*
	 * Set the event types, the upper half must use zero and the lower
	 * half the actual event type
	 */
	writel_relaxed(EVSEL(0), l3pmu->regs + L3_HML3_PM_EVTYPE(idx + 1));
	writel_relaxed(EVSEL(evsel), l3pmu->regs + L3_HML3_PM_EVTYPE(idx));

	/* Finally, enable the counters */
	writel_relaxed(PMCNT_RESET, l3pmu->regs + L3_HML3_PM_CNTCTL(idx + 1));
	writel_relaxed(PMCNTENSET(idx + 1), l3pmu->regs + L3_M_BC_CNTENSET);
	writel_relaxed(PMCNT_RESET, l3pmu->regs + L3_HML3_PM_CNTCTL(idx));
	writel_relaxed(PMCNTENSET(idx), l3pmu->regs + L3_M_BC_CNTENSET);
}
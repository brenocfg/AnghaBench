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
typedef  int u32 ;
struct TYPE_2__ {int idx; int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_1__ hw; int /*<<< orphan*/  pmu; } ;
struct l3cache_pmu {scalar_t__ regs; } ;

/* Variables and functions */
 int EVSEL (int) ; 
 scalar_t__ L3_HML3_PM_CNTCTL (int) ; 
 scalar_t__ L3_HML3_PM_EVCNTR (int) ; 
 scalar_t__ L3_HML3_PM_EVTYPE (int) ; 
 scalar_t__ L3_M_BC_CNTENSET ; 
 scalar_t__ L3_M_BC_INTENSET ; 
 scalar_t__ L3_M_BC_IRQCTL ; 
 int PMCNTENSET (int) ; 
 int PMCNT_RESET ; 
 int PMINTENSET (int) ; 
 int PMIRQONMSBEN (int) ; 
 int get_event_type (struct perf_event*) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 struct l3cache_pmu* to_l3cache_pmu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void qcom_l3_cache__32bit_counter_start(struct perf_event *event)
{
	struct l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	int idx = event->hw.idx;
	u32 evsel = get_event_type(event);
	u32 irqctl = readl_relaxed(l3pmu->regs + L3_M_BC_IRQCTL);

	/* Set the counter to assert the overflow IRQ on MSB toggling */
	writel_relaxed(irqctl | PMIRQONMSBEN(idx), l3pmu->regs + L3_M_BC_IRQCTL);

	/* Initialize the hardware counter and reset prev_count*/
	local64_set(&event->hw.prev_count, 0);
	writel_relaxed(0, l3pmu->regs + L3_HML3_PM_EVCNTR(idx));

	/* Set the event type */
	writel_relaxed(EVSEL(evsel), l3pmu->regs + L3_HML3_PM_EVTYPE(idx));

	/* Enable interrupt generation by this counter */
	writel_relaxed(PMINTENSET(idx), l3pmu->regs + L3_M_BC_INTENSET);

	/* Finally, enable the counter */
	writel_relaxed(PMCNT_RESET, l3pmu->regs + L3_HML3_PM_CNTCTL(idx));
	writel_relaxed(PMCNTENSET(idx), l3pmu->regs + L3_M_BC_CNTENSET);
}
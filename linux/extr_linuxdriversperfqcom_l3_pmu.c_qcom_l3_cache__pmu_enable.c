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
struct pmu {int dummy; } ;
struct l3cache_pmu {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_ENABLE ; 
 scalar_t__ L3_M_BC_CR ; 
 struct l3cache_pmu* to_l3cache_pmu (struct pmu*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void qcom_l3_cache__pmu_enable(struct pmu *pmu)
{
	struct l3cache_pmu *l3pmu = to_l3cache_pmu(pmu);

	/* Ensure the other programming commands are observed before enabling */
	wmb();

	writel_relaxed(BC_ENABLE, l3pmu->regs + L3_M_BC_CR);
}
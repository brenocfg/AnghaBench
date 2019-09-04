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
typedef  int /*<<< orphan*/  u32 ;
struct pmu {int dummy; } ;
struct dsu_pmu {int /*<<< orphan*/  pmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERPMCR_E ; 
 int /*<<< orphan*/  __dsu_pmu_read_pmcr () ; 
 int /*<<< orphan*/  __dsu_pmu_write_pmcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dsu_pmu* to_dsu_pmu (struct pmu*) ; 

__attribute__((used)) static void dsu_pmu_disable(struct pmu *pmu)
{
	u32 pmcr;
	unsigned long flags;
	struct dsu_pmu *dsu_pmu = to_dsu_pmu(pmu);

	raw_spin_lock_irqsave(&dsu_pmu->pmu_lock, flags);
	pmcr = __dsu_pmu_read_pmcr();
	pmcr &= ~CLUSTERPMCR_E;
	__dsu_pmu_write_pmcr(pmcr);
	raw_spin_unlock_irqrestore(&dsu_pmu->pmu_lock, flags);
}
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
struct xgene_pmu_dev {TYPE_1__* inf; } ;
struct TYPE_2__ {scalar_t__ csr; } ;

/* Variables and functions */
 scalar_t__ PMU_PMEVTYPER0 ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void
xgene_pmu_write_evttype(struct xgene_pmu_dev *pmu_dev, int idx, u32 val)
{
	writel(val, pmu_dev->inf->csr + PMU_PMEVTYPER0 + (4 * idx));
}
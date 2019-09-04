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
struct xgene_pmu {scalar_t__ pcppmu_csr; } ;

/* Variables and functions */
 scalar_t__ PCPPMU_INTMASK_REG ; 
 int /*<<< orphan*/  PCPPMU_V3_INTCLRMASK ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void xgene_pmu_v3_unmask_int(struct xgene_pmu *xgene_pmu)
{
	writel(PCPPMU_V3_INTCLRMASK,
	       xgene_pmu->pcppmu_csr + PCPPMU_INTMASK_REG);
}
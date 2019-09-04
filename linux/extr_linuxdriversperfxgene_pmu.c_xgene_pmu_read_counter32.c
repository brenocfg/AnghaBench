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
typedef  int /*<<< orphan*/  u64 ;
struct xgene_pmu_dev {TYPE_1__* inf; } ;
struct TYPE_2__ {scalar_t__ csr; } ;

/* Variables and functions */
 scalar_t__ PMU_PMEVCNTR0 ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline u64 xgene_pmu_read_counter32(struct xgene_pmu_dev *pmu_dev,
					   int idx)
{
	return readl(pmu_dev->inf->csr + PMU_PMEVCNTR0 + (4 * idx));
}
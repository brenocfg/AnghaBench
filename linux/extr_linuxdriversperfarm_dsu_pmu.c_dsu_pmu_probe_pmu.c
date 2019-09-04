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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct dsu_pmu {int num_counters; int /*<<< orphan*/  cpmceid_bitmap; } ;

/* Variables and functions */
 int CLUSTERPMCR_N_MASK ; 
 int CLUSTERPMCR_N_SHIFT ; 
 int /*<<< orphan*/  DSU_PMU_MAX_COMMON_EVENTS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __dsu_pmu_read_pmceid (int) ; 
 int __dsu_pmu_read_pmcr () ; 
 int /*<<< orphan*/  bitmap_from_arr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsu_pmu_probe_pmu(struct dsu_pmu *dsu_pmu)
{
	u64 num_counters;
	u32 cpmceid[2];

	num_counters = (__dsu_pmu_read_pmcr() >> CLUSTERPMCR_N_SHIFT) &
						CLUSTERPMCR_N_MASK;
	/* We can only support up to 31 independent counters */
	if (WARN_ON(num_counters > 31))
		num_counters = 31;
	dsu_pmu->num_counters = num_counters;
	if (!dsu_pmu->num_counters)
		return;
	cpmceid[0] = __dsu_pmu_read_pmceid(0);
	cpmceid[1] = __dsu_pmu_read_pmceid(1);
	bitmap_from_arr32(dsu_pmu->cpmceid_bitmap, cpmceid,
			  DSU_PMU_MAX_COMMON_EVENTS);
}
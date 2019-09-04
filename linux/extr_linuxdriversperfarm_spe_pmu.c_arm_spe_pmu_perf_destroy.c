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
struct arm_spe_pmu {int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_pmu_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void arm_spe_pmu_perf_destroy(struct arm_spe_pmu *spe_pmu)
{
	perf_pmu_unregister(&spe_pmu->pmu);
}
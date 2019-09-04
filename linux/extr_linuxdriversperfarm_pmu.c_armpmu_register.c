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
struct arm_pmu {int /*<<< orphan*/  num_events; int /*<<< orphan*/  name; int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 struct arm_pmu* __oprofile_cpu_pmu ; 
 int /*<<< orphan*/  cpu_pmu_destroy (struct arm_pmu*) ; 
 int cpu_pmu_init (struct arm_pmu*) ; 
 int perf_pmu_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int armpmu_register(struct arm_pmu *pmu)
{
	int ret;

	ret = cpu_pmu_init(pmu);
	if (ret)
		return ret;

	ret = perf_pmu_register(&pmu->pmu, pmu->name, -1);
	if (ret)
		goto out_destroy;

	if (!__oprofile_cpu_pmu)
		__oprofile_cpu_pmu = pmu;

	pr_info("enabled with %s PMU driver, %d counters available\n",
		pmu->name, pmu->num_events);

	return 0;

out_destroy:
	cpu_pmu_destroy(pmu);
	return ret;
}
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
struct arm_pmu {int /*<<< orphan*/  (* stop ) (struct arm_pmu*) ;int /*<<< orphan*/  supported_cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (struct arm_pmu*) ; 
 struct arm_pmu* to_arm_pmu (struct pmu*) ; 

__attribute__((used)) static void armpmu_disable(struct pmu *pmu)
{
	struct arm_pmu *armpmu = to_arm_pmu(pmu);

	/* For task-bound events we may be called on other CPUs */
	if (!cpumask_test_cpu(smp_processor_id(), &armpmu->supported_cpus))
		return;

	armpmu->stop(armpmu);
}
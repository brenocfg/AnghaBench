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
struct platform_device {int dummy; } ;
struct hisi_pmu {int /*<<< orphan*/  node; int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_PERF_ARM_HISI_HHA_ONLINE ; 
 int /*<<< orphan*/  cpuhp_state_remove_instance (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_pmu_unregister (int /*<<< orphan*/ *) ; 
 struct hisi_pmu* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int hisi_hha_pmu_remove(struct platform_device *pdev)
{
	struct hisi_pmu *hha_pmu = platform_get_drvdata(pdev);

	perf_pmu_unregister(&hha_pmu->pmu);
	cpuhp_state_remove_instance(CPUHP_AP_PERF_ARM_HISI_HHA_ONLINE,
				    &hha_pmu->node);

	return 0;
}
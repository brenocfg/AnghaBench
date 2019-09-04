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
struct hisi_pmu {int ccl_id; int sccl_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_read_sccl_and_ccl_id (int*,int*) ; 

__attribute__((used)) static bool hisi_pmu_cpu_is_associated_pmu(struct hisi_pmu *hisi_pmu)
{
	int sccl_id, ccl_id;

	if (hisi_pmu->ccl_id == -1) {
		/* If CCL_ID is -1, the PMU only shares the same SCCL */
		hisi_read_sccl_and_ccl_id(&sccl_id, NULL);

		return sccl_id == hisi_pmu->sccl_id;
	}

	hisi_read_sccl_and_ccl_id(&sccl_id, &ccl_id);

	return sccl_id == hisi_pmu->sccl_id && ccl_id == hisi_pmu->ccl_id;
}
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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hw_perf_event {int /*<<< orphan*/  idx; } ;
struct hisi_pmu {scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ hisi_l3c_pmu_get_counter_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_uncore_pmu_counter_valid (struct hisi_pmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 

__attribute__((used)) static u64 hisi_l3c_pmu_read_counter(struct hisi_pmu *l3c_pmu,
				     struct hw_perf_event *hwc)
{
	u32 idx = hwc->idx;

	if (!hisi_uncore_pmu_counter_valid(l3c_pmu, idx)) {
		dev_err(l3c_pmu->dev, "Unsupported event index:%d!\n", idx);
		return 0;
	}

	/* Read 64-bits and the upper 16 bits are RAZ */
	return readq(l3c_pmu->base + hisi_l3c_pmu_get_counter_offset(idx));
}
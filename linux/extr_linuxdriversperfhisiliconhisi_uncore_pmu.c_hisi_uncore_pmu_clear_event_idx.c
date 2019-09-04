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
struct TYPE_2__ {int /*<<< orphan*/  used_mask; } ;
struct hisi_pmu {TYPE_1__ pmu_events; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hisi_uncore_pmu_counter_valid (struct hisi_pmu*,int) ; 

__attribute__((used)) static void hisi_uncore_pmu_clear_event_idx(struct hisi_pmu *hisi_pmu, int idx)
{
	if (!hisi_uncore_pmu_counter_valid(hisi_pmu, idx)) {
		dev_err(hisi_pmu->dev, "Unsupported event index:%d!\n", idx);
		return;
	}

	clear_bit(idx, hisi_pmu->pmu_events.used_mask);
}
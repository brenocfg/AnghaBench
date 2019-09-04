#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmu {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  used_mask; } ;
struct hisi_pmu {TYPE_2__* ops; int /*<<< orphan*/  num_counters; TYPE_1__ pmu_events; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* start_counters ) (struct hisi_pmu*) ;} ;

/* Variables and functions */
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hisi_pmu*) ; 
 struct hisi_pmu* to_hisi_pmu (struct pmu*) ; 

void hisi_uncore_pmu_enable(struct pmu *pmu)
{
	struct hisi_pmu *hisi_pmu = to_hisi_pmu(pmu);
	int enabled = bitmap_weight(hisi_pmu->pmu_events.used_mask,
				    hisi_pmu->num_counters);

	if (!enabled)
		return;

	hisi_pmu->ops->start_counters(hisi_pmu);
}
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
struct pmu {int dummy; } ;
struct hisi_pmu {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop_counters ) (struct hisi_pmu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hisi_pmu*) ; 
 struct hisi_pmu* to_hisi_pmu (struct pmu*) ; 

void hisi_uncore_pmu_disable(struct pmu *pmu)
{
	struct hisi_pmu *hisi_pmu = to_hisi_pmu(pmu);

	hisi_pmu->ops->stop_counters(hisi_pmu);
}
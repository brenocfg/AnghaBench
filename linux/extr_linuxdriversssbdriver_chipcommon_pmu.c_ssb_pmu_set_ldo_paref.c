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
struct ssb_chipcommon {TYPE_1__* dev; } ;
struct ssb_bus {int chip_id; } ;
struct TYPE_2__ {struct ssb_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_CHIPCO_PMU_MINRES_MSK ; 
 int SSB_PMURES_4312_PA_REF_LDO ; 
 int SSB_PMURES_4328_PA_REF_LDO ; 
 int SSB_PMURES_5354_PA_REF_LDO ; 
 int /*<<< orphan*/  chipco_mask32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chipco_read32 (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipco_set32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 

void ssb_pmu_set_ldo_paref(struct ssb_chipcommon *cc, bool on)
{
	struct ssb_bus *bus = cc->dev->bus;
	int ldo;

	switch (bus->chip_id) {
	case 0x4312:
		ldo = SSB_PMURES_4312_PA_REF_LDO;
		break;
	case 0x4328:
		ldo = SSB_PMURES_4328_PA_REF_LDO;
		break;
	case 0x5354:
		ldo = SSB_PMURES_5354_PA_REF_LDO;
		break;
	default:
		return;
	}

	if (on)
		chipco_set32(cc, SSB_CHIPCO_PMU_MINRES_MSK, 1 << ldo);
	else
		chipco_mask32(cc, SSB_CHIPCO_PMU_MINRES_MSK, ~(1 << ldo));
	chipco_read32(cc, SSB_CHIPCO_PMU_MINRES_MSK); //SPEC FIXME found via mmiotrace - dummy read?
}
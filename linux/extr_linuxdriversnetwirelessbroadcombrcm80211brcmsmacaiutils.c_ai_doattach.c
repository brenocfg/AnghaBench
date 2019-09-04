#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct si_pub {int /*<<< orphan*/  boardtype; int /*<<< orphan*/  boardvendor; int /*<<< orphan*/  chippkg; int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; } ;
struct si_info {int /*<<< orphan*/  pcibus; struct bcma_bus* icbus; struct si_pub pub; } ;
struct bcma_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  vendor; } ;
struct TYPE_5__ {int /*<<< orphan*/  pkg; int /*<<< orphan*/  rev; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {struct bcma_device* core; } ;
struct bcma_bus {TYPE_3__ boardinfo; TYPE_2__ chipinfo; TYPE_1__ drv_cc; int /*<<< orphan*/  host_pci; } ;

/* Variables and functions */
 int CC_CAP_PMU ; 
 int /*<<< orphan*/  CHIPCREGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ai_buscore_setup (struct si_info*,struct bcma_device*) ; 
 int ai_get_cccaps (struct si_pub*) ; 
 int /*<<< orphan*/  bcma_write32 (struct bcma_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiopulldown ; 
 int /*<<< orphan*/  gpiopullup ; 
 int /*<<< orphan*/  si_pmu_measure_alpclk (struct si_pub*) ; 

__attribute__((used)) static struct si_info *ai_doattach(struct si_info *sii,
				   struct bcma_bus *pbus)
{
	struct si_pub *sih = &sii->pub;
	struct bcma_device *cc;

	sii->icbus = pbus;
	sii->pcibus = pbus->host_pci;

	/* switch to Chipcommon core */
	cc = pbus->drv_cc.core;

	sih->chip = pbus->chipinfo.id;
	sih->chiprev = pbus->chipinfo.rev;
	sih->chippkg = pbus->chipinfo.pkg;
	sih->boardvendor = pbus->boardinfo.vendor;
	sih->boardtype = pbus->boardinfo.type;

	if (!ai_buscore_setup(sii, cc))
		goto exit;

	/* === NVRAM, clock is ready === */
	bcma_write32(cc, CHIPCREGOFFS(gpiopullup), 0);
	bcma_write32(cc, CHIPCREGOFFS(gpiopulldown), 0);

	/* PMU specific initializations */
	if (ai_get_cccaps(sih) & CC_CAP_PMU) {
		(void)si_pmu_measure_alpclk(sih);
	}

	return sii;

 exit:

	return NULL;
}
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
typedef  int u32 ;
struct ctlr_info {int discovery_polling; TYPE_2__* pdev; } ;
struct ReportExtendedLUNdata {TYPE_1__* LUN; int /*<<< orphan*/  LUNListLength; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ device_type; int /*<<< orphan*/  lunid; } ;

/* Variables and functions */
 scalar_t__ BMIC_DEVICE_TYPE_CONTROLLER ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int get_unaligned_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_disable_rld_caching (struct ctlr_info*) ; 
 int /*<<< orphan*/  is_hba_lunid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpsa_ext_ctrl_present(struct ctlr_info *h,
	struct ReportExtendedLUNdata *physdev)
{
	u32 nphysicals;
	int i;

	if (h->discovery_polling)
		return;

	nphysicals = (get_unaligned_be32(physdev->LUNListLength) / 24) + 1;

	for (i = 0; i < nphysicals; i++) {
		if (physdev->LUN[i].device_type ==
			BMIC_DEVICE_TYPE_CONTROLLER
			&& !is_hba_lunid(physdev->LUN[i].lunid)) {
			dev_info(&h->pdev->dev,
				"External controller present, activate discovery polling and disable rld caching\n");
			hpsa_disable_rld_caching(h);
			h->discovery_polling = 1;
			break;
		}
	}
}
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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ gen; } ;
struct TYPE_4__ {TYPE_1__ sb_type; } ;

/* Variables and functions */
 scalar_t__ AMD_CHIPSET_TAISHAN ; 
 scalar_t__ AMD_CHIPSET_YANGTZE ; 
 TYPE_2__ amd_chipset ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usb_amd_find_chipset_info () ; 

int usb_hcd_amd_remote_wakeup_quirk(struct pci_dev *pdev)
{
	/* Make sure amd chipset type has already been initialized */
	usb_amd_find_chipset_info();
	if (amd_chipset.sb_type.gen == AMD_CHIPSET_YANGTZE ||
	    amd_chipset.sb_type.gen == AMD_CHIPSET_TAISHAN) {
		dev_dbg(&pdev->dev, "QUIRK: Enable AMD remote wakeup fix\n");
		return 1;
	}
	return 0;
}
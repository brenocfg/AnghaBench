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
struct aac_dev {int msi_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  ODR_R; int /*<<< orphan*/  ODR_MSI; } ;

/* Variables and functions */
 TYPE_1__ MUnit ; 
 int SRC_MSI_READ_MASK ; 
 int SRC_ODR_SHIFT ; 
 int src_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aac_src_get_sync_status(struct aac_dev *dev)
{
	int msix_val = 0;
	int legacy_val = 0;

	msix_val = src_readl(dev, MUnit.ODR_MSI) & SRC_MSI_READ_MASK ? 1 : 0;

	if (!dev->msi_enabled) {
		/*
		 * if Legacy int status indicates cmd is not complete
		 * sample MSIx register to see if it indiactes cmd complete,
		 * if yes set the controller in MSIx mode and consider cmd
		 * completed
		 */
		legacy_val = src_readl(dev, MUnit.ODR_R) >> SRC_ODR_SHIFT;
		if (!(legacy_val & 1) && msix_val)
			dev->msi_enabled = 1;
		return legacy_val;
	}

	return msix_val;
}
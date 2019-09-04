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
struct TYPE_2__ {unsigned long driver_data; scalar_t__ class_mask; scalar_t__ class; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  subvendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct xen_pcibk_config_quirk {struct pci_dev* pdev; TYPE_1__ devid; } ;
struct pci_dev {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct xen_pcibk_config_quirk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_quirk (struct xen_pcibk_config_quirk*) ; 

int xen_pcibk_config_quirks_init(struct pci_dev *dev)
{
	struct xen_pcibk_config_quirk *quirk;
	int ret = 0;

	quirk = kzalloc(sizeof(*quirk), GFP_KERNEL);
	if (!quirk) {
		ret = -ENOMEM;
		goto out;
	}

	quirk->devid.vendor = dev->vendor;
	quirk->devid.device = dev->device;
	quirk->devid.subvendor = dev->subsystem_vendor;
	quirk->devid.subdevice = dev->subsystem_device;
	quirk->devid.class = 0;
	quirk->devid.class_mask = 0;
	quirk->devid.driver_data = 0UL;

	quirk->pdev = dev;

	register_quirk(quirk);
out:
	return ret;
}
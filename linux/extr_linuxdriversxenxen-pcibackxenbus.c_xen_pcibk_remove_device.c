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
struct xen_pcibk_device {TYPE_1__* xdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  otherend_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCI_DEVFN (int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 struct pci_dev* xen_pcibk_get_pci_dev (struct xen_pcibk_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_pcibk_release_pci_dev (struct xen_pcibk_device*,struct pci_dev*,int) ; 
 int /*<<< orphan*/  xen_unregister_device_domain_owner (struct pci_dev*) ; 

__attribute__((used)) static int xen_pcibk_remove_device(struct xen_pcibk_device *pdev,
				 int domain, int bus, int slot, int func)
{
	int err = 0;
	struct pci_dev *dev;

	dev_dbg(&pdev->xdev->dev, "removing dom %x bus %x slot %x func %x\n",
		domain, bus, slot, func);

	dev = xen_pcibk_get_pci_dev(pdev, domain, bus, PCI_DEVFN(slot, func));
	if (!dev) {
		err = -EINVAL;
		dev_dbg(&pdev->xdev->dev, "Couldn't locate PCI device "
			"(%04x:%02x:%02x.%d)! not owned by this domain\n",
			domain, bus, slot, func);
		goto out;
	}

	dev_dbg(&dev->dev, "unregistering for %d\n", pdev->xdev->otherend_id);
	xen_unregister_device_domain_owner(dev);

	/* N.B. This ends up calling pcistub_put_pci_dev which ends up
	 * doing the FLR. */
	xen_pcibk_release_pci_dev(pdev, dev, true /* use the lock. */);

out:
	return err;
}
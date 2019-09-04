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
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct pci_dev* pcistub_get_pci_dev_by_slot (struct xen_pcibk_device*,int,int,int,int) ; 
 int /*<<< orphan*/  xen_find_device_domain_owner (struct pci_dev*) ; 
 int xen_pcibk_add_pci_dev (struct xen_pcibk_device*,struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_pcibk_publish_pci_dev ; 
 scalar_t__ xen_register_device_domain_owner (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_unregister_device_domain_owner (struct pci_dev*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (TYPE_1__*,int,char*,int,int,int,int) ; 

__attribute__((used)) static int xen_pcibk_export_device(struct xen_pcibk_device *pdev,
				 int domain, int bus, int slot, int func,
				 int devid)
{
	struct pci_dev *dev;
	int err = 0;

	dev_dbg(&pdev->xdev->dev, "exporting dom %x bus %x slot %x func %x\n",
		domain, bus, slot, func);

	dev = pcistub_get_pci_dev_by_slot(pdev, domain, bus, slot, func);
	if (!dev) {
		err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Couldn't locate PCI device "
				 "(%04x:%02x:%02x.%d)! "
				 "perhaps already in-use?",
				 domain, bus, slot, func);
		goto out;
	}

	err = xen_pcibk_add_pci_dev(pdev, dev, devid,
				    xen_pcibk_publish_pci_dev);
	if (err)
		goto out;

	dev_info(&dev->dev, "registering for %d\n", pdev->xdev->otherend_id);
	if (xen_register_device_domain_owner(dev,
					     pdev->xdev->otherend_id) != 0) {
		dev_err(&dev->dev, "Stealing ownership from dom%d.\n",
			xen_find_device_domain_owner(dev));
		xen_unregister_device_domain_owner(dev);
		xen_register_device_domain_owner(dev, pdev->xdev->otherend_id);
	}

	/* TODO: It'd be nice to export a bridge and have all of its children
	 * get exported with it. This may be best done in xend (which will
	 * have to calculate resource usage anyway) but we probably want to
	 * put something in here to ensure that if a bridge gets given to a
	 * driver domain, that all devices under that bridge are not given
	 * to other driver domains (as he who controls the bridge can disable
	 * it and stop the other devices from working).
	 */
out:
	return err;
}
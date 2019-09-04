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
struct pcifront_device {TYPE_1__* xdev; } ;
struct pci_bus {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pci_bus_add_devices (struct pci_bus*) ; 
 struct pci_bus* pci_find_bus (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pci_walk_bus (struct pci_bus*,int /*<<< orphan*/ ,struct pcifront_device*) ; 
 int /*<<< orphan*/  pcifront_claim_resource ; 
 int pcifront_scan_bus (struct pcifront_device*,unsigned int,unsigned int,struct pci_bus*) ; 
 int pcifront_scan_root (struct pcifront_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int pcifront_rescan_root(struct pcifront_device *pdev,
				   unsigned int domain, unsigned int bus)
{
	int err;
	struct pci_bus *b;

#ifndef CONFIG_PCI_DOMAINS
	if (domain != 0) {
		dev_err(&pdev->xdev->dev,
			"PCI Root in non-zero PCI Domain! domain=%d\n", domain);
		dev_err(&pdev->xdev->dev,
			"Please compile with CONFIG_PCI_DOMAINS\n");
		return -EINVAL;
	}
#endif

	dev_info(&pdev->xdev->dev, "Rescanning PCI Frontend Bus %04x:%02x\n",
		 domain, bus);

	b = pci_find_bus(domain, bus);
	if (!b)
		/* If the bus is unknown, create it. */
		return pcifront_scan_root(pdev, domain, bus);

	err = pcifront_scan_bus(pdev, domain, bus, b);

	/* Claim resources before going "live" with our devices */
	pci_walk_bus(b, pcifront_claim_resource, pdev);

	/* Create SysFS and notify udev of the devices. Aka: "going live" */
	pci_bus_add_devices(b);

	return err;
}
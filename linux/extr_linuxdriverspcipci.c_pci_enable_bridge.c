#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  is_busmaster; } ;

/* Variables and functions */
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,int) ; 
 scalar_t__ pci_is_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 struct pci_dev* pci_upstream_bridge (struct pci_dev*) ; 

__attribute__((used)) static void pci_enable_bridge(struct pci_dev *dev)
{
	struct pci_dev *bridge;
	int retval;

	bridge = pci_upstream_bridge(dev);
	if (bridge)
		pci_enable_bridge(bridge);

	if (pci_is_enabled(dev)) {
		if (!dev->is_busmaster)
			pci_set_master(dev);
		return;
	}

	retval = pci_enable_device(dev);
	if (retval)
		pci_err(dev, "Error enabling bridge (%d), continuing\n",
			retval);
	pci_set_master(dev);
}
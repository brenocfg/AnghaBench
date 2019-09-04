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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 unsigned long TYPE_PCI1753 ; 
 unsigned long TYPE_PCI1753E ; 
 int inb (unsigned long) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 scalar_t__ pci_request_region (struct pci_dev*,int,char*) ; 
 int pci_resource_start (struct pci_dev*,int) ; 

__attribute__((used)) static unsigned long pci_dio_override_cardtype(struct pci_dev *pcidev,
					       unsigned long cardtype)
{
	/*
	 * Change cardtype from TYPE_PCI1753 to TYPE_PCI1753E if expansion
	 * board available.  Need to enable PCI device and request the main
	 * registers PCI BAR temporarily to perform the test.
	 */
	if (cardtype != TYPE_PCI1753)
		return cardtype;
	if (pci_enable_device(pcidev) < 0)
		return cardtype;
	if (pci_request_region(pcidev, 2, "adv_pci_dio") == 0) {
		/*
		 * This test is based on Advantech's "advdaq" driver source
		 * (which declares its module licence as "GPL" although the
		 * driver source does not include a "COPYING" file).
		 */
		unsigned long reg = pci_resource_start(pcidev, 2) + 53;

		outb(0x05, reg);
		if ((inb(reg) & 0x07) == 0x02) {
			outb(0x02, reg);
			if ((inb(reg) & 0x07) == 0x05)
				cardtype = TYPE_PCI1753E;
		}
		pci_release_region(pcidev, 2);
	}
	pci_disable_device(pcidev);
	return cardtype;
}
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
typedef  int u_short ;
struct sym_chip {int features; } ;
struct sym_device {struct pci_dev* pdev; struct sym_chip chip; } ;
struct pci_dev {scalar_t__ device; int revision; } ;

/* Variables and functions */
 int ENODEV ; 
 int FE_66MHZ ; 
 int FE_CLSE ; 
 int FE_WRIE ; 
 scalar_t__ PCI_DEVICE_ID_NCR_53C896 ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int PCI_STATUS_66MHZ ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_set_mwi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sym_set_workarounds(struct sym_device *device)
{
	struct sym_chip *chip = &device->chip;
	struct pci_dev *pdev = device->pdev;
	u_short status_reg;

	/*
	 *  (ITEM 12 of a DEL about the 896 I haven't yet).
	 *  We must ensure the chip will use WRITE AND INVALIDATE.
	 *  The revision number limit is for now arbitrary.
	 */
	if (pdev->device == PCI_DEVICE_ID_NCR_53C896 && pdev->revision < 0x4) {
		chip->features	|= (FE_WRIE | FE_CLSE);
	}

	/* If the chip can do Memory Write Invalidate, enable it */
	if (chip->features & FE_WRIE) {
		if (pci_set_mwi(pdev))
			return -ENODEV;
	}

	/*
	 *  Work around for errant bit in 895A. The 66Mhz
	 *  capable bit is set erroneously. Clear this bit.
	 *  (Item 1 DEL 533)
	 *
	 *  Make sure Config space and Features agree.
	 *
	 *  Recall: writes are not normal to status register -
	 *  write a 1 to clear and a 0 to leave unchanged.
	 *  Can only reset bits.
	 */
	pci_read_config_word(pdev, PCI_STATUS, &status_reg);
	if (chip->features & FE_66MHZ) {
		if (!(status_reg & PCI_STATUS_66MHZ))
			chip->features &= ~FE_66MHZ;
	} else {
		if (status_reg & PCI_STATUS_66MHZ) {
			status_reg = PCI_STATUS_66MHZ;
			pci_write_config_word(pdev, PCI_STATUS, status_reg);
			pci_read_config_word(pdev, PCI_STATUS, &status_reg);
		}
	}

	return 0;
}
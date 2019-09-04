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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_DEVSTA ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_capability_write_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pci_aer_clear_device_status(struct pci_dev *dev)
{
	u16 sta;

	pcie_capability_read_word(dev, PCI_EXP_DEVSTA, &sta);
	pcie_capability_write_word(dev, PCI_EXP_DEVSTA, sta);
}
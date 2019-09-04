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
 int /*<<< orphan*/  PCI_BRIDGE_CONTROL ; 
 int /*<<< orphan*/  PCI_BRIDGE_CTL_BUS_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssleep (int) ; 

void pci_reset_secondary_bus(struct pci_dev *dev)
{
	u16 ctrl;

	pci_read_config_word(dev, PCI_BRIDGE_CONTROL, &ctrl);
	ctrl |= PCI_BRIDGE_CTL_BUS_RESET;
	pci_write_config_word(dev, PCI_BRIDGE_CONTROL, ctrl);

	/*
	 * PCI spec v3.0 7.6.4.2 requires minimum Trst of 1ms.  Double
	 * this to 2ms to ensure that we meet the minimum requirement.
	 */
	msleep(2);

	ctrl &= ~PCI_BRIDGE_CTL_BUS_RESET;
	pci_write_config_word(dev, PCI_BRIDGE_CONTROL, ctrl);

	/*
	 * Trhfa for conventional PCI is 2^25 clock cycles.
	 * Assuming a minimum 33MHz clock this results in a 1s
	 * delay before we can consider subordinate devices to
	 * be re-initialized.  PCIe has some ways to shorten this,
	 * but we don't make use of them yet.
	 */
	ssleep(1);
}
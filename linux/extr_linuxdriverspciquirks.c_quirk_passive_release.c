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
 int /*<<< orphan*/  PCI_DEVICE_ID_INTEL_82371SB_0 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,unsigned char*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,unsigned char) ; 

__attribute__((used)) static void quirk_passive_release(struct pci_dev *dev)
{
	struct pci_dev *d = NULL;
	unsigned char dlc;

	/*
	 * We have to make sure a particular bit is set in the PIIX3
	 * ISA bridge, so we have to go out and find it.
	 */
	while ((d = pci_get_device(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82371SB_0, d))) {
		pci_read_config_byte(d, 0x82, &dlc);
		if (!(dlc & 1<<1)) {
			pci_info(d, "PIIX3: Enabling Passive Release\n");
			dlc |= 1<<1;
			pci_write_config_byte(d, 0x82, dlc);
		}
	}
}
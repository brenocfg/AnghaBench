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
typedef  int u8 ;
struct pci_dev {scalar_t__ hdr_type; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CAP_ID_EA ; 
 int PCI_EA_FIRST_ENT ; 
 scalar_t__ PCI_EA_NUM_ENT ; 
 int PCI_EA_NUM_ENT_MASK ; 
 scalar_t__ PCI_HEADER_TYPE_BRIDGE ; 
 int /*<<< orphan*/  pci_bus_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int pci_ea_read (struct pci_dev*,int) ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 

void pci_ea_init(struct pci_dev *dev)
{
	int ea;
	u8 num_ent;
	int offset;
	int i;

	/* find PCI EA capability in list */
	ea = pci_find_capability(dev, PCI_CAP_ID_EA);
	if (!ea)
		return;

	/* determine the number of entries */
	pci_bus_read_config_byte(dev->bus, dev->devfn, ea + PCI_EA_NUM_ENT,
					&num_ent);
	num_ent &= PCI_EA_NUM_ENT_MASK;

	offset = ea + PCI_EA_FIRST_ENT;

	/* Skip DWORD 2 for type 1 functions */
	if (dev->hdr_type == PCI_HEADER_TYPE_BRIDGE)
		offset += 4;

	/* parse each EA entry */
	for (i = 0; i < num_ent; ++i)
		offset = pci_ea_read(dev, offset);
}
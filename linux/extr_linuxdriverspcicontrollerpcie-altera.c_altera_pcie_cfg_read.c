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
typedef  int u32 ;
struct pci_bus {int /*<<< orphan*/  number; struct altera_pcie* sysdata; } ;
struct altera_pcie {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int /*<<< orphan*/  PCI_SLOT (unsigned int) ; 
 int _altera_pcie_cfg_read (struct altera_pcie*,int /*<<< orphan*/ ,unsigned int,int,int,int*) ; 
 scalar_t__ altera_pcie_hide_rc_bar (struct pci_bus*,unsigned int,int) ; 
 int /*<<< orphan*/  altera_pcie_valid_device (struct altera_pcie*,struct pci_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int altera_pcie_cfg_read(struct pci_bus *bus, unsigned int devfn,
				int where, int size, u32 *value)
{
	struct altera_pcie *pcie = bus->sysdata;

	if (altera_pcie_hide_rc_bar(bus, devfn, where))
		return PCIBIOS_BAD_REGISTER_NUMBER;

	if (!altera_pcie_valid_device(pcie, bus, PCI_SLOT(devfn))) {
		*value = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	return _altera_pcie_cfg_read(pcie, bus->number, devfn, where, size,
				     value);
}
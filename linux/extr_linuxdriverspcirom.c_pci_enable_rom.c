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
struct resource {int flags; } ;
struct pci_dev {int /*<<< orphan*/  rom_base_reg; int /*<<< orphan*/  bus; struct resource* resource; } ;
struct pci_bus_region {int start; } ;

/* Variables and functions */
 int IORESOURCE_ROM_SHADOW ; 
 int PCI_ROM_ADDRESS_ENABLE ; 
 int PCI_ROM_ADDRESS_MASK ; 
 size_t PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcibios_resource_to_bus (int /*<<< orphan*/ ,struct pci_bus_region*,struct resource*) ; 

int pci_enable_rom(struct pci_dev *pdev)
{
	struct resource *res = &pdev->resource[PCI_ROM_RESOURCE];
	struct pci_bus_region region;
	u32 rom_addr;

	if (!res->flags)
		return -1;

	/* Nothing to enable if we're using a shadow copy in RAM */
	if (res->flags & IORESOURCE_ROM_SHADOW)
		return 0;

	/*
	 * Ideally pci_update_resource() would update the ROM BAR address,
	 * and we would only set the enable bit here.  But apparently some
	 * devices have buggy ROM BARs that read as zero when disabled.
	 */
	pcibios_resource_to_bus(pdev->bus, &region, res);
	pci_read_config_dword(pdev, pdev->rom_base_reg, &rom_addr);
	rom_addr &= ~PCI_ROM_ADDRESS_MASK;
	rom_addr |= region.start | PCI_ROM_ADDRESS_ENABLE;
	pci_write_config_dword(pdev, pdev->rom_base_reg, rom_addr);
	return 0;
}
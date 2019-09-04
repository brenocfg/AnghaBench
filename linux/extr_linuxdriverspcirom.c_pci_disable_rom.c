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
typedef  int /*<<< orphan*/  u32 ;
struct resource {int flags; } ;
struct pci_dev {int /*<<< orphan*/  rom_base_reg; struct resource* resource; } ;

/* Variables and functions */
 int IORESOURCE_ROM_SHADOW ; 
 int /*<<< orphan*/  PCI_ROM_ADDRESS_ENABLE ; 
 size_t PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pci_disable_rom(struct pci_dev *pdev)
{
	struct resource *res = &pdev->resource[PCI_ROM_RESOURCE];
	u32 rom_addr;

	if (res->flags & IORESOURCE_ROM_SHADOW)
		return;

	pci_read_config_dword(pdev, pdev->rom_base_reg, &rom_addr);
	rom_addr &= ~PCI_ROM_ADDRESS_ENABLE;
	pci_write_config_dword(pdev, pdev->rom_base_reg, rom_addr);
}
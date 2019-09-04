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
struct resource {int flags; } ;
struct pci_dev {int rom_base_reg; struct resource* resource; scalar_t__ is_virtfn; scalar_t__ non_compliant_bars; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int IORESOURCE_PREFETCH ; 
 int IORESOURCE_READONLY ; 
 int IORESOURCE_SIZEALIGN ; 
 unsigned int PCI_BASE_ADDRESS_0 ; 
 size_t PCI_ROM_RESOURCE ; 
 scalar_t__ __pci_read_base (struct pci_dev*,int /*<<< orphan*/ ,struct resource*,int) ; 
 int /*<<< orphan*/  pci_bar_mem32 ; 
 int /*<<< orphan*/  pci_bar_unknown ; 

__attribute__((used)) static void pci_read_bases(struct pci_dev *dev, unsigned int howmany, int rom)
{
	unsigned int pos, reg;

	if (dev->non_compliant_bars)
		return;

	/* Per PCIe r4.0, sec 9.3.4.1.11, the VF BARs are all RO Zero */
	if (dev->is_virtfn)
		return;

	for (pos = 0; pos < howmany; pos++) {
		struct resource *res = &dev->resource[pos];
		reg = PCI_BASE_ADDRESS_0 + (pos << 2);
		pos += __pci_read_base(dev, pci_bar_unknown, res, reg);
	}

	if (rom) {
		struct resource *res = &dev->resource[PCI_ROM_RESOURCE];
		dev->rom_base_reg = rom;
		res->flags = IORESOURCE_MEM | IORESOURCE_PREFETCH |
				IORESOURCE_READONLY | IORESOURCE_SIZEALIGN;
		__pci_read_base(dev, pci_bar_mem32, res, rom);
	}
}
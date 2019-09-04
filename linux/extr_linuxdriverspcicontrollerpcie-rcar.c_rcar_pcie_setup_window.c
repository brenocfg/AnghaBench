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
struct resource {int flags; int /*<<< orphan*/  start; } ;
struct rcar_pcie {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IO_SPACE ; 
 int PAR_ENABLE ; 
 int /*<<< orphan*/  PCIEPALR (int) ; 
 int /*<<< orphan*/  PCIEPAMR (int) ; 
 int /*<<< orphan*/  PCIEPAUR (int) ; 
 int /*<<< orphan*/  PCIEPTCTLR (int) ; 
 int SZ_128 ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_pio_to_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_pci_write_reg (struct rcar_pcie*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int roundup_pow_of_two (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_pcie_setup_window(int win, struct rcar_pcie *pcie,
				   struct resource *res)
{
	/* Setup PCIe address space mappings for each resource */
	resource_size_t size;
	resource_size_t res_start;
	u32 mask;

	rcar_pci_write_reg(pcie, 0x00000000, PCIEPTCTLR(win));

	/*
	 * The PAMR mask is calculated in units of 128Bytes, which
	 * keeps things pretty simple.
	 */
	size = resource_size(res);
	mask = (roundup_pow_of_two(size) / SZ_128) - 1;
	rcar_pci_write_reg(pcie, mask << 7, PCIEPAMR(win));

	if (res->flags & IORESOURCE_IO)
		res_start = pci_pio_to_address(res->start);
	else
		res_start = res->start;

	rcar_pci_write_reg(pcie, upper_32_bits(res_start), PCIEPAUR(win));
	rcar_pci_write_reg(pcie, lower_32_bits(res_start) & ~0x7F,
			   PCIEPALR(win));

	/* First resource is for IO */
	mask = PAR_ENABLE;
	if (res->flags & IORESOURCE_IO)
		mask |= IO_SPACE;

	rcar_pci_write_reg(pcie, mask, PCIEPTCTLR(win));
}
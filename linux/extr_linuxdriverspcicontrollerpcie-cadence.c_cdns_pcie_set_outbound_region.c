#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct cdns_pcie {TYPE_1__* mem_res; int /*<<< orphan*/  bus; scalar_t__ is_rc; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_CPU_ADDR0 (int) ; 
 int CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS (int) ; 
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_CPU_ADDR1 (int) ; 
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_DESC0 (int) ; 
 int CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN (int /*<<< orphan*/ ) ; 
 int CDNS_PCIE_AT_OB_REGION_DESC0_HARDCODED_RID ; 
 int CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_IO ; 
 int CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_MEM ; 
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_DESC1 (int) ; 
 int CDNS_PCIE_AT_OB_REGION_DESC1_BUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0 (int) ; 
 int CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_NBITS (int) ; 
 int /*<<< orphan*/  CDNS_PCIE_AT_OB_REGION_PCI_ADDR1 (int) ; 
 int GENMASK (int,int) ; 
 int /*<<< orphan*/  cdns_pcie_writel (struct cdns_pcie*,int /*<<< orphan*/ ,int) ; 
 unsigned long long fls64 (size_t) ; 
 int ilog2 (unsigned long long) ; 
 int lower_32_bits (unsigned long long) ; 
 int upper_32_bits (unsigned long long) ; 

void cdns_pcie_set_outbound_region(struct cdns_pcie *pcie, u8 fn,
				   u32 r, bool is_io,
				   u64 cpu_addr, u64 pci_addr, size_t size)
{
	/*
	 * roundup_pow_of_two() returns an unsigned long, which is not suited
	 * for 64bit values.
	 */
	u64 sz = 1ULL << fls64(size - 1);
	int nbits = ilog2(sz);
	u32 addr0, addr1, desc0, desc1;

	if (nbits < 8)
		nbits = 8;

	/* Set the PCI address */
	addr0 = CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_NBITS(nbits) |
		(lower_32_bits(pci_addr) & GENMASK(31, 8));
	addr1 = upper_32_bits(pci_addr);

	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR0(r), addr0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR1(r), addr1);

	/* Set the PCIe header descriptor */
	if (is_io)
		desc0 = CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_IO;
	else
		desc0 = CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_MEM;
	desc1 = 0;

	/*
	 * Whatever Bit [23] is set or not inside DESC0 register of the outbound
	 * PCIe descriptor, the PCI function number must be set into
	 * Bits [26:24] of DESC0 anyway.
	 *
	 * In Root Complex mode, the function number is always 0 but in Endpoint
	 * mode, the PCIe controller may support more than one function. This
	 * function number needs to be set properly into the outbound PCIe
	 * descriptor.
	 *
	 * Besides, setting Bit [23] is mandatory when in Root Complex mode:
	 * then the driver must provide the bus, resp. device, number in
	 * Bits [7:0] of DESC1, resp. Bits[31:27] of DESC0. Like the function
	 * number, the device number is always 0 in Root Complex mode.
	 *
	 * However when in Endpoint mode, we can clear Bit [23] of DESC0, hence
	 * the PCIe controller will use the captured values for the bus and
	 * device numbers.
	 */
	if (pcie->is_rc) {
		/* The device and function numbers are always 0. */
		desc0 |= CDNS_PCIE_AT_OB_REGION_DESC0_HARDCODED_RID |
			 CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN(0);
		desc1 |= CDNS_PCIE_AT_OB_REGION_DESC1_BUS(pcie->bus);
	} else {
		/*
		 * Use captured values for bus and device numbers but still
		 * need to set the function number.
		 */
		desc0 |= CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN(fn);
	}

	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_DESC0(r), desc0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_DESC1(r), desc1);

	/* Set the CPU address */
	cpu_addr -= pcie->mem_res->start;
	addr0 = CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS(nbits) |
		(lower_32_bits(cpu_addr) & GENMASK(31, 8));
	addr1 = upper_32_bits(cpu_addr);

	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR0(r), addr0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR1(r), addr1);
}
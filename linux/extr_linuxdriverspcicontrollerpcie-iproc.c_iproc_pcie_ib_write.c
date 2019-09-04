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
typedef  int u64 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct iproc_pcie_ib_map {scalar_t__ imap_window_offset; scalar_t__ imap_addr_offset; } ;
struct iproc_pcie {scalar_t__ base; struct iproc_pcie_ib_map* ib_map; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int IMAP_VALID ; 
 int /*<<< orphan*/  IPROC_PCIE_IARR0 ; 
 int /*<<< orphan*/  IPROC_PCIE_IMAP0 ; 
 int /*<<< orphan*/  MAP_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,...) ; 
 int ilog2 (int) ; 
 scalar_t__ iproc_pcie_reg_is_invalid (scalar_t__) ; 
 scalar_t__ iproc_pcie_reg_offset (struct iproc_pcie*,int /*<<< orphan*/ ) ; 
 int lower_32_bits (int) ; 
 int readl (scalar_t__) ; 
 int upper_32_bits (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int iproc_pcie_ib_write(struct iproc_pcie *pcie, int region_idx,
			       int size_idx, int nr_windows, u64 axi_addr,
			       u64 pci_addr, resource_size_t size)
{
	struct device *dev = pcie->dev;
	const struct iproc_pcie_ib_map *ib_map = &pcie->ib_map[region_idx];
	u16 iarr_offset, imap_offset;
	u32 val;
	int window_idx;

	iarr_offset = iproc_pcie_reg_offset(pcie,
				MAP_REG(IPROC_PCIE_IARR0, region_idx));
	imap_offset = iproc_pcie_reg_offset(pcie,
				MAP_REG(IPROC_PCIE_IMAP0, region_idx));
	if (iproc_pcie_reg_is_invalid(iarr_offset) ||
	    iproc_pcie_reg_is_invalid(imap_offset))
		return -EINVAL;

	dev_dbg(dev, "ib region [%d]: offset 0x%x axi %pap pci %pap\n",
		region_idx, iarr_offset, &axi_addr, &pci_addr);

	/*
	 * Program the IARR registers.  The upper 32-bit IARR register is
	 * always right after the lower 32-bit IARR register.
	 */
	writel(lower_32_bits(pci_addr) | BIT(size_idx),
	       pcie->base + iarr_offset);
	writel(upper_32_bits(pci_addr), pcie->base + iarr_offset + 4);

	dev_dbg(dev, "iarr lo 0x%x iarr hi 0x%x\n",
		readl(pcie->base + iarr_offset),
		readl(pcie->base + iarr_offset + 4));

	/*
	 * Now program the IMAP registers.  Each IARR region may have one or
	 * more IMAP windows.
	 */
	size >>= ilog2(nr_windows);
	for (window_idx = 0; window_idx < nr_windows; window_idx++) {
		val = readl(pcie->base + imap_offset);
		val |= lower_32_bits(axi_addr) | IMAP_VALID;
		writel(val, pcie->base + imap_offset);
		writel(upper_32_bits(axi_addr),
		       pcie->base + imap_offset + ib_map->imap_addr_offset);

		dev_dbg(dev, "imap window [%d] lo 0x%x hi 0x%x\n",
			window_idx, readl(pcie->base + imap_offset),
			readl(pcie->base + imap_offset +
			      ib_map->imap_addr_offset));

		imap_offset += ib_map->imap_window_offset;
		axi_addr += size;
	}

	return 0;
}
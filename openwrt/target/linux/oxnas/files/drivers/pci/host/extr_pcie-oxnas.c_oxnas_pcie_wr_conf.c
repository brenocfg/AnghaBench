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
struct pci_bus {int /*<<< orphan*/  number; int /*<<< orphan*/  sysdata; } ;
struct oxnas_pcie {int /*<<< orphan*/  lock; scalar_t__ cfgbase; int /*<<< orphan*/  haslink; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 scalar_t__ PCI_SLOT (int) ; 
 unsigned int oxnas_pcie_cfg_to_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_out_lanes (struct oxnas_pcie*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct oxnas_pcie* sys_to_pcie (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int oxnas_pcie_wr_conf(struct pci_bus *bus, u32 devfn,
			      int where, int size, u32 val)
{
	unsigned long flags;
	struct oxnas_pcie *pcie = sys_to_pcie(bus->sysdata);
	unsigned offset;
	u32 value;
	u32 lanes;

	/* Only a single device per bus for PCIe point-to-point links */
	if (PCI_SLOT(devfn) > 0)
		return PCIBIOS_DEVICE_NOT_FOUND;

	if (!pcie->haslink)
		return PCIBIOS_DEVICE_NOT_FOUND;

	offset = oxnas_pcie_cfg_to_offset(bus->sysdata, bus->number, devfn,
					  where);

	value = val << (8 * (where & 3));
	lanes = (0xf >> (4-size)) << (where & 3);
	/* it race with mem and io write, but the possibility is low, normally
	 * all config writes happens at driver initialize stage, wont interleave
	 * with others.
	 * and many pcie cards use dword (4bytes) access mem/io access only,
	 * so not bother to copy that ugly work-around now. */
	spin_lock_irqsave(&pcie->lock, flags);
	set_out_lanes(pcie, lanes);
	writel_relaxed(value, pcie->cfgbase + offset);
	set_out_lanes(pcie, 0xf);
	spin_unlock_irqrestore(&pcie->lock, flags);

	return PCIBIOS_SUCCESSFUL;
}
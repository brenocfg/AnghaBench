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
struct rcar_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN2_PCIEPHYADDR ; 
 int /*<<< orphan*/  GEN2_PCIEPHYCTRL ; 
 int /*<<< orphan*/  GEN2_PCIEPHYDATA ; 
 int /*<<< orphan*/  rcar_pci_write_reg (struct rcar_pcie*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_pcie_phy_init_gen2(struct rcar_pcie *pcie)
{
	/*
	 * These settings come from the R-Car Series, 2nd Generation User's
	 * Manual, section 50.3.1 (2) Initialization of the physical layer.
	 */
	rcar_pci_write_reg(pcie, 0x000f0030, GEN2_PCIEPHYADDR);
	rcar_pci_write_reg(pcie, 0x00381203, GEN2_PCIEPHYDATA);
	rcar_pci_write_reg(pcie, 0x00000001, GEN2_PCIEPHYCTRL);
	rcar_pci_write_reg(pcie, 0x00000006, GEN2_PCIEPHYCTRL);

	rcar_pci_write_reg(pcie, 0x000f0054, GEN2_PCIEPHYADDR);
	/* The following value is for DC connection, no termination resistor */
	rcar_pci_write_reg(pcie, 0x13802007, GEN2_PCIEPHYDATA);
	rcar_pci_write_reg(pcie, 0x00000001, GEN2_PCIEPHYCTRL);
	rcar_pci_write_reg(pcie, 0x00000006, GEN2_PCIEPHYCTRL);

	return 0;
}
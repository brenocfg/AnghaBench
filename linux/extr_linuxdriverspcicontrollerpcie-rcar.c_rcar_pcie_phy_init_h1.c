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
 int /*<<< orphan*/  phy_write_reg (struct rcar_pcie*,int,int,int,int) ; 

__attribute__((used)) static int rcar_pcie_phy_init_h1(struct rcar_pcie *pcie)
{
	/* Initialize the phy */
	phy_write_reg(pcie, 0, 0x42, 0x1, 0x0EC34191);
	phy_write_reg(pcie, 1, 0x42, 0x1, 0x0EC34180);
	phy_write_reg(pcie, 0, 0x43, 0x1, 0x00210188);
	phy_write_reg(pcie, 1, 0x43, 0x1, 0x00210188);
	phy_write_reg(pcie, 0, 0x44, 0x1, 0x015C0014);
	phy_write_reg(pcie, 1, 0x44, 0x1, 0x015C0014);
	phy_write_reg(pcie, 1, 0x4C, 0x1, 0x786174A0);
	phy_write_reg(pcie, 1, 0x4D, 0x1, 0x048000BB);
	phy_write_reg(pcie, 0, 0x51, 0x1, 0x079EC062);
	phy_write_reg(pcie, 0, 0x52, 0x1, 0x20000000);
	phy_write_reg(pcie, 1, 0x52, 0x1, 0x20000000);
	phy_write_reg(pcie, 1, 0x56, 0x1, 0x00003806);

	phy_write_reg(pcie, 0, 0x60, 0x1, 0x004B03A5);
	phy_write_reg(pcie, 0, 0x64, 0x1, 0x3F0F1F0F);
	phy_write_reg(pcie, 0, 0x66, 0x1, 0x00008000);

	return 0;
}
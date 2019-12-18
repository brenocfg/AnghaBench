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
typedef  int u16 ;
struct mii_bus {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ag71xx_mdio_mii_write (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int mk_high_addr (int) ; 
 int mk_phy_addr (int) ; 
 int mk_phy_reg (int) ; 

__attribute__((used)) static void __ar7240sw_reg_write(struct mii_bus *mii, u32 reg, u32 val)
{
	unsigned long flags;
	u16 phy_addr;
	u16 phy_reg;

	reg = (reg & 0xfffffffc) >> 2;
	phy_addr = mk_phy_addr(reg);
	phy_reg = mk_phy_reg(reg);

	local_irq_save(flags);
	ag71xx_mdio_mii_write(mii->priv, 0x1f, 0x10, mk_high_addr(reg));
	ag71xx_mdio_mii_write(mii->priv, phy_addr, phy_reg + 1, (val >> 16));
	ag71xx_mdio_mii_write(mii->priv, phy_addr, phy_reg, (val & 0xffff));
	local_irq_restore(flags);
}
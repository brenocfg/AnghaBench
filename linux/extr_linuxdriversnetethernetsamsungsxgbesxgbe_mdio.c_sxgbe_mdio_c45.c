#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sxgbe_priv_data {TYPE_2__* hw; scalar_t__ ioaddr; } ;
struct TYPE_3__ {scalar_t__ addr; } ;
struct TYPE_4__ {TYPE_1__ mii; } ;

/* Variables and functions */
 int /*<<< orphan*/  sxgbe_mdio_ctrl_data (struct sxgbe_priv_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sxgbe_mdio_c45(struct sxgbe_priv_data *sp, u32 cmd, int phyaddr,
			   int phyreg, u16 phydata)
{
	u32 reg;

	/* set mdio address register */
	reg = ((phyreg >> 16) & 0x1f) << 21;
	reg |= (phyaddr << 16) | (phyreg & 0xffff);
	writel(reg, sp->ioaddr + sp->hw->mii.addr);

	sxgbe_mdio_ctrl_data(sp, cmd, phydata);
}
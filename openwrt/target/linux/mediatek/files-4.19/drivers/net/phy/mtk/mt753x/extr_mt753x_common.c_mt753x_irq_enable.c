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
struct gsw_mt753x {int (* mii_read ) (struct gsw_mt753x*,int,int /*<<< orphan*/ ) ;int phy_link_sts; } ;

/* Variables and functions */
 int BIT (int) ; 
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int MT753X_NUM_PHYS ; 
 int /*<<< orphan*/  SYS_INT_EN ; 
 int /*<<< orphan*/  mt753x_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct gsw_mt753x*,int,int /*<<< orphan*/ ) ; 

void mt753x_irq_enable(struct gsw_mt753x *gsw)
{
	u32 val;
	int i;

	/* Record initial PHY link status */
	for (i = 0; i < MT753X_NUM_PHYS; i++) {
		val = gsw->mii_read(gsw, i, MII_BMSR);
		if (val & BMSR_LSTATUS)
			gsw->phy_link_sts |= BIT(i);
	}

	val = BIT(MT753X_NUM_PHYS) - 1;

	mt753x_reg_write(gsw, SYS_INT_EN, val);
}
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
typedef  int /*<<< orphan*/  u16 ;
struct gsw_mt753x {int phy_base; int /*<<< orphan*/  mii_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_CMD_WRITE ; 
 int /*<<< orphan*/  MDIO_ST_C22 ; 
 int MT753X_NUM_PHYS ; 
 int MT753X_SMI_ADDR_MASK ; 
 int /*<<< orphan*/  mt753x_mii_rw (struct gsw_mt753x*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mt753x_mii_write(struct gsw_mt753x *gsw, int phy, int reg, u16 val)
{
	if (phy < MT753X_NUM_PHYS)
		phy = (gsw->phy_base + phy) & MT753X_SMI_ADDR_MASK;

	mutex_lock(&gsw->mii_lock);
	mt753x_mii_rw(gsw, phy, reg, val, MDIO_CMD_WRITE, MDIO_ST_C22);
	mutex_unlock(&gsw->mii_lock);
}
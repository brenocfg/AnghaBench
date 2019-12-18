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
struct gsw_mt753x {int phy_base; int /*<<< orphan*/  host_bus; } ;

/* Variables and functions */
 int MT753X_NUM_PHYS ; 
 int MT753X_SMI_ADDR_MASK ; 
 int mdiobus_read (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mt7530_mii_read(struct gsw_mt753x *gsw, int phy, int reg)
{
	if (phy < MT753X_NUM_PHYS)
		phy = (gsw->phy_base + phy) & MT753X_SMI_ADDR_MASK;

	return mdiobus_read(gsw->host_bus, phy, reg);
}
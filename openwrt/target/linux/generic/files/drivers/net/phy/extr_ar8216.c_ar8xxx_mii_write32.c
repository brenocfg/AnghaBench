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
typedef  int u32 ;
typedef  int u16 ;
struct mii_bus {int /*<<< orphan*/  (* write ) (struct mii_bus*,int,int,int) ;} ;
struct ar8xxx_priv {TYPE_1__* chip; struct mii_bus* mii_bus; } ;
struct TYPE_2__ {scalar_t__ mii_lo_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mii_bus*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct mii_bus*,int,int,int) ; 
 int /*<<< orphan*/  stub3 (struct mii_bus*,int,int,int) ; 
 int /*<<< orphan*/  stub4 (struct mii_bus*,int,int,int) ; 

void
ar8xxx_mii_write32(struct ar8xxx_priv *priv, int phy_id, int regnum, u32 val)
{
	struct mii_bus *bus = priv->mii_bus;
	u16 lo, hi;

	lo = val & 0xffff;
	hi = (u16) (val >> 16);

	if (priv->chip->mii_lo_first)
	{
		bus->write(bus, phy_id, regnum, lo);
		bus->write(bus, phy_id, regnum + 1, hi);
	} else {
		bus->write(bus, phy_id, regnum + 1, hi);
		bus->write(bus, phy_id, regnum, lo);
	}
}
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
struct mii_bus {int (* read ) (struct mii_bus*,int,int) ;} ;
struct ar8xxx_priv {struct mii_bus* mii_bus; } ;

/* Variables and functions */
 int stub1 (struct mii_bus*,int,int) ; 
 int stub2 (struct mii_bus*,int,int) ; 

u32
ar8xxx_mii_read32(struct ar8xxx_priv *priv, int phy_id, int regnum)
{
	struct mii_bus *bus = priv->mii_bus;
	u16 lo, hi;

	lo = bus->read(bus, phy_id, regnum);
	hi = bus->read(bus, phy_id, regnum + 1);

	return (hi << 16) | lo;
}
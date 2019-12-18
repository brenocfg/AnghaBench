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
struct mii_bus {int /*<<< orphan*/  mdio_lock; int /*<<< orphan*/  (* write ) (struct mii_bus*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct ar8xxx_priv {struct mii_bus* mii_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ATH_DBG_ADDR ; 
 int /*<<< orphan*/  MII_ATH_DBG_DATA ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mii_bus*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mii_bus*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar8xxx_phy_dbg_write(struct ar8xxx_priv *priv, int phy_addr,
		     u16 dbg_addr, u16 dbg_data)
{
	struct mii_bus *bus = priv->mii_bus;

	mutex_lock(&bus->mdio_lock);
	bus->write(bus, phy_addr, MII_ATH_DBG_ADDR, dbg_addr);
	bus->write(bus, phy_addr, MII_ATH_DBG_DATA, dbg_data);
	mutex_unlock(&bus->mdio_lock);
}
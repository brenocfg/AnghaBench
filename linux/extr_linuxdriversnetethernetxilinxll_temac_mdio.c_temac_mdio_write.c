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
typedef  int u16 ;
struct temac_local {int /*<<< orphan*/  indirect_mutex; int /*<<< orphan*/  dev; } ;
struct mii_bus {struct temac_local* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  XTE_MGTDR_OFFSET ; 
 int /*<<< orphan*/  XTE_MIIMAI_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temac_indirect_out32 (struct temac_local*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int temac_mdio_write(struct mii_bus *bus, int phy_id, int reg, u16 val)
{
	struct temac_local *lp = bus->priv;

	dev_dbg(lp->dev, "temac_mdio_write(phy_id=%i, reg=%x, val=%x)\n",
		phy_id, reg, val);

	/* First write the desired value into the write data register
	 * and then write the address into the access initiator register
	 */
	mutex_lock(&lp->indirect_mutex);
	temac_indirect_out32(lp, XTE_MGTDR_OFFSET, val);
	temac_indirect_out32(lp, XTE_MIIMAI_OFFSET, (phy_id << 5) | reg);
	mutex_unlock(&lp->indirect_mutex);

	return 0;
}
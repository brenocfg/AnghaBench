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
struct mii_bus {struct ag71xx_mdio* priv; } ;
struct ag71xx_mdio {int /*<<< orphan*/  mii_regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_MII_ADDR ; 
 int /*<<< orphan*/  AG71XX_REG_MII_CMD ; 
 int /*<<< orphan*/  AG71XX_REG_MII_STATUS ; 
 int /*<<< orphan*/  DBG (char*,int,int,int) ; 
 int MII_ADDR_SHIFT ; 
 int MII_CMD_READ ; 
 int MII_CMD_WRITE ; 
 int ag71xx_mdio_wait_busy (struct ag71xx_mdio*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ag71xx_mdio_mii_read(struct mii_bus *bus, int addr, int reg)
{
	struct ag71xx_mdio *am = bus->priv;
	int err;
	int ret;

	err = ag71xx_mdio_wait_busy(am);
	if (err)
		return 0xffff;

	regmap_write(am->mii_regmap, AG71XX_REG_MII_CMD, MII_CMD_WRITE);
	regmap_write(am->mii_regmap, AG71XX_REG_MII_ADDR,
			((addr & 0xff) << MII_ADDR_SHIFT) | (reg & 0xff));
	regmap_write(am->mii_regmap, AG71XX_REG_MII_CMD, MII_CMD_READ);

	err = ag71xx_mdio_wait_busy(am);
	if (err)
		return 0xffff;

	regmap_read(am->mii_regmap, AG71XX_REG_MII_STATUS, &ret);
	ret &= 0xffff;
	regmap_write(am->mii_regmap, AG71XX_REG_MII_CMD, MII_CMD_WRITE);

	DBG("mii_read: addr=%04x, reg=%04x, value=%04x\n", addr, reg, ret);

	return ret;
}
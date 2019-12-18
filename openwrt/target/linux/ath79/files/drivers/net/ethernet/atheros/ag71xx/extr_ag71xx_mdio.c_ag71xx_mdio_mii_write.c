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
struct mii_bus {struct ag71xx_mdio* priv; } ;
struct ag71xx_mdio {int /*<<< orphan*/  mii_regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_MII_ADDR ; 
 int /*<<< orphan*/  AG71XX_REG_MII_CTRL ; 
 int /*<<< orphan*/  DBG (char*,int,int,int) ; 
 int MII_ADDR_SHIFT ; 
 int /*<<< orphan*/  ag71xx_mdio_wait_busy (struct ag71xx_mdio*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ag71xx_mdio_mii_write(struct mii_bus *bus, int addr, int reg, u16 val)
{
	struct ag71xx_mdio *am = bus->priv;

	DBG("mii_write: addr=%04x, reg=%04x, value=%04x\n", addr, reg, val);

	regmap_write(am->mii_regmap, AG71XX_REG_MII_ADDR,
			((addr & 0xff) << MII_ADDR_SHIFT) | (reg & 0xff));
	regmap_write(am->mii_regmap, AG71XX_REG_MII_CTRL, val);

	ag71xx_mdio_wait_busy(am);

	return 0;
}
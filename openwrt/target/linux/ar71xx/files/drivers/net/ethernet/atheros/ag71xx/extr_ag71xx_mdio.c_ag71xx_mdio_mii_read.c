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
struct ag71xx_mdio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_MII_ADDR ; 
 int /*<<< orphan*/  AG71XX_REG_MII_CMD ; 
 int /*<<< orphan*/  AG71XX_REG_MII_STATUS ; 
 int /*<<< orphan*/  DBG (char*,int,int,int) ; 
 int MII_ADDR_SHIFT ; 
 int MII_CMD_READ ; 
 int MII_CMD_WRITE ; 
 int ag71xx_mdio_rr (struct ag71xx_mdio*,int /*<<< orphan*/ ) ; 
 int ag71xx_mdio_wait_busy (struct ag71xx_mdio*) ; 
 int /*<<< orphan*/  ag71xx_mdio_wr (struct ag71xx_mdio*,int /*<<< orphan*/ ,int) ; 

int ag71xx_mdio_mii_read(struct ag71xx_mdio *am, int addr, int reg)
{
	int err;
	int ret;

	err = ag71xx_mdio_wait_busy(am);
	if (err)
		return 0xffff;

	ag71xx_mdio_wr(am, AG71XX_REG_MII_CMD, MII_CMD_WRITE);
	ag71xx_mdio_wr(am, AG71XX_REG_MII_ADDR,
			((addr & 0xff) << MII_ADDR_SHIFT) | (reg & 0xff));
	ag71xx_mdio_wr(am, AG71XX_REG_MII_CMD, MII_CMD_READ);

	err = ag71xx_mdio_wait_busy(am);
	if (err)
		return 0xffff;

	ret = ag71xx_mdio_rr(am, AG71XX_REG_MII_STATUS) & 0xffff;
	ag71xx_mdio_wr(am, AG71XX_REG_MII_CMD, MII_CMD_WRITE);

	DBG("mii_read: addr=%04x, reg=%04x, value=%04x\n", addr, reg, ret);

	return ret;
}
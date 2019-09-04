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
struct niu {int /*<<< orphan*/  port; int /*<<< orphan*/  dev; int /*<<< orphan*/  phy_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM8704_PHYXS_DEV_ADDR ; 
 int BMCR_RESET ; 
 int ENODEV ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int mdio_read (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mdio_write (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm8704_reset(struct niu *np)
{
	int err, limit;

	err = mdio_read(np, np->phy_addr,
			BCM8704_PHYXS_DEV_ADDR, MII_BMCR);
	if (err < 0 || err == 0xffff)
		return err;
	err |= BMCR_RESET;
	err = mdio_write(np, np->phy_addr, BCM8704_PHYXS_DEV_ADDR,
			 MII_BMCR, err);
	if (err)
		return err;

	limit = 1000;
	while (--limit >= 0) {
		err = mdio_read(np, np->phy_addr,
				BCM8704_PHYXS_DEV_ADDR, MII_BMCR);
		if (err < 0)
			return err;
		if (!(err & BMCR_RESET))
			break;
	}
	if (limit < 0) {
		netdev_err(np->dev, "Port %u PHY will not reset (bmcr=%04x)\n",
			   np->port, (err & 0xffff));
		return -ENODEV;
	}
	return 0;
}
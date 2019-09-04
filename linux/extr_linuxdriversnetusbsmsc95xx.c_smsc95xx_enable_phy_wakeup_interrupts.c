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
struct mii_if_info {int /*<<< orphan*/  phy_id; } ;
struct usbnet {int /*<<< orphan*/  net; struct mii_if_info mii; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_INT_MASK ; 
 int /*<<< orphan*/  PHY_INT_SRC ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int smsc95xx_mdio_read_nopm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc95xx_mdio_write_nopm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsc95xx_enable_phy_wakeup_interrupts(struct usbnet *dev, u16 mask)
{
	struct mii_if_info *mii = &dev->mii;
	int ret;

	netdev_dbg(dev->net, "enabling PHY wakeup interrupts\n");

	/* read to clear */
	ret = smsc95xx_mdio_read_nopm(dev->net, mii->phy_id, PHY_INT_SRC);
	if (ret < 0)
		return ret;

	/* enable interrupt source */
	ret = smsc95xx_mdio_read_nopm(dev->net, mii->phy_id, PHY_INT_MASK);
	if (ret < 0)
		return ret;

	ret |= mask;

	smsc95xx_mdio_write_nopm(dev->net, mii->phy_id, PHY_INT_MASK, ret);

	return 0;
}
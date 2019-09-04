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
struct TYPE_2__ {int (* mdio_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int phy_id_mask; int reg_num_mask; int supports_gmii; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  (* mdio_write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  dev; } ;
struct usbnet {int /*<<< orphan*/  net; TYPE_1__ mii; } ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_ALL ; 
 int ADVERTISE_CSMA ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int BMCR_RESET ; 
 int EIO ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  PHY_INT_MASK ; 
 int PHY_INT_MASK_DEFAULT ; 
 int /*<<< orphan*/  PHY_INT_SRC ; 
 int /*<<< orphan*/  SMSC75XX_INTERNAL_PHY_ID ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  mii_nway_restart (TYPE_1__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int smsc75xx_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc75xx_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smsc75xx_phy_gig_workaround (struct usbnet*) ; 

__attribute__((used)) static int smsc75xx_phy_initialize(struct usbnet *dev)
{
	int bmcr, ret, timeout = 0;

	/* Initialize MII structure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_read = smsc75xx_mdio_read;
	dev->mii.mdio_write = smsc75xx_mdio_write;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.supports_gmii = 1;
	dev->mii.phy_id = SMSC75XX_INTERNAL_PHY_ID;

	/* reset phy and wait for reset to complete */
	smsc75xx_mdio_write(dev->net, dev->mii.phy_id, MII_BMCR, BMCR_RESET);

	do {
		msleep(10);
		bmcr = smsc75xx_mdio_read(dev->net, dev->mii.phy_id, MII_BMCR);
		if (bmcr < 0) {
			netdev_warn(dev->net, "Error reading MII_BMCR\n");
			return bmcr;
		}
		timeout++;
	} while ((bmcr & BMCR_RESET) && (timeout < 100));

	if (timeout >= 100) {
		netdev_warn(dev->net, "timeout on PHY Reset\n");
		return -EIO;
	}

	/* phy workaround for gig link */
	smsc75xx_phy_gig_workaround(dev);

	smsc75xx_mdio_write(dev->net, dev->mii.phy_id, MII_ADVERTISE,
		ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP |
		ADVERTISE_PAUSE_ASYM);
	smsc75xx_mdio_write(dev->net, dev->mii.phy_id, MII_CTRL1000,
		ADVERTISE_1000FULL);

	/* read and write to clear phy interrupt status */
	ret = smsc75xx_mdio_read(dev->net, dev->mii.phy_id, PHY_INT_SRC);
	if (ret < 0) {
		netdev_warn(dev->net, "Error reading PHY_INT_SRC\n");
		return ret;
	}

	smsc75xx_mdio_write(dev->net, dev->mii.phy_id, PHY_INT_SRC, 0xffff);

	smsc75xx_mdio_write(dev->net, dev->mii.phy_id, PHY_INT_MASK,
		PHY_INT_MASK_DEFAULT);
	mii_nway_restart(&dev->mii);

	netif_dbg(dev, ifup, dev->net, "phy initialised successfully\n");
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int phy_id_mask; int reg_num_mask; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  (* mdio_write ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  mdio_read; TYPE_2__* dev; } ;
struct usbnet {TYPE_3__ mii; TYPE_2__* net; TYPE_1__* driver_info; } ;
struct usb_interface {int dummy; } ;
struct TYPE_6__ {int needed_headroom; int needed_tailroom; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_5__ {unsigned long data; } ;

/* Variables and functions */
 int ADVERTISE_ALL ; 
 int ADVERTISE_CSMA ; 
 int ADVERTISE_PAUSE_CAP ; 
 int /*<<< orphan*/  AX88172_CMD_READ_NODE_ID ; 
 int /*<<< orphan*/  AX_CMD_WRITE_GPIOS ; 
 int /*<<< orphan*/  BMCR_RESET ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  asix_get_phy_addr (struct usbnet*) ; 
 int /*<<< orphan*/  asix_mdio_read ; 
 int /*<<< orphan*/  asix_mdio_write (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  asix_phy_reset (struct usbnet*,int /*<<< orphan*/ ) ; 
 int asix_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asix_set_netdev_dev_addr (struct usbnet*,int /*<<< orphan*/ *) ; 
 int asix_write_cmd (struct usbnet*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int asix_write_rx_ctl (struct usbnet*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax88172_ethtool_ops ; 
 int /*<<< orphan*/  ax88172_netdev_ops ; 
 int /*<<< orphan*/  mii_nway_restart (TYPE_3__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int ax88172_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int ret = 0;
	u8 buf[ETH_ALEN];
	int i;
	unsigned long gpio_bits = dev->driver_info->data;

	usbnet_get_endpoints(dev,intf);

	/* Toggle the GPIOs in a manufacturer/model specific way */
	for (i = 2; i >= 0; i--) {
		ret = asix_write_cmd(dev, AX_CMD_WRITE_GPIOS,
				(gpio_bits >> (i * 8)) & 0xff, 0, 0, NULL, 0);
		if (ret < 0)
			goto out;
		msleep(5);
	}

	ret = asix_write_rx_ctl(dev, 0x80, 0);
	if (ret < 0)
		goto out;

	/* Get the MAC address */
	ret = asix_read_cmd(dev, AX88172_CMD_READ_NODE_ID,
			    0, 0, ETH_ALEN, buf, 0);
	if (ret < 0) {
		netdev_dbg(dev->net, "read AX_CMD_READ_NODE_ID failed: %d\n",
			   ret);
		goto out;
	}

	asix_set_netdev_dev_addr(dev, buf);

	/* Initialize MII structure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_read = asix_mdio_read;
	dev->mii.mdio_write = asix_mdio_write;
	dev->mii.phy_id_mask = 0x3f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.phy_id = asix_get_phy_addr(dev);

	dev->net->netdev_ops = &ax88172_netdev_ops;
	dev->net->ethtool_ops = &ax88172_ethtool_ops;
	dev->net->needed_headroom = 4; /* cf asix_tx_fixup() */
	dev->net->needed_tailroom = 4; /* cf asix_tx_fixup() */

	asix_phy_reset(dev, BMCR_RESET);
	asix_mdio_write(dev->net, dev->mii.phy_id, MII_ADVERTISE,
		ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP);
	mii_nway_restart(&dev->mii);

	return 0;

out:
	return ret;
}
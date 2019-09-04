#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int phy_id_mask; int reg_num_mask; int supports_gmii; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; TYPE_3__* dev; } ;
struct usbnet {int rx_urb_size; int /*<<< orphan*/  driver_priv; TYPE_2__* driver_info; TYPE_3__* net; TYPE_1__ mii; } ;
struct usb_interface {int dummy; } ;
struct asix_common_private {int dummy; } ;
struct TYPE_6__ {scalar_t__ hard_header_len; scalar_t__ max_mtu; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_CMD_READ_NODE_ID ; 
 int AX_SWRESET_IPPD ; 
 int AX_SWRESET_PRL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int FLAG_FRAMING_AX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  asix_get_phy_addr (struct usbnet*) ; 
 int /*<<< orphan*/  asix_mdio_read ; 
 int /*<<< orphan*/  asix_mdio_write ; 
 int asix_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asix_set_netdev_dev_addr (struct usbnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asix_sw_reset (struct usbnet*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax88178_ethtool_ops ; 
 int /*<<< orphan*/  ax88178_netdev_ops ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int ax88178_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int ret;
	u8 buf[ETH_ALEN];

	usbnet_get_endpoints(dev,intf);

	/* Get the MAC address */
	ret = asix_read_cmd(dev, AX_CMD_READ_NODE_ID, 0, 0, ETH_ALEN, buf, 0);
	if (ret < 0) {
		netdev_dbg(dev->net, "Failed to read MAC address: %d\n", ret);
		return ret;
	}

	asix_set_netdev_dev_addr(dev, buf);

	/* Initialize MII structure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_read = asix_mdio_read;
	dev->mii.mdio_write = asix_mdio_write;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0xff;
	dev->mii.supports_gmii = 1;
	dev->mii.phy_id = asix_get_phy_addr(dev);

	dev->net->netdev_ops = &ax88178_netdev_ops;
	dev->net->ethtool_ops = &ax88178_ethtool_ops;
	dev->net->max_mtu = 16384 - (dev->net->hard_header_len + 4);

	/* Blink LEDS so users know driver saw dongle */
	asix_sw_reset(dev, 0, 0);
	msleep(150);

	asix_sw_reset(dev, AX_SWRESET_PRL | AX_SWRESET_IPPD, 0);
	msleep(150);

	/* Asix framing packs multiple eth frames into a 2K usb bulk transfer */
	if (dev->driver_info->flags & FLAG_FRAMING_AX) {
		/* hard_mtu  is still the default - the device does not support
		   jumbo eth frames */
		dev->rx_urb_size = 2048;
	}

	dev->driver_priv = kzalloc(sizeof(struct asix_common_private), GFP_KERNEL);
	if (!dev->driver_priv)
			return -ENOMEM;

	return 0;
}
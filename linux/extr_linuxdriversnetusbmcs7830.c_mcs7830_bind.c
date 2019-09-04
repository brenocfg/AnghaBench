#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int phy_id_mask; int reg_num_mask; int /*<<< orphan*/  phy_id; struct net_device* dev; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; } ;
struct usbnet {TYPE_2__ mii; scalar_t__ rx_urb_size; TYPE_1__* udev; struct net_device* net; } ;
struct usb_interface {int dummy; } ;
struct net_device {scalar_t__ dev_addr; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * ethtool_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ETH_FRAME_LEN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int mcs7830_apply_base_config (struct usbnet*) ; 
 int /*<<< orphan*/  mcs7830_data_set_multicast (struct net_device*) ; 
 int /*<<< orphan*/  mcs7830_ethtool_ops ; 
 int mcs7830_hif_get_mac_address (struct usbnet*,scalar_t__) ; 
 int /*<<< orphan*/  mcs7830_mdio_read ; 
 int /*<<< orphan*/  mcs7830_mdio_write ; 
 int /*<<< orphan*/  mcs7830_netdev_ops ; 
 int usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int mcs7830_bind(struct usbnet *dev, struct usb_interface *udev)
{
	struct net_device *net = dev->net;
	int ret;
	int retry;

	/* Initial startup: Gather MAC address setting from EEPROM */
	ret = -EINVAL;
	for (retry = 0; retry < 5 && ret; retry++)
		ret = mcs7830_hif_get_mac_address(dev, net->dev_addr);
	if (ret) {
		dev_warn(&dev->udev->dev, "Cannot read MAC address\n");
		goto out;
	}

	mcs7830_data_set_multicast(net);

	ret = mcs7830_apply_base_config(dev);
	if (ret)
		goto out;

	net->ethtool_ops = &mcs7830_ethtool_ops;
	net->netdev_ops = &mcs7830_netdev_ops;

	/* reserve space for the status byte on rx */
	dev->rx_urb_size = ETH_FRAME_LEN + 1;

	dev->mii.mdio_read = mcs7830_mdio_read;
	dev->mii.mdio_write = mcs7830_mdio_write;
	dev->mii.dev = net;
	dev->mii.phy_id_mask = 0x3f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.phy_id = *((u8 *) net->dev_addr + 1);

	ret = usbnet_get_endpoints(dev, udev);
out:
	return ret;
}
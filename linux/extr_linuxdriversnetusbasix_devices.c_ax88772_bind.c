#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_7__ {int phy_id_mask; int reg_num_mask; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; TYPE_4__* dev; } ;
struct usbnet {int rx_urb_size; struct asix_common_private* driver_priv; TYPE_3__* driver_info; TYPE_4__* net; TYPE_2__ mii; TYPE_1__* udev; } ;
struct usb_interface {int dummy; } ;
struct asix_common_private {void* suspend; int /*<<< orphan*/  resume; scalar_t__ presvd_phy_advertise; scalar_t__ presvd_phy_bmcr; } ;
struct TYPE_9__ {int needed_headroom; int needed_tailroom; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_8__ {int data; int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_AX88772_CHIPCODE ; 
 int /*<<< orphan*/  AX_CHIPCODE_MASK ; 
 int /*<<< orphan*/  AX_CMD_READ_EEPROM ; 
 int /*<<< orphan*/  AX_CMD_READ_NODE_ID ; 
 int /*<<< orphan*/  AX_CMD_STATMNGSTS_REG ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int FLAG_EEPROM_MAC ; 
 int FLAG_FRAMING_AX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  asix_get_phy_addr (struct usbnet*) ; 
 int asix_get_phyid (struct usbnet*) ; 
 int /*<<< orphan*/  asix_mdio_read ; 
 int /*<<< orphan*/  asix_mdio_write ; 
 int asix_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asix_set_netdev_dev_addr (struct usbnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ax88772_ethtool_ops ; 
 int ax88772_hw_reset (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax88772_netdev_ops ; 
 int /*<<< orphan*/  ax88772_resume ; 
 void* ax88772_suspend ; 
 int ax88772a_hw_reset (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax88772a_resume ; 
 int /*<<< orphan*/  eth_platform_get_mac_address (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifup ; 
 struct asix_common_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int ax88772_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int ret, i;
	u8 buf[ETH_ALEN], chipcode = 0;
	u32 phyid;
	struct asix_common_private *priv;

	usbnet_get_endpoints(dev, intf);

	/* Maybe the boot loader passed the MAC address via device tree */
	if (!eth_platform_get_mac_address(&dev->udev->dev, buf)) {
		netif_dbg(dev, ifup, dev->net,
			  "MAC address read from device tree");
	} else {
		/* Try getting the MAC address from EEPROM */
		if (dev->driver_info->data & FLAG_EEPROM_MAC) {
			for (i = 0; i < (ETH_ALEN >> 1); i++) {
				ret = asix_read_cmd(dev, AX_CMD_READ_EEPROM,
						    0x04 + i, 0, 2, buf + i * 2,
						    0);
				if (ret < 0)
					break;
			}
		} else {
			ret = asix_read_cmd(dev, AX_CMD_READ_NODE_ID,
					    0, 0, ETH_ALEN, buf, 0);
		}

		if (ret < 0) {
			netdev_dbg(dev->net, "Failed to read MAC address: %d\n",
				   ret);
			return ret;
		}
	}

	asix_set_netdev_dev_addr(dev, buf);

	/* Initialize MII structure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_read = asix_mdio_read;
	dev->mii.mdio_write = asix_mdio_write;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.phy_id = asix_get_phy_addr(dev);

	dev->net->netdev_ops = &ax88772_netdev_ops;
	dev->net->ethtool_ops = &ax88772_ethtool_ops;
	dev->net->needed_headroom = 4; /* cf asix_tx_fixup() */
	dev->net->needed_tailroom = 4; /* cf asix_tx_fixup() */

	asix_read_cmd(dev, AX_CMD_STATMNGSTS_REG, 0, 0, 1, &chipcode, 0);
	chipcode &= AX_CHIPCODE_MASK;

	ret = (chipcode == AX_AX88772_CHIPCODE) ? ax88772_hw_reset(dev, 0) :
						  ax88772a_hw_reset(dev, 0);

	if (ret < 0) {
		netdev_dbg(dev->net, "Failed to reset AX88772: %d\n", ret);
		return ret;
	}

	/* Read PHYID register *AFTER* the PHY was reset properly */
	phyid = asix_get_phyid(dev);
	netdev_dbg(dev->net, "PHYID=0x%08x\n", phyid);

	/* Asix framing packs multiple eth frames into a 2K usb bulk transfer */
	if (dev->driver_info->flags & FLAG_FRAMING_AX) {
		/* hard_mtu  is still the default - the device does not support
		   jumbo eth frames */
		dev->rx_urb_size = 2048;
	}

	dev->driver_priv = kzalloc(sizeof(struct asix_common_private), GFP_KERNEL);
	if (!dev->driver_priv)
		return -ENOMEM;

	priv = dev->driver_priv;

	priv->presvd_phy_bmcr = 0;
	priv->presvd_phy_advertise = 0;
	if (chipcode == AX_AX88772_CHIPCODE) {
		priv->resume = ax88772_resume;
		priv->suspend = ax88772_suspend;
	} else {
		priv->resume = ax88772a_resume;
		priv->suspend = ax88772_suspend;
	}

	return 0;
}
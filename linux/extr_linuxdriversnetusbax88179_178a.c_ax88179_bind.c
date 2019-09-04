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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_4__ {int phy_id_mask; int reg_num_mask; int phy_id; int supports_gmii; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; TYPE_1__* dev; } ;
struct usbnet {int rx_urb_size; TYPE_2__ mii; TYPE_1__* net; scalar_t__ data; } ;
struct usb_interface {int dummy; } ;
struct ethtool_eee {scalar_t__ advertised; } ;
struct ax88179_data {scalar_t__ eee_active; scalar_t__ eee_enabled; } ;
struct TYPE_3__ {int* perm_addr; int needed_headroom; int max_mtu; int features; int hw_features; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/ * AX88179_BULKIN_SIZE ; 
 int /*<<< orphan*/  AX_ACCESS_MAC ; 
 int /*<<< orphan*/  AX_CLK_SELECT ; 
 int AX_CLK_SELECT_ACS ; 
 int AX_CLK_SELECT_BCS ; 
 int AX_MEDIUM_FULL_DUPLEX ; 
 int AX_MEDIUM_GIGAMODE ; 
 int AX_MEDIUM_RECEIVE_EN ; 
 int AX_MEDIUM_RXFLOW_CTRLEN ; 
 int /*<<< orphan*/  AX_MEDIUM_STATUS_MODE ; 
 int AX_MEDIUM_TXFLOW_CTRLEN ; 
 int /*<<< orphan*/  AX_MONITOR_MOD ; 
 int AX_MONITOR_MODE_PMEPOL ; 
 int AX_MONITOR_MODE_PMETYPE ; 
 int AX_MONITOR_MODE_RWMP ; 
 int /*<<< orphan*/  AX_NODE_ID ; 
 int /*<<< orphan*/  AX_PAUSE_WATERLVL_HIGH ; 
 int /*<<< orphan*/  AX_PAUSE_WATERLVL_LOW ; 
 int /*<<< orphan*/  AX_PHYPWR_RSTCTL ; 
 int AX_PHYPWR_RSTCTL_IPRL ; 
 int /*<<< orphan*/  AX_RXCOE_CTL ; 
 int AX_RXCOE_IP ; 
 int AX_RXCOE_TCP ; 
 int AX_RXCOE_TCPV6 ; 
 int AX_RXCOE_UDP ; 
 int AX_RXCOE_UDPV6 ; 
 int /*<<< orphan*/  AX_RX_BULKIN_QCTRL ; 
 int /*<<< orphan*/  AX_RX_CTL ; 
 int AX_RX_CTL_AB ; 
 int AX_RX_CTL_AMALL ; 
 int AX_RX_CTL_AP ; 
 int AX_RX_CTL_DROPCRCERR ; 
 int AX_RX_CTL_IPE ; 
 int AX_RX_CTL_START ; 
 int /*<<< orphan*/  AX_TXCOE_CTL ; 
 int AX_TXCOE_IP ; 
 int AX_TXCOE_TCP ; 
 int AX_TXCOE_TCPV6 ; 
 int AX_TXCOE_UDP ; 
 int AX_TXCOE_UDPV6 ; 
 int ETH_ALEN ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  ax88179_disable_eee (struct usbnet*) ; 
 int /*<<< orphan*/  ax88179_ethtool_get_eee (struct usbnet*,struct ethtool_eee*) ; 
 int /*<<< orphan*/  ax88179_ethtool_ops ; 
 int /*<<< orphan*/  ax88179_ethtool_set_eee (struct usbnet*,struct ethtool_eee*) ; 
 int /*<<< orphan*/  ax88179_led_setting (struct usbnet*) ; 
 int /*<<< orphan*/  ax88179_mdio_read ; 
 int /*<<< orphan*/  ax88179_mdio_write ; 
 int /*<<< orphan*/  ax88179_netdev_ops ; 
 int /*<<< orphan*/  ax88179_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ax88179_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct ax88179_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_nway_restart (TYPE_2__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 
 int /*<<< orphan*/  usbnet_link_change (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ax88179_bind(struct usbnet *dev, struct usb_interface *intf)
{
	u8 buf[5];
	u16 *tmp16;
	u8 *tmp;
	struct ax88179_data *ax179_data = (struct ax88179_data *)dev->data;
	struct ethtool_eee eee_data;

	usbnet_get_endpoints(dev, intf);

	tmp16 = (u16 *)buf;
	tmp = (u8 *)buf;

	memset(ax179_data, 0, sizeof(*ax179_data));

	/* Power up ethernet PHY */
	*tmp16 = 0;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL, 2, 2, tmp16);
	*tmp16 = AX_PHYPWR_RSTCTL_IPRL;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_PHYPWR_RSTCTL, 2, 2, tmp16);
	msleep(200);

	*tmp = AX_CLK_SELECT_ACS | AX_CLK_SELECT_BCS;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_CLK_SELECT, 1, 1, tmp);
	msleep(100);

	ax88179_read_cmd(dev, AX_ACCESS_MAC, AX_NODE_ID, ETH_ALEN,
			 ETH_ALEN, dev->net->dev_addr);
	memcpy(dev->net->perm_addr, dev->net->dev_addr, ETH_ALEN);

	/* RX bulk configuration */
	memcpy(tmp, &AX88179_BULKIN_SIZE[0], 5);
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_RX_BULKIN_QCTRL, 5, 5, tmp);

	dev->rx_urb_size = 1024 * 20;

	*tmp = 0x34;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_PAUSE_WATERLVL_LOW, 1, 1, tmp);

	*tmp = 0x52;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_PAUSE_WATERLVL_HIGH,
			  1, 1, tmp);

	dev->net->netdev_ops = &ax88179_netdev_ops;
	dev->net->ethtool_ops = &ax88179_ethtool_ops;
	dev->net->needed_headroom = 8;
	dev->net->max_mtu = 4088;

	/* Initialize MII structure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_read = ax88179_mdio_read;
	dev->mii.mdio_write = ax88179_mdio_write;
	dev->mii.phy_id_mask = 0xff;
	dev->mii.reg_num_mask = 0xff;
	dev->mii.phy_id = 0x03;
	dev->mii.supports_gmii = 1;

	dev->net->features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			      NETIF_F_RXCSUM;

	dev->net->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				 NETIF_F_RXCSUM;

	/* Enable checksum offload */
	*tmp = AX_RXCOE_IP | AX_RXCOE_TCP | AX_RXCOE_UDP |
	       AX_RXCOE_TCPV6 | AX_RXCOE_UDPV6;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_RXCOE_CTL, 1, 1, tmp);

	*tmp = AX_TXCOE_IP | AX_TXCOE_TCP | AX_TXCOE_UDP |
	       AX_TXCOE_TCPV6 | AX_TXCOE_UDPV6;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTL, 1, 1, tmp);

	/* Configure RX control register => start operation */
	*tmp16 = AX_RX_CTL_DROPCRCERR | AX_RX_CTL_IPE | AX_RX_CTL_START |
		 AX_RX_CTL_AP | AX_RX_CTL_AMALL | AX_RX_CTL_AB;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_RX_CTL, 2, 2, tmp16);

	*tmp = AX_MONITOR_MODE_PMETYPE | AX_MONITOR_MODE_PMEPOL |
	       AX_MONITOR_MODE_RWMP;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_MONITOR_MOD, 1, 1, tmp);

	/* Configure default medium type => giga */
	*tmp16 = AX_MEDIUM_RECEIVE_EN | AX_MEDIUM_TXFLOW_CTRLEN |
		 AX_MEDIUM_RXFLOW_CTRLEN | AX_MEDIUM_FULL_DUPLEX |
		 AX_MEDIUM_GIGAMODE;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			  2, 2, tmp16);

	ax88179_led_setting(dev);

	ax179_data->eee_enabled = 0;
	ax179_data->eee_active = 0;

	ax88179_disable_eee(dev);

	ax88179_ethtool_get_eee(dev, &eee_data);
	eee_data.advertised = 0;
	ax88179_ethtool_set_eee(dev, &eee_data);

	/* Restart autoneg */
	mii_nway_restart(&dev->mii);

	usbnet_link_change(dev, 0, 0);

	return 0;
}
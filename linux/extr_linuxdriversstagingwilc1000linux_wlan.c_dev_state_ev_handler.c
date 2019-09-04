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
typedef  char u8 ;
struct wilc_vif {int /*<<< orphan*/  idx; int /*<<< orphan*/  iftype; } ;
struct wilc_priv {scalar_t__ hif_drv; } ;
struct notifier_block {int dummy; } ;
struct net_device {TYPE_2__* ieee80211_ptr; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_label; int /*<<< orphan*/  ifa_address; TYPE_1__* ifa_dev; } ;
struct host_if_drv {int ifc_up; } ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_3__ {scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_MODE ; 
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  STATION_MODE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,char,...) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wilc_during_ip_timer ; 
 int /*<<< orphan*/  wilc_enable_ps ; 
 int wilc_optaining_ip ; 
 int /*<<< orphan*/  wilc_resolve_disconnect_aberration (struct wilc_vif*) ; 
 int /*<<< orphan*/  wilc_set_power_mgmt (struct wilc_vif*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_setup_ipaddress (struct wilc_vif*,char*,int /*<<< orphan*/ ) ; 
 struct wilc_priv* wiphy_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dev_state_ev_handler(struct notifier_block *this,
				unsigned long event, void *ptr)
{
	struct in_ifaddr *dev_iface = ptr;
	struct wilc_priv *priv;
	struct host_if_drv *hif_drv;
	struct net_device *dev;
	u8 *ip_addr_buf;
	struct wilc_vif *vif;
	u8 null_ip[4] = {0};
	char wlan_dev_name[5] = "wlan0";

	if (!dev_iface || !dev_iface->ifa_dev || !dev_iface->ifa_dev->dev)
		return NOTIFY_DONE;

	if (memcmp(dev_iface->ifa_label, "wlan0", 5) &&
	    memcmp(dev_iface->ifa_label, "p2p0", 4))
		return NOTIFY_DONE;

	dev  = (struct net_device *)dev_iface->ifa_dev->dev;
	if (!dev->ieee80211_ptr || !dev->ieee80211_ptr->wiphy)
		return NOTIFY_DONE;

	priv = wiphy_priv(dev->ieee80211_ptr->wiphy);
	if (!priv)
		return NOTIFY_DONE;

	hif_drv = (struct host_if_drv *)priv->hif_drv;
	vif = netdev_priv(dev);
	if (!vif || !hif_drv)
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		if (vif->iftype == STATION_MODE || vif->iftype == CLIENT_MODE) {
			hif_drv->ifc_up = 1;
			wilc_optaining_ip = false;
			del_timer(&wilc_during_ip_timer);
		}

		if (wilc_enable_ps)
			wilc_set_power_mgmt(vif, 1, 0);

		netdev_dbg(dev, "[%s] Up IP\n", dev_iface->ifa_label);

		ip_addr_buf = (char *)&dev_iface->ifa_address;
		netdev_dbg(dev, "IP add=%d:%d:%d:%d\n",
			   ip_addr_buf[0], ip_addr_buf[1],
			   ip_addr_buf[2], ip_addr_buf[3]);
		wilc_setup_ipaddress(vif, ip_addr_buf, vif->idx);

		break;

	case NETDEV_DOWN:
		if (vif->iftype == STATION_MODE || vif->iftype == CLIENT_MODE) {
			hif_drv->ifc_up = 0;
			wilc_optaining_ip = false;
		}

		if (memcmp(dev_iface->ifa_label, wlan_dev_name, 5) == 0)
			wilc_set_power_mgmt(vif, 0, 0);

		wilc_resolve_disconnect_aberration(vif);

		netdev_dbg(dev, "[%s] Down IP\n", dev_iface->ifa_label);

		ip_addr_buf = null_ip;
		netdev_dbg(dev, "IP add=%d:%d:%d:%d\n",
			   ip_addr_buf[0], ip_addr_buf[1],
			   ip_addr_buf[2], ip_addr_buf[3]);

		wilc_setup_ipaddress(vif, ip_addr_buf, vif->idx);

		break;

	default:
		break;
	}

	return NOTIFY_DONE;
}
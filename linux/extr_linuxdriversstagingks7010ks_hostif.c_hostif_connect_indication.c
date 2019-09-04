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
struct TYPE_6__ {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct TYPE_5__ {scalar_t__ flags; scalar_t__ length; } ;
union iwreq_data {TYPE_3__ ap_addr; TYPE_2__ data; } ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct link_ap_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  confirm_wait; int /*<<< orphan*/  snooze_guard; } ;
struct ks_wlan_private {unsigned int connect_status; scalar_t__ scan_ind_count; struct net_device* net_dev; TYPE_1__ psstatus; scalar_t__ rxp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  CONNECT_STATUS ; 
 int /*<<< orphan*/  DISCONNECT_STATUS ; 
 unsigned int FORCE_DISCONNECT ; 
#define  RESULT_CONNECT 129 
#define  RESULT_DISCONNECT 128 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_ap (struct ks_wlan_private*,struct link_ap_info*) ; 
 int get_word (struct ks_wlan_private*) ; 
 scalar_t__ is_connect_status (unsigned int) ; 
 scalar_t__ is_disconnect_status (unsigned int) ; 
 int /*<<< orphan*/  ks_wlan_do_power_save (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,...) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void hostif_connect_indication(struct ks_wlan_private *priv)
{
	u16 connect_code;
	unsigned int tmp = 0;
	unsigned int old_status = priv->connect_status;
	struct net_device *netdev = priv->net_dev;
	union iwreq_data wrqu0;

	connect_code = get_word(priv);

	switch (connect_code) {
	case RESULT_CONNECT:
		if (!(priv->connect_status & FORCE_DISCONNECT))
			netif_carrier_on(netdev);
		tmp = FORCE_DISCONNECT & priv->connect_status;
		priv->connect_status = tmp + CONNECT_STATUS;
		break;
	case RESULT_DISCONNECT:
		netif_carrier_off(netdev);
		tmp = FORCE_DISCONNECT & priv->connect_status;
		priv->connect_status = tmp + DISCONNECT_STATUS;
		break;
	default:
		netdev_dbg(priv->net_dev, "unknown connect_code=%d :: scan_ind_count=%d\n",
			   connect_code, priv->scan_ind_count);
		netif_carrier_off(netdev);
		tmp = FORCE_DISCONNECT & priv->connect_status;
		priv->connect_status = tmp + DISCONNECT_STATUS;
		break;
	}

	get_current_ap(priv, (struct link_ap_info *)priv->rxp);
	if (is_connect_status(priv->connect_status) &&
	    is_disconnect_status(old_status)) {
		/* for power save */
		atomic_set(&priv->psstatus.snooze_guard, 0);
		atomic_set(&priv->psstatus.confirm_wait, 0);
	}
	ks_wlan_do_power_save(priv);

	wrqu0.data.length = 0;
	wrqu0.data.flags = 0;
	wrqu0.ap_addr.sa_family = ARPHRD_ETHER;
	if (is_disconnect_status(priv->connect_status) &&
	    is_connect_status(old_status)) {
		eth_zero_addr(wrqu0.ap_addr.sa_data);
		netdev_dbg(priv->net_dev, "disconnect :: scan_ind_count=%d\n",
			   priv->scan_ind_count);
		wireless_send_event(netdev, SIOCGIWAP, &wrqu0, NULL);
	}
	priv->scan_ind_count = 0;
}
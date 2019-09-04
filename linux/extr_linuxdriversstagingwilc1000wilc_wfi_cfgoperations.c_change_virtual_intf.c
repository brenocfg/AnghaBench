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
struct wiphy {int dummy; } ;
struct wilc_vif {void* iftype; int /*<<< orphan*/  ifc_id; int /*<<< orphan*/  monitor_flag; struct wilc* wilc; } ;
struct TYPE_4__ {int /*<<< orphan*/  sta_associated_bss; } ;
struct wilc_priv {TYPE_3__* wdev; TYPE_1__ assoc_stainfo; } ;
struct wilc {int /*<<< orphan*/  initialized; } ;
struct vif_params {int dummy; } ;
struct net_device {TYPE_2__* ieee80211_ptr; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_6__ {int iftype; } ;
struct TYPE_5__ {int iftype; } ;

/* Variables and functions */
 void* AP_MODE ; 
 void* CLIENT_MODE ; 
 int /*<<< orphan*/  DURING_IP_TIME_OUT ; 
 int EINVAL ; 
 int ETH_ALEN ; 
 void* GO_MODE ; 
 int MAX_NUM_STA ; 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 void* STATION_MODE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int p2p_local_random ; 
 int p2p_recv_random ; 
 int /*<<< orphan*/  wilc_connecting ; 
 int /*<<< orphan*/  wilc_during_ip_timer ; 
 int wilc_enable_ps ; 
 int /*<<< orphan*/  wilc_get_vif_idx (struct wilc_vif*) ; 
 int wilc_ie ; 
 int wilc_optaining_ip ; 
 int /*<<< orphan*/  wilc_set_operation_mode (struct wilc_vif*,void*) ; 
 int /*<<< orphan*/  wilc_set_power_mgmt (struct wilc_vif*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_set_wfi_drv_handler (struct wilc_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int change_virtual_intf(struct wiphy *wiphy, struct net_device *dev,
			       enum nl80211_iftype type,
			       struct vif_params *params)
{
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wl = vif->wilc;

	p2p_local_random = 0x01;
	p2p_recv_random = 0x00;
	wilc_ie = false;
	wilc_optaining_ip = false;
	del_timer(&wilc_during_ip_timer);

	switch (type) {
	case NL80211_IFTYPE_STATION:
		wilc_connecting = 0;
		dev->ieee80211_ptr->iftype = type;
		priv->wdev->iftype = type;
		vif->monitor_flag = 0;
		vif->iftype = STATION_MODE;
		wilc_set_operation_mode(vif, STATION_MODE);

		memset(priv->assoc_stainfo.sta_associated_bss, 0,
		       MAX_NUM_STA * ETH_ALEN);

		wilc_enable_ps = true;
		wilc_set_power_mgmt(vif, 1, 0);
		break;

	case NL80211_IFTYPE_P2P_CLIENT:
		wilc_connecting = 0;
		dev->ieee80211_ptr->iftype = type;
		priv->wdev->iftype = type;
		vif->monitor_flag = 0;
		vif->iftype = CLIENT_MODE;
		wilc_set_operation_mode(vif, STATION_MODE);

		wilc_enable_ps = false;
		wilc_set_power_mgmt(vif, 0, 0);
		break;

	case NL80211_IFTYPE_AP:
		wilc_enable_ps = false;
		dev->ieee80211_ptr->iftype = type;
		priv->wdev->iftype = type;
		vif->iftype = AP_MODE;

		if (wl->initialized) {
			wilc_set_wfi_drv_handler(vif, wilc_get_vif_idx(vif),
						 0, vif->ifc_id);
			wilc_set_operation_mode(vif, AP_MODE);
			wilc_set_power_mgmt(vif, 0, 0);
		}
		break;

	case NL80211_IFTYPE_P2P_GO:
		wilc_optaining_ip = true;
		mod_timer(&wilc_during_ip_timer,
			  jiffies + msecs_to_jiffies(DURING_IP_TIME_OUT));
		wilc_set_operation_mode(vif, AP_MODE);
		dev->ieee80211_ptr->iftype = type;
		priv->wdev->iftype = type;
		vif->iftype = GO_MODE;

		wilc_enable_ps = false;
		wilc_set_power_mgmt(vif, 0, 0);
		break;

	default:
		netdev_err(dev, "Unknown interface type= %d\n", type);
		return -EINVAL;
	}

	return 0;
}
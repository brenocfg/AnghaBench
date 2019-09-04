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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct wilc_vif {size_t idx; struct wilc* wilc; } ;
struct wilc {TYPE_1__** vif; } ;
struct net_device {int dummy; } ;
struct cfg80211_beacon_data {scalar_t__ tail; int /*<<< orphan*/  tail_len; scalar_t__ head; int /*<<< orphan*/  head_len; } ;
struct cfg80211_ap_settings {int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  chandef; struct cfg80211_beacon_data beacon; } ;
struct TYPE_2__ {int /*<<< orphan*/  src_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_MODE ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int set_channel (struct wiphy*,int /*<<< orphan*/ *) ; 
 int wilc_add_beacon (struct wilc_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wilc_set_power_mgmt (struct wilc_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_wlan_set_bssid (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_ap(struct wiphy *wiphy, struct net_device *dev,
		    struct cfg80211_ap_settings *settings)
{
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wl = vif->wilc;
	struct cfg80211_beacon_data *beacon = &settings->beacon;
	int ret;

	ret = set_channel(wiphy, &settings->chandef);

	if (ret != 0)
		netdev_err(dev, "Error in setting channel\n");

	wilc_wlan_set_bssid(dev, wl->vif[vif->idx]->src_addr, AP_MODE);
	wilc_set_power_mgmt(vif, 0, 0);

	return wilc_add_beacon(vif, settings->beacon_interval,
				   settings->dtim_period, beacon->head_len,
				   (u8 *)beacon->head, beacon->tail_len,
				   (u8 *)beacon->tail);
}
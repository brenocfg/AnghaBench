#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct sta_info {int /*<<< orphan*/  sta; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  sta_mtx; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_OFF_CHANNEL ; 
 int /*<<< orphan*/  clear_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv_tdls_cancel_channel_switch (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tdls_dbg (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

void
ieee80211_tdls_cancel_channel_switch(struct wiphy *wiphy,
				     struct net_device *dev,
				     const u8 *addr)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;

	mutex_lock(&local->sta_mtx);
	sta = sta_info_get(sdata, addr);
	if (!sta) {
		tdls_dbg(sdata,
			 "Invalid TDLS peer %pM for channel switch cancel\n",
			 addr);
		goto out;
	}

	if (!test_sta_flag(sta, WLAN_STA_TDLS_OFF_CHANNEL)) {
		tdls_dbg(sdata, "TDLS channel switch not initiated by %pM\n",
			 addr);
		goto out;
	}

	drv_tdls_cancel_channel_switch(local, sdata, &sta->sta);
	clear_sta_flag(sta, WLAN_STA_TDLS_OFF_CHANNEL);

out:
	mutex_unlock(&local->sta_mtx);
}
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
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct sta_info {int /*<<< orphan*/  sta; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  sta_mtx; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTSUPP ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_CHAN_SWITCH ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_OFF_CHANNEL ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int drv_tdls_channel_switch (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cfg80211_chan_def*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* ieee80211_tdls_ch_sw_tmpl_get (struct sta_info*,int /*<<< orphan*/ ,struct cfg80211_chan_def*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tdls_dbg (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

int
ieee80211_tdls_channel_switch(struct wiphy *wiphy, struct net_device *dev,
			      const u8 *addr, u8 oper_class,
			      struct cfg80211_chan_def *chandef)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;
	struct sk_buff *skb = NULL;
	u32 ch_sw_tm_ie;
	int ret;

	mutex_lock(&local->sta_mtx);
	sta = sta_info_get(sdata, addr);
	if (!sta) {
		tdls_dbg(sdata,
			 "Invalid TDLS peer %pM for channel switch request\n",
			 addr);
		ret = -ENOENT;
		goto out;
	}

	if (!test_sta_flag(sta, WLAN_STA_TDLS_CHAN_SWITCH)) {
		tdls_dbg(sdata, "TDLS channel switch unsupported by %pM\n",
			 addr);
		ret = -ENOTSUPP;
		goto out;
	}

	skb = ieee80211_tdls_ch_sw_tmpl_get(sta, oper_class, chandef,
					    &ch_sw_tm_ie);
	if (!skb) {
		ret = -ENOENT;
		goto out;
	}

	ret = drv_tdls_channel_switch(local, sdata, &sta->sta, oper_class,
				      chandef, skb, ch_sw_tm_ie);
	if (!ret)
		set_sta_flag(sta, WLAN_STA_TDLS_OFF_CHANNEL);

out:
	mutex_unlock(&local->sta_mtx);
	dev_kfree_skb_any(skb);
	return ret;
}
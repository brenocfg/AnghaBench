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
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int ieee80211_vif_change_bandwidth (struct ieee80211_sub_if_data*,struct cfg80211_chan_def*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ieee80211_set_ap_chanwidth(struct wiphy *wiphy,
				      struct net_device *dev,
				      struct cfg80211_chan_def *chandef)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	int ret;
	u32 changed = 0;

	ret = ieee80211_vif_change_bandwidth(sdata, chandef, &changed);
	if (ret == 0)
		ieee80211_bss_info_change_notify(sdata, changed);

	return ret;
}
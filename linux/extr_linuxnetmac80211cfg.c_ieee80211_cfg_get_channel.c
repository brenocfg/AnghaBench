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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_3__ {struct cfg80211_chan_def chandef; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ bss_conf; int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;
struct ieee80211_local {scalar_t__ open_count; scalar_t__ monitors; struct cfg80211_chan_def _oper_chandef; struct cfg80211_chan_def monitor_chandef; scalar_t__ use_chanctx; } ;
struct ieee80211_chanctx_conf {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 struct ieee80211_sub_if_data* IEEE80211_WDEV_TO_SUB_IF (struct wireless_dev*) ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ieee80211_cfg_get_channel(struct wiphy *wiphy,
				     struct wireless_dev *wdev,
				     struct cfg80211_chan_def *chandef)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	struct ieee80211_local *local = wiphy_priv(wiphy);
	struct ieee80211_chanctx_conf *chanctx_conf;
	int ret = -ENODATA;

	rcu_read_lock();
	chanctx_conf = rcu_dereference(sdata->vif.chanctx_conf);
	if (chanctx_conf) {
		*chandef = sdata->vif.bss_conf.chandef;
		ret = 0;
	} else if (local->open_count > 0 &&
		   local->open_count == local->monitors &&
		   sdata->vif.type == NL80211_IFTYPE_MONITOR) {
		if (local->use_chanctx)
			*chandef = local->monitor_chandef;
		else
			*chandef = local->_oper_chandef;
		ret = 0;
	}
	rcu_read_unlock();

	return ret;
}
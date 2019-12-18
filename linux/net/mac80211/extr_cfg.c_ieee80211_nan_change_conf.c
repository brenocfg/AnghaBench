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
typedef  int u32 ;
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct cfg80211_nan_conf {int /*<<< orphan*/  bands; int /*<<< orphan*/  master_pref; } ;
struct TYPE_4__ {struct cfg80211_nan_conf conf; } ;
struct TYPE_5__ {TYPE_1__ nan; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; int /*<<< orphan*/  local; TYPE_3__ vif; } ;

/* Variables and functions */
 int CFG80211_NAN_CONF_CHANGED_BANDS ; 
 int CFG80211_NAN_CONF_CHANGED_PREF ; 
 int ENETDOWN ; 
 int EOPNOTSUPP ; 
 struct ieee80211_sub_if_data* IEEE80211_WDEV_TO_SUB_IF (struct wireless_dev*) ; 
 scalar_t__ NL80211_IFTYPE_NAN ; 
 int drv_nan_change_conf (int /*<<< orphan*/ ,struct ieee80211_sub_if_data*,struct cfg80211_nan_conf*,int) ; 
 int /*<<< orphan*/  ieee80211_sdata_running (struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static int ieee80211_nan_change_conf(struct wiphy *wiphy,
				     struct wireless_dev *wdev,
				     struct cfg80211_nan_conf *conf,
				     u32 changes)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	struct cfg80211_nan_conf new_conf;
	int ret = 0;

	if (sdata->vif.type != NL80211_IFTYPE_NAN)
		return -EOPNOTSUPP;

	if (!ieee80211_sdata_running(sdata))
		return -ENETDOWN;

	new_conf = sdata->u.nan.conf;

	if (changes & CFG80211_NAN_CONF_CHANGED_PREF)
		new_conf.master_pref = conf->master_pref;

	if (changes & CFG80211_NAN_CONF_CHANGED_BANDS)
		new_conf.bands = conf->bands;

	ret = drv_nan_change_conf(sdata->local, sdata, &new_conf, changes);
	if (!ret)
		sdata->u.nan.conf = new_conf;

	return ret;
}
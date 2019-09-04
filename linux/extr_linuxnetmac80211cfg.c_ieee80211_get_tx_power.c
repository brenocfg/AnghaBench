#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct TYPE_10__ {int txpower; } ;
struct TYPE_9__ {TYPE_5__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_4__ vif; } ;
struct TYPE_7__ {int power_level; } ;
struct TYPE_8__ {TYPE_2__ conf; } ;
struct ieee80211_local {TYPE_3__ hw; int /*<<< orphan*/  use_chanctx; TYPE_1__* ops; } ;
struct TYPE_6__ {scalar_t__ get_txpower; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_WDEV_TO_SUB_IF (struct wireless_dev*) ; 
 int drv_get_txpower (struct ieee80211_local*,struct ieee80211_sub_if_data*,int*) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ieee80211_get_tx_power(struct wiphy *wiphy,
				  struct wireless_dev *wdev,
				  int *dbm)
{
	struct ieee80211_local *local = wiphy_priv(wiphy);
	struct ieee80211_sub_if_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);

	if (local->ops->get_txpower)
		return drv_get_txpower(local, sdata, dbm);

	if (!local->use_chanctx)
		*dbm = local->hw.conf.power_level;
	else
		*dbm = sdata->vif.bss_conf.txpower;

	return 0;
}
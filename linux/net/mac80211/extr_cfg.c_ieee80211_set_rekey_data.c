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
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_local {TYPE_1__* ops; } ;
struct cfg80211_gtk_rekey_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_rekey_data; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  drv_set_rekey_data (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct cfg80211_gtk_rekey_data*) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ieee80211_set_rekey_data(struct wiphy *wiphy,
				    struct net_device *dev,
				    struct cfg80211_gtk_rekey_data *data)
{
	struct ieee80211_local *local = wiphy_priv(wiphy);
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	if (!local->ops->set_rekey_data)
		return -EOPNOTSUPP;

	drv_set_rekey_data(local, sdata, data);

	return 0;
}
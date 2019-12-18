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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct vif_params {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_local {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 struct wireless_dev* ERR_PTR (int) ; 
 struct ieee80211_sub_if_data* IEEE80211_WDEV_TO_SUB_IF (struct wireless_dev*) ; 
 int NL80211_IFTYPE_MONITOR ; 
 int ieee80211_if_add (struct ieee80211_local*,char const*,unsigned char,struct wireless_dev**,int,struct vif_params*) ; 
 int /*<<< orphan*/  ieee80211_if_remove (struct ieee80211_sub_if_data*) ; 
 int ieee80211_set_mon_options (struct ieee80211_sub_if_data*,struct vif_params*) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static struct wireless_dev *ieee80211_add_iface(struct wiphy *wiphy,
						const char *name,
						unsigned char name_assign_type,
						enum nl80211_iftype type,
						struct vif_params *params)
{
	struct ieee80211_local *local = wiphy_priv(wiphy);
	struct wireless_dev *wdev;
	struct ieee80211_sub_if_data *sdata;
	int err;

	err = ieee80211_if_add(local, name, name_assign_type, &wdev, type, params);
	if (err)
		return ERR_PTR(err);

	sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);

	if (type == NL80211_IFTYPE_MONITOR) {
		err = ieee80211_set_mon_options(sdata, params);
		if (err) {
			ieee80211_if_remove(sdata);
			return NULL;
		}
	}

	return wdev;
}
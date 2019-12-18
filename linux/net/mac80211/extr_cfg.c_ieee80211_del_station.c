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
struct wiphy {int dummy; } ;
struct station_del_parameters {int /*<<< orphan*/  mac; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int sta_info_destroy_addr_bss (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sta_info_flush (struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static int ieee80211_del_station(struct wiphy *wiphy, struct net_device *dev,
				 struct station_del_parameters *params)
{
	struct ieee80211_sub_if_data *sdata;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	if (params->mac)
		return sta_info_destroy_addr_bss(sdata, params->mac);

	sta_info_flush(sdata);
	return 0;
}
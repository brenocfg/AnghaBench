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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  _ieee80211_enable_rssi_reports (struct ieee80211_sub_if_data*,int,int) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

void ieee80211_enable_rssi_reports(struct ieee80211_vif *vif,
				    int rssi_min_thold,
				    int rssi_max_thold)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);

	WARN_ON(rssi_min_thold == rssi_max_thold ||
		rssi_min_thold > rssi_max_thold);

	_ieee80211_enable_rssi_reports(sdata, rssi_min_thold,
				       rssi_max_thold);
}
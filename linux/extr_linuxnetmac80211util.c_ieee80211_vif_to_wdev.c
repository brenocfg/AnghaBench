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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sub_if_data {int flags; struct wireless_dev wdev; } ;

/* Variables and functions */
 int IEEE80211_SDATA_IN_DRIVER ; 
 int /*<<< orphan*/  ieee80211_sdata_running (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

struct wireless_dev *ieee80211_vif_to_wdev(struct ieee80211_vif *vif)
{
	struct ieee80211_sub_if_data *sdata;

	if (!vif)
		return NULL;

	sdata = vif_to_sdata(vif);

	if (!ieee80211_sdata_running(sdata) ||
	    !(sdata->flags & IEEE80211_SDATA_IN_DRIVER))
		return NULL;

	return &sdata->wdev;
}
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
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_TXPOWER ; 
 scalar_t__ __ieee80211_recalc_txpower (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_sdata_running (struct ieee80211_sub_if_data*) ; 

void ieee80211_recalc_txpower(struct ieee80211_sub_if_data *sdata,
			      bool update_bss)
{
	if (__ieee80211_recalc_txpower(sdata) ||
	    (update_bss && ieee80211_sdata_running(sdata)))
		ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_TXPOWER);
}
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
typedef  scalar_t__ u32 ;
struct sta_info {struct ieee80211_sub_if_data* sdata; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_mbss_info_change_notify (struct ieee80211_sub_if_data*,scalar_t__) ; 
 scalar_t__ mesh_plink_deactivate (struct sta_info*) ; 

void mesh_sta_cleanup(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	u32 changed = mesh_plink_deactivate(sta);

	if (changed)
		ieee80211_mbss_info_change_notify(sdata, changed);
}
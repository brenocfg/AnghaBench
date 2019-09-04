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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; struct ieee80211_local* local; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 int /*<<< orphan*/  drv_bss_info_changed (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ieee80211_bss_info_change_notify(struct ieee80211_sub_if_data *sdata,
				      u32 changed)
{
	struct ieee80211_local *local = sdata->local;

	if (!changed || sdata->vif.type == NL80211_IFTYPE_AP_VLAN)
		return;

	drv_bss_info_changed(local, sdata, &sdata->vif.bss_conf, changed);
}
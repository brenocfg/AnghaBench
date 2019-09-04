#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ps; } ;
struct TYPE_4__ {TYPE_1__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_PS ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int ieee80211_powersave_allowed (struct ieee80211_sub_if_data*) ; 

void ieee80211_recalc_ps_vif(struct ieee80211_sub_if_data *sdata)
{
	bool ps_allowed = ieee80211_powersave_allowed(sdata);

	if (sdata->vif.bss_conf.ps != ps_allowed) {
		sdata->vif.bss_conf.ps = ps_allowed;
		ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_PS);
	}
}
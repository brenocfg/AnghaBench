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
typedef  unsigned long long u8 ;
typedef  unsigned long long u64 ;
typedef  unsigned long long u16 ;
struct ps_data {unsigned long long dtim_count; } ;
struct TYPE_8__ {struct ps_data ps; } ;
struct TYPE_9__ {TYPE_3__ mesh; } ;
struct TYPE_6__ {int beacon_int; unsigned long long dtim_period; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_1__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_5__ vif; TYPE_2__* bss; } ;
struct ieee80211_local {int dummy; } ;
struct TYPE_7__ {struct ps_data ps; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 unsigned long long do_div (unsigned long long,unsigned long long) ; 
 unsigned long long drv_get_tsf (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 scalar_t__ ieee80211_vif_is_mesh (TYPE_5__*) ; 

void ieee80211_recalc_dtim(struct ieee80211_local *local,
			   struct ieee80211_sub_if_data *sdata)
{
	u64 tsf = drv_get_tsf(local, sdata);
	u64 dtim_count = 0;
	u16 beacon_int = sdata->vif.bss_conf.beacon_int * 1024;
	u8 dtim_period = sdata->vif.bss_conf.dtim_period;
	struct ps_data *ps;
	u8 bcns_from_dtim;

	if (tsf == -1ULL || !beacon_int || !dtim_period)
		return;

	if (sdata->vif.type == NL80211_IFTYPE_AP ||
	    sdata->vif.type == NL80211_IFTYPE_AP_VLAN) {
		if (!sdata->bss)
			return;

		ps = &sdata->bss->ps;
	} else if (ieee80211_vif_is_mesh(&sdata->vif)) {
		ps = &sdata->u.mesh.ps;
	} else {
		return;
	}

	/*
	 * actually finds last dtim_count, mac80211 will update in
	 * __beacon_add_tim().
	 * dtim_count = dtim_period - (tsf / bcn_int) % dtim_period
	 */
	do_div(tsf, beacon_int);
	bcns_from_dtim = do_div(tsf, dtim_period);
	/* just had a DTIM */
	if (!bcns_from_dtim)
		dtim_count = 0;
	else
		dtim_count = dtim_period - bcns_from_dtim;

	ps->dtim_count = dtim_count;
}
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
typedef  int u16 ;
struct TYPE_6__ {scalar_t__ ht_supported; } ;
struct TYPE_7__ {TYPE_1__ ht_cap; } ;
struct sta_info {TYPE_2__ sta; } ;
struct TYPE_8__ {int ht_operation_mode; } ;
struct TYPE_9__ {TYPE_3__ bss_conf; } ;
struct ieee80211_if_managed {int flags; } ;
struct TYPE_10__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_4__ vif; TYPE_5__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_HT ; 
 int IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT ; 
 int IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT ; 
 int IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED ; 
 int IEEE80211_STA_DISABLE_HT ; 
 scalar_t__ iee80211_tdls_have_ht_peers (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iee80211_tdls_recalc_ht_protection(struct ieee80211_sub_if_data *sdata,
				   struct sta_info *sta)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	bool tdls_ht;
	u16 protection = IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED |
			 IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT |
			 IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT;
	u16 opmode;

	/* Nothing to do if the BSS connection uses HT */
	if (!(ifmgd->flags & IEEE80211_STA_DISABLE_HT))
		return;

	tdls_ht = (sta && sta->sta.ht_cap.ht_supported) ||
		  iee80211_tdls_have_ht_peers(sdata);

	opmode = sdata->vif.bss_conf.ht_operation_mode;

	if (tdls_ht)
		opmode |= protection;
	else
		opmode &= ~protection;

	if (opmode == sdata->vif.bss_conf.ht_operation_mode)
		return;

	sdata->vif.bss_conf.ht_operation_mode = opmode;
	ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_HT);
}
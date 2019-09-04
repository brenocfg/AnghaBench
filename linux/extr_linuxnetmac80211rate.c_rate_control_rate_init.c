#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_sta {int dummy; } ;
struct sta_info {int /*<<< orphan*/  rate_ctrl_lock; TYPE_2__* sdata; void* rate_ctrl_priv; struct ieee80211_sta sta; struct rate_control_ref* rate_ctrl; } ;
struct rate_control_ref {int /*<<< orphan*/  priv; TYPE_6__* ops; } ;
struct ieee80211_supported_band {int dummy; } ;
struct TYPE_11__ {TYPE_3__* wiphy; } ;
struct ieee80211_local {TYPE_4__ hw; } ;
struct TYPE_14__ {TYPE_5__* chan; } ;
struct ieee80211_chanctx_conf {TYPE_7__ def; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* rate_init ) (int /*<<< orphan*/ ,struct ieee80211_supported_band*,TYPE_7__*,struct ieee80211_sta*,void*) ;} ;
struct TYPE_12__ {size_t band; } ;
struct TYPE_10__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_8__ {int /*<<< orphan*/  chanctx_conf; } ;
struct TYPE_9__ {TYPE_1__ vif; struct ieee80211_local* local; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_STA_RATE_CONTROL ; 
 int /*<<< orphan*/  ieee80211_sta_set_rx_nss (struct sta_info*) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ieee80211_supported_band*,TYPE_7__*,struct ieee80211_sta*,void*) ; 

void rate_control_rate_init(struct sta_info *sta)
{
	struct ieee80211_local *local = sta->sdata->local;
	struct rate_control_ref *ref = sta->rate_ctrl;
	struct ieee80211_sta *ista = &sta->sta;
	void *priv_sta = sta->rate_ctrl_priv;
	struct ieee80211_supported_band *sband;
	struct ieee80211_chanctx_conf *chanctx_conf;

	ieee80211_sta_set_rx_nss(sta);

	if (!ref)
		return;

	rcu_read_lock();

	chanctx_conf = rcu_dereference(sta->sdata->vif.chanctx_conf);
	if (WARN_ON(!chanctx_conf)) {
		rcu_read_unlock();
		return;
	}

	sband = local->hw.wiphy->bands[chanctx_conf->def.chan->band];

	spin_lock_bh(&sta->rate_ctrl_lock);
	ref->ops->rate_init(ref->priv, sband, &chanctx_conf->def, ista,
			    priv_sta);
	spin_unlock_bh(&sta->rate_ctrl_lock);
	rcu_read_unlock();
	set_sta_flag(sta, WLAN_STA_RATE_CONTROL);
}
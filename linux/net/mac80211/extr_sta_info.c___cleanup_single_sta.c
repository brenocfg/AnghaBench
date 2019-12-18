#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct txq_info {int dummy; } ;
struct tid_ampdu_tx {int /*<<< orphan*/  pending; } ;
struct TYPE_11__ {int /*<<< orphan*/ * tid_tx; struct tid_ampdu_tx** tid_start_tx; } ;
struct TYPE_10__ {scalar_t__* txq; } ;
struct sta_info {TYPE_5__ ampdu_mlme; int /*<<< orphan*/  drv_deliver_wk; int /*<<< orphan*/ * tx_filtered; int /*<<< orphan*/ * ps_tx_buf; TYPE_4__ sta; struct ieee80211_sub_if_data* sdata; } ;
struct ps_data {int /*<<< orphan*/  num_sta_ps; } ;
struct TYPE_12__ {scalar_t__ type; } ;
struct TYPE_8__ {struct ps_data ps; } ;
struct TYPE_9__ {TYPE_2__ mesh; } ;
struct ieee80211_sub_if_data {TYPE_6__ vif; TYPE_3__ u; TYPE_1__* bss; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; int /*<<< orphan*/  total_ps_buffered; } ;
struct TYPE_7__ {struct ps_data ps; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int IEEE80211_NUM_ACS ; 
 int IEEE80211_NUM_TIDS ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 int /*<<< orphan*/  WLAN_STA_PS_DELIVER ; 
 int /*<<< orphan*/  WLAN_STA_PS_DRIVER ; 
 int /*<<< orphan*/  WLAN_STA_PS_STA ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_purge_tx_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_txq_purge (struct ieee80211_local*,struct txq_info*) ; 
 scalar_t__ ieee80211_vif_is_mesh (TYPE_6__*) ; 
 int /*<<< orphan*/  kfree (struct tid_ampdu_tx*) ; 
 int /*<<< orphan*/  mesh_sta_cleanup (struct sta_info*) ; 
 struct tid_ampdu_tx* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 struct txq_info* to_txq_info (scalar_t__) ; 

__attribute__((used)) static void __cleanup_single_sta(struct sta_info *sta)
{
	int ac, i;
	struct tid_ampdu_tx *tid_tx;
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct ieee80211_local *local = sdata->local;
	struct ps_data *ps;

	if (test_sta_flag(sta, WLAN_STA_PS_STA) ||
	    test_sta_flag(sta, WLAN_STA_PS_DRIVER) ||
	    test_sta_flag(sta, WLAN_STA_PS_DELIVER)) {
		if (sta->sdata->vif.type == NL80211_IFTYPE_AP ||
		    sta->sdata->vif.type == NL80211_IFTYPE_AP_VLAN)
			ps = &sdata->bss->ps;
		else if (ieee80211_vif_is_mesh(&sdata->vif))
			ps = &sdata->u.mesh.ps;
		else
			return;

		clear_sta_flag(sta, WLAN_STA_PS_STA);
		clear_sta_flag(sta, WLAN_STA_PS_DRIVER);
		clear_sta_flag(sta, WLAN_STA_PS_DELIVER);

		atomic_dec(&ps->num_sta_ps);
	}

	if (sta->sta.txq[0]) {
		for (i = 0; i < ARRAY_SIZE(sta->sta.txq); i++) {
			struct txq_info *txqi;

			if (!sta->sta.txq[i])
				continue;

			txqi = to_txq_info(sta->sta.txq[i]);

			ieee80211_txq_purge(local, txqi);
		}
	}

	for (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		local->total_ps_buffered -= skb_queue_len(&sta->ps_tx_buf[ac]);
		ieee80211_purge_tx_queue(&local->hw, &sta->ps_tx_buf[ac]);
		ieee80211_purge_tx_queue(&local->hw, &sta->tx_filtered[ac]);
	}

	if (ieee80211_vif_is_mesh(&sdata->vif))
		mesh_sta_cleanup(sta);

	cancel_work_sync(&sta->drv_deliver_wk);

	/*
	 * Destroy aggregation state here. It would be nice to wait for the
	 * driver to finish aggregation stop and then clean up, but for now
	 * drivers have to handle aggregation stop being requested, followed
	 * directly by station destruction.
	 */
	for (i = 0; i < IEEE80211_NUM_TIDS; i++) {
		kfree(sta->ampdu_mlme.tid_start_tx[i]);
		tid_tx = rcu_dereference_raw(sta->ampdu_mlme.tid_tx[i]);
		if (!tid_tx)
			continue;
		ieee80211_purge_tx_queue(&local->hw, &tid_tx->pending);
		kfree(tid_tx);
	}
}
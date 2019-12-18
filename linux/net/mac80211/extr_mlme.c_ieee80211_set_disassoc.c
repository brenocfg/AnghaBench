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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {int /*<<< orphan*/ * position; int /*<<< orphan*/ * membership; } ;
struct TYPE_10__ {int assoc; int qos; int /*<<< orphan*/ * beacon_rate; scalar_t__ dtim_period; scalar_t__ arp_addr_cnt; TYPE_2__ mu_group; int /*<<< orphan*/  p2p_noa_attr; } ;
struct TYPE_11__ {int mu_mimo_owner; int csa_active; TYPE_4__ bss_conf; } ;
struct ieee80211_if_managed {int have_beacon; int p2p_noa_index; int csa_waiting_bcn; int csa_ignored_same_chan; int /*<<< orphan*/  tx_tspec_wk; int /*<<< orphan*/ * tx_tspec; scalar_t__ flags; int /*<<< orphan*/  chswitch_timer; int /*<<< orphan*/  timer; int /*<<< orphan*/  bcn_mon_timer; int /*<<< orphan*/  conn_mon_timer; int /*<<< orphan*/  vht_capa_mask; int /*<<< orphan*/  vht_capa; int /*<<< orphan*/  ht_capa_mask; int /*<<< orphan*/  ht_capa; int /*<<< orphan*/  bssid; int /*<<< orphan*/ * associated; } ;
struct TYPE_9__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {int csa_block_tx; int /*<<< orphan*/  encrypt_headroom; TYPE_5__ vif; TYPE_3__ u; int /*<<< orphan*/  ap_power_level; struct ieee80211_local* local; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_12__ {TYPE_1__ conf; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  dynamic_ps_enable_work; int /*<<< orphan*/  dynamic_ps_timer; TYPE_6__ hw; int /*<<< orphan*/ * ps_sdata; } ;

/* Variables and functions */
 int BSS_CHANGED_ARP_FILTER ; 
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_HT ; 
 int BSS_CHANGED_MU_GROUPS ; 
 int BSS_CHANGED_QOS ; 
 int /*<<< orphan*/  DEAUTH_NEED_MGD_TX_PREP ; 
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_PS ; 
 int IEEE80211_CONF_PS ; 
 int /*<<< orphan*/  IEEE80211_ENCRYPT_HEADROOM ; 
 int /*<<< orphan*/  IEEE80211_QUEUE_STOP_REASON_CSA ; 
 int /*<<< orphan*/  IEEE80211_UNSET_POWER_LEVEL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv_mgd_prepare_tx (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_flush_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*,int) ; 
 scalar_t__ ieee80211_hw_check (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_led_assoc (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_recalc_ps_vif (struct ieee80211_sub_if_data*) ; 
 int ieee80211_reset_erp_info (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_send_deauth_disassoc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_set_wmm_default (struct ieee80211_sub_if_data*,int,int) ; 
 int /*<<< orphan*/  ieee80211_stop_poll (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_vif_release_channel (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_wake_vif_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdata_assert_lock (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  sta_info_flush (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  synchronize_net () ; 

__attribute__((used)) static void ieee80211_set_disassoc(struct ieee80211_sub_if_data *sdata,
				   u16 stype, u16 reason, bool tx,
				   u8 *frame_buf)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct ieee80211_local *local = sdata->local;
	u32 changed = 0;

	sdata_assert_lock(sdata);

	if (WARN_ON_ONCE(tx && !frame_buf))
		return;

	if (WARN_ON(!ifmgd->associated))
		return;

	ieee80211_stop_poll(sdata);

	ifmgd->associated = NULL;
	netif_carrier_off(sdata->dev);

	/*
	 * if we want to get out of ps before disassoc (why?) we have
	 * to do it before sending disassoc, as otherwise the null-packet
	 * won't be valid.
	 */
	if (local->hw.conf.flags & IEEE80211_CONF_PS) {
		local->hw.conf.flags &= ~IEEE80211_CONF_PS;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_PS);
	}
	local->ps_sdata = NULL;

	/* disable per-vif ps */
	ieee80211_recalc_ps_vif(sdata);

	/* make sure ongoing transmission finishes */
	synchronize_net();

	/*
	 * drop any frame before deauth/disassoc, this can be data or
	 * management frame. Since we are disconnecting, we should not
	 * insist sending these frames which can take time and delay
	 * the disconnection and possible the roaming.
	 */
	if (tx)
		ieee80211_flush_queues(local, sdata, true);

	/* deauthenticate/disassociate now */
	if (tx || frame_buf) {
		/*
		 * In multi channel scenarios guarantee that the virtual
		 * interface is granted immediate airtime to transmit the
		 * deauthentication frame by calling mgd_prepare_tx, if the
		 * driver requested so.
		 */
		if (ieee80211_hw_check(&local->hw, DEAUTH_NEED_MGD_TX_PREP) &&
		    !ifmgd->have_beacon)
			drv_mgd_prepare_tx(sdata->local, sdata, 0);

		ieee80211_send_deauth_disassoc(sdata, ifmgd->bssid,
					       ifmgd->bssid, stype, reason,
					       tx, frame_buf);
	}

	/* flush out frame - make sure the deauth was actually sent */
	if (tx)
		ieee80211_flush_queues(local, sdata, false);

	/* clear bssid only after building the needed mgmt frames */
	eth_zero_addr(ifmgd->bssid);

	/* remove AP and TDLS peers */
	sta_info_flush(sdata);

	/* finally reset all BSS / config parameters */
	changed |= ieee80211_reset_erp_info(sdata);

	ieee80211_led_assoc(local, 0);
	changed |= BSS_CHANGED_ASSOC;
	sdata->vif.bss_conf.assoc = false;

	ifmgd->p2p_noa_index = -1;
	memset(&sdata->vif.bss_conf.p2p_noa_attr, 0,
	       sizeof(sdata->vif.bss_conf.p2p_noa_attr));

	/* on the next assoc, re-program HT/VHT parameters */
	memset(&ifmgd->ht_capa, 0, sizeof(ifmgd->ht_capa));
	memset(&ifmgd->ht_capa_mask, 0, sizeof(ifmgd->ht_capa_mask));
	memset(&ifmgd->vht_capa, 0, sizeof(ifmgd->vht_capa));
	memset(&ifmgd->vht_capa_mask, 0, sizeof(ifmgd->vht_capa_mask));

	/* reset MU-MIMO ownership and group data */
	memset(sdata->vif.bss_conf.mu_group.membership, 0,
	       sizeof(sdata->vif.bss_conf.mu_group.membership));
	memset(sdata->vif.bss_conf.mu_group.position, 0,
	       sizeof(sdata->vif.bss_conf.mu_group.position));
	changed |= BSS_CHANGED_MU_GROUPS;
	sdata->vif.mu_mimo_owner = false;

	sdata->ap_power_level = IEEE80211_UNSET_POWER_LEVEL;

	del_timer_sync(&local->dynamic_ps_timer);
	cancel_work_sync(&local->dynamic_ps_enable_work);

	/* Disable ARP filtering */
	if (sdata->vif.bss_conf.arp_addr_cnt)
		changed |= BSS_CHANGED_ARP_FILTER;

	sdata->vif.bss_conf.qos = false;
	changed |= BSS_CHANGED_QOS;

	/* The BSSID (not really interesting) and HT changed */
	changed |= BSS_CHANGED_BSSID | BSS_CHANGED_HT;
	ieee80211_bss_info_change_notify(sdata, changed);

	/* disassociated - set to defaults now */
	ieee80211_set_wmm_default(sdata, false, false);

	del_timer_sync(&sdata->u.mgd.conn_mon_timer);
	del_timer_sync(&sdata->u.mgd.bcn_mon_timer);
	del_timer_sync(&sdata->u.mgd.timer);
	del_timer_sync(&sdata->u.mgd.chswitch_timer);

	sdata->vif.bss_conf.dtim_period = 0;
	sdata->vif.bss_conf.beacon_rate = NULL;

	ifmgd->have_beacon = false;

	ifmgd->flags = 0;
	mutex_lock(&local->mtx);
	ieee80211_vif_release_channel(sdata);

	sdata->vif.csa_active = false;
	ifmgd->csa_waiting_bcn = false;
	ifmgd->csa_ignored_same_chan = false;
	if (sdata->csa_block_tx) {
		ieee80211_wake_vif_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);
		sdata->csa_block_tx = false;
	}
	mutex_unlock(&local->mtx);

	/* existing TX TSPEC sessions no longer exist */
	memset(ifmgd->tx_tspec, 0, sizeof(ifmgd->tx_tspec));
	cancel_delayed_work_sync(&ifmgd->tx_tspec_wk);

	sdata->encrypt_headroom = IEEE80211_ENCRYPT_HEADROOM;
}
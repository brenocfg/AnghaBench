#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct il_rxon_cmd {int dummy; } ;
struct TYPE_10__ {void* bssid_addr; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  qos_active; } ;
struct il_priv {int beacon_enabled; void* bssid; scalar_t__ band; int /*<<< orphan*/  mutex; TYPE_3__* ops; TYPE_4__ staging; int /*<<< orphan*/  active; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  lock; TYPE_1__ qos_data; } ;
struct TYPE_8__ {scalar_t__ enable_beacon; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_2__ bss_conf; } ;
struct ieee80211_hw {struct il_priv* priv; } ;
struct ieee80211_bss_conf {TYPE_4__* bssid; int /*<<< orphan*/  ibss_joined; scalar_t__ aid; int /*<<< orphan*/  sync_tsf; scalar_t__ assoc; scalar_t__ use_cts_prot; scalar_t__ use_short_preamble; int /*<<< orphan*/  qos; } ;
struct TYPE_9__ {int (* manage_ibss_station ) (struct il_priv*,struct ieee80211_vif*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* config_ap ) (struct il_priv*) ;int /*<<< orphan*/  (* post_associate ) (struct il_priv*) ;int /*<<< orphan*/  (* set_rxon_chain ) (struct il_priv*) ;} ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_ERP_CTS_PROT ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 int BSS_CHANGED_HT ; 
 int BSS_CHANGED_IBSS ; 
 int BSS_CHANGED_QOS ; 
 int /*<<< orphan*/  D_MAC80211 (char*,...) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  IL_ERR (char*,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  IL_STOP_REASON_PASSIVE ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  RXON_FLG_SELF_CTS_EN ; 
 int /*<<< orphan*/  RXON_FLG_SHORT_PREAMBLE_MSK ; 
 int /*<<< orphan*/  RXON_FLG_TGG_PROTECT_MSK ; 
 int /*<<< orphan*/  il_beacon_update (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  il_ht_conf (struct il_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  il_is_alive (struct il_priv*) ; 
 scalar_t__ il_is_associated (struct il_priv*) ; 
 int /*<<< orphan*/  il_is_rfkill (struct il_priv*) ; 
 scalar_t__ il_scan_cancel_timeout (struct il_priv*,int) ; 
 int il_send_rxon_assoc (struct il_priv*) ; 
 int /*<<< orphan*/  il_set_no_assoc (struct il_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  il_update_qos (struct il_priv*) ; 
 int /*<<< orphan*/  il_wake_queues_by_reason (struct il_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_zero_ether_addr (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (void*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*) ; 
 int /*<<< orphan*/  stub2 (struct il_priv*) ; 
 int /*<<< orphan*/  stub3 (struct il_priv*) ; 
 int stub4 (struct il_priv*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 

void
il_mac_bss_info_changed(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			struct ieee80211_bss_conf *bss_conf, u32 changes)
{
	struct il_priv *il = hw->priv;
	int ret;

	mutex_lock(&il->mutex);
	D_MAC80211("enter: changes 0x%x\n", changes);

	if (!il_is_alive(il)) {
		D_MAC80211("leave - not alive\n");
		mutex_unlock(&il->mutex);
		return;
	}

	if (changes & BSS_CHANGED_QOS) {
		unsigned long flags;

		spin_lock_irqsave(&il->lock, flags);
		il->qos_data.qos_active = bss_conf->qos;
		il_update_qos(il);
		spin_unlock_irqrestore(&il->lock, flags);
	}

	if (changes & BSS_CHANGED_BEACON_ENABLED) {
		/* FIXME: can we remove beacon_enabled ? */
		if (vif->bss_conf.enable_beacon)
			il->beacon_enabled = true;
		else
			il->beacon_enabled = false;
	}

	if (changes & BSS_CHANGED_BSSID) {
		D_MAC80211("BSSID %pM\n", bss_conf->bssid);

		/*
		 * On passive channel we wait with blocked queues to see if
		 * there is traffic on that channel. If no frame will be
		 * received (what is very unlikely since scan detects AP on
		 * that channel, but theoretically possible), mac80211 associate
		 * procedure will time out and mac80211 will call us with NULL
		 * bssid. We have to unblock queues on such condition.
		 */
		if (is_zero_ether_addr(bss_conf->bssid))
			il_wake_queues_by_reason(il, IL_STOP_REASON_PASSIVE);

		/*
		 * If there is currently a HW scan going on in the background,
		 * then we need to cancel it, otherwise sometimes we are not
		 * able to authenticate (FIXME: why ?)
		 */
		if (il_scan_cancel_timeout(il, 100)) {
			D_MAC80211("leave - scan abort failed\n");
			mutex_unlock(&il->mutex);
			return;
		}

		/* mac80211 only sets assoc when in STATION mode */
		memcpy(il->staging.bssid_addr, bss_conf->bssid, ETH_ALEN);

		/* FIXME: currently needed in a few places */
		memcpy(il->bssid, bss_conf->bssid, ETH_ALEN);
	}

	/*
	 * This needs to be after setting the BSSID in case
	 * mac80211 decides to do both changes at once because
	 * it will invoke post_associate.
	 */
	if (vif->type == NL80211_IFTYPE_ADHOC && (changes & BSS_CHANGED_BEACON))
		il_beacon_update(hw, vif);

	if (changes & BSS_CHANGED_ERP_PREAMBLE) {
		D_MAC80211("ERP_PREAMBLE %d\n", bss_conf->use_short_preamble);
		if (bss_conf->use_short_preamble)
			il->staging.flags |= RXON_FLG_SHORT_PREAMBLE_MSK;
		else
			il->staging.flags &= ~RXON_FLG_SHORT_PREAMBLE_MSK;
	}

	if (changes & BSS_CHANGED_ERP_CTS_PROT) {
		D_MAC80211("ERP_CTS %d\n", bss_conf->use_cts_prot);
		if (bss_conf->use_cts_prot && il->band != NL80211_BAND_5GHZ)
			il->staging.flags |= RXON_FLG_TGG_PROTECT_MSK;
		else
			il->staging.flags &= ~RXON_FLG_TGG_PROTECT_MSK;
		if (bss_conf->use_cts_prot)
			il->staging.flags |= RXON_FLG_SELF_CTS_EN;
		else
			il->staging.flags &= ~RXON_FLG_SELF_CTS_EN;
	}

	if (changes & BSS_CHANGED_BASIC_RATES) {
		/* XXX use this information
		 *
		 * To do that, remove code from il_set_rate() and put something
		 * like this here:
		 *
		 if (A-band)
		 il->staging.ofdm_basic_rates =
		 bss_conf->basic_rates;
		 else
		 il->staging.ofdm_basic_rates =
		 bss_conf->basic_rates >> 4;
		 il->staging.cck_basic_rates =
		 bss_conf->basic_rates & 0xF;
		 */
	}

	if (changes & BSS_CHANGED_HT) {
		il_ht_conf(il, vif);

		if (il->ops->set_rxon_chain)
			il->ops->set_rxon_chain(il);
	}

	if (changes & BSS_CHANGED_ASSOC) {
		D_MAC80211("ASSOC %d\n", bss_conf->assoc);
		if (bss_conf->assoc) {
			il->timestamp = bss_conf->sync_tsf;

			if (!il_is_rfkill(il))
				il->ops->post_associate(il);
		} else
			il_set_no_assoc(il, vif);
	}

	if (changes && il_is_associated(il) && bss_conf->aid) {
		D_MAC80211("Changes (%#x) while associated\n", changes);
		ret = il_send_rxon_assoc(il);
		if (!ret) {
			/* Sync active_rxon with latest change. */
			memcpy((void *)&il->active, &il->staging,
			       sizeof(struct il_rxon_cmd));
		}
	}

	if (changes & BSS_CHANGED_BEACON_ENABLED) {
		if (vif->bss_conf.enable_beacon) {
			memcpy(il->staging.bssid_addr, bss_conf->bssid,
			       ETH_ALEN);
			memcpy(il->bssid, bss_conf->bssid, ETH_ALEN);
			il->ops->config_ap(il);
		} else
			il_set_no_assoc(il, vif);
	}

	if (changes & BSS_CHANGED_IBSS) {
		ret = il->ops->manage_ibss_station(il, vif,
						   bss_conf->ibss_joined);
		if (ret)
			IL_ERR("failed to %s IBSS station %pM\n",
			       bss_conf->ibss_joined ? "add" : "remove",
			       bss_conf->bssid);
	}

	D_MAC80211("leave\n");
	mutex_unlock(&il->mutex);
}
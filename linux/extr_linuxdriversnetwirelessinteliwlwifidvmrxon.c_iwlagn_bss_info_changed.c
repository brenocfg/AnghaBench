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
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  filter_flags; int /*<<< orphan*/  bssid_addr; int /*<<< orphan*/  flags; int /*<<< orphan*/  assoc_id; } ;
struct TYPE_7__ {int protection; int non_gf_sta_present; scalar_t__ enabled; } ;
struct TYPE_6__ {int /*<<< orphan*/  qos_active; } ;
struct iwl_rxon_context {scalar_t__ ctxid; int /*<<< orphan*/  active; TYPE_5__ staging; TYPE_2__ ht; TYPE_1__ qos_data; int /*<<< orphan*/  vif; } ;
struct TYPE_9__ {scalar_t__ state; } ;
struct iwl_priv {int have_rekey_data; scalar_t__ band; int start_calib; int /*<<< orphan*/  mutex; struct iwl_rxon_context* beacon_ctx; TYPE_4__ chain_noise_data; int /*<<< orphan*/  current_ht_config; int /*<<< orphan*/  timestamp; } ;
struct TYPE_8__ {scalar_t__ enable_beacon; scalar_t__ use_short_preamble; int /*<<< orphan*/  aid; } ;
struct ieee80211_vif {scalar_t__ type; TYPE_3__ bss_conf; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_bss_conf {int ht_operation_mode; int /*<<< orphan*/  bssid; scalar_t__ ibss_joined; scalar_t__ assoc; scalar_t__ use_cts_prot; int /*<<< orphan*/  sync_tsf; int /*<<< orphan*/  qos; scalar_t__ idle; } ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_IBSS ; 
 int BSS_CHANGED_IDLE ; 
 int BSS_CHANGED_QOS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT ; 
 int IEEE80211_HT_OP_MODE_PROTECTION ; 
 scalar_t__ IWL_CHAIN_NOISE_DONE ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,...) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 scalar_t__ IWL_RXON_CTX_BSS ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  RXON_FILTER_ASSOC_MSK ; 
 int /*<<< orphan*/  RXON_FILTER_BCON_AWARE_MSK ; 
 int /*<<< orphan*/  RXON_FLG_SELF_CTS_EN ; 
 int /*<<< orphan*/  RXON_FLG_SHORT_PREAMBLE_MSK ; 
 int /*<<< orphan*/  RXON_FLG_TGG_PROTECT_MSK ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_is_ready (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_power_update_mode (struct iwl_priv*,int) ; 
 struct iwl_rxon_context* iwl_rxon_ctx_from_vif (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_set_rxon_ht (struct iwl_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwlagn_bt_coex_rssi_monitor (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwlagn_chain_noise_reset (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwlagn_check_needed_chains (struct iwl_priv*,struct iwl_rxon_context*,struct ieee80211_bss_conf*) ; 
 int /*<<< orphan*/  iwlagn_commit_rxon (struct iwl_priv*,struct iwl_rxon_context*) ; 
 int /*<<< orphan*/  iwlagn_lift_passive_no_rx (struct iwl_priv*) ; 
 int iwlagn_manage_ibss_station (struct iwl_priv*,struct ieee80211_vif*,scalar_t__) ; 
 int /*<<< orphan*/  iwlagn_set_rxon_chain (struct iwl_priv*,struct iwl_rxon_context*) ; 
 scalar_t__ iwlagn_update_beacon (struct iwl_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwlagn_update_qos (struct iwl_priv*,struct iwl_rxon_context*) ; 
 scalar_t__ memcmp (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void iwlagn_bss_info_changed(struct ieee80211_hw *hw,
			     struct ieee80211_vif *vif,
			     struct ieee80211_bss_conf *bss_conf,
			     u32 changes)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	struct iwl_rxon_context *ctx = iwl_rxon_ctx_from_vif(vif);
	int ret;
	bool force = false;

	mutex_lock(&priv->mutex);

	if (changes & BSS_CHANGED_IDLE && bss_conf->idle) {
		/*
		 * If we go idle, then clearly no "passive-no-rx"
		 * workaround is needed any more, this is a reset.
		 */
		iwlagn_lift_passive_no_rx(priv);
	}

	if (unlikely(!iwl_is_ready(priv))) {
		IWL_DEBUG_MAC80211(priv, "leave - not ready\n");
		mutex_unlock(&priv->mutex);
		return;
        }

	if (unlikely(!ctx->vif)) {
		IWL_DEBUG_MAC80211(priv, "leave - vif is NULL\n");
		mutex_unlock(&priv->mutex);
		return;
	}

	if (changes & BSS_CHANGED_BEACON_INT)
		force = true;

	if (changes & BSS_CHANGED_QOS) {
		ctx->qos_data.qos_active = bss_conf->qos;
		iwlagn_update_qos(priv, ctx);
	}

	ctx->staging.assoc_id = cpu_to_le16(vif->bss_conf.aid);
	if (vif->bss_conf.use_short_preamble)
		ctx->staging.flags |= RXON_FLG_SHORT_PREAMBLE_MSK;
	else
		ctx->staging.flags &= ~RXON_FLG_SHORT_PREAMBLE_MSK;

	if (changes & BSS_CHANGED_ASSOC) {
		if (bss_conf->assoc) {
			priv->timestamp = bss_conf->sync_tsf;
			ctx->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
		} else {
			ctx->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;

			if (ctx->ctxid == IWL_RXON_CTX_BSS)
				priv->have_rekey_data = false;
		}

		iwlagn_bt_coex_rssi_monitor(priv);
	}

	if (ctx->ht.enabled) {
		ctx->ht.protection = bss_conf->ht_operation_mode &
					IEEE80211_HT_OP_MODE_PROTECTION;
		ctx->ht.non_gf_sta_present = !!(bss_conf->ht_operation_mode &
					IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
		iwlagn_check_needed_chains(priv, ctx, bss_conf);
		iwl_set_rxon_ht(priv, &priv->current_ht_config);
	}

	iwlagn_set_rxon_chain(priv, ctx);

	if (bss_conf->use_cts_prot && (priv->band != NL80211_BAND_5GHZ))
		ctx->staging.flags |= RXON_FLG_TGG_PROTECT_MSK;
	else
		ctx->staging.flags &= ~RXON_FLG_TGG_PROTECT_MSK;

	if (bss_conf->use_cts_prot)
		ctx->staging.flags |= RXON_FLG_SELF_CTS_EN;
	else
		ctx->staging.flags &= ~RXON_FLG_SELF_CTS_EN;

	memcpy(ctx->staging.bssid_addr, bss_conf->bssid, ETH_ALEN);

	if (vif->type == NL80211_IFTYPE_AP ||
	    vif->type == NL80211_IFTYPE_ADHOC) {
		if (vif->bss_conf.enable_beacon) {
			ctx->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
			priv->beacon_ctx = ctx;
		} else {
			ctx->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;
			priv->beacon_ctx = NULL;
		}
	}

	/*
	 * If the ucode decides to do beacon filtering before
	 * association, it will lose beacons that are needed
	 * before sending frames out on passive channels. This
	 * causes association failures on those channels. Enable
	 * receiving beacons in such cases.
	 */

	if (vif->type == NL80211_IFTYPE_STATION) {
		if (!bss_conf->assoc)
			ctx->staging.filter_flags |= RXON_FILTER_BCON_AWARE_MSK;
		else
			ctx->staging.filter_flags &=
						    ~RXON_FILTER_BCON_AWARE_MSK;
	}

	if (force || memcmp(&ctx->staging, &ctx->active, sizeof(ctx->staging)))
		iwlagn_commit_rxon(priv, ctx);

	if (changes & BSS_CHANGED_ASSOC && bss_conf->assoc) {
		/*
		 * The chain noise calibration will enable PM upon
		 * completion. If calibration has already been run
		 * then we need to enable power management here.
		 */
		if (priv->chain_noise_data.state == IWL_CHAIN_NOISE_DONE)
			iwl_power_update_mode(priv, false);

		/* Enable RX differential gain and sensitivity calibrations */
		iwlagn_chain_noise_reset(priv);
		priv->start_calib = 1;
	}

	if (changes & BSS_CHANGED_IBSS) {
		ret = iwlagn_manage_ibss_station(priv, vif,
						 bss_conf->ibss_joined);
		if (ret)
			IWL_ERR(priv, "failed to %s IBSS station %pM\n",
				bss_conf->ibss_joined ? "add" : "remove",
				bss_conf->bssid);
	}

	if (changes & BSS_CHANGED_BEACON && priv->beacon_ctx == ctx) {
		if (iwlagn_update_beacon(priv, vif))
			IWL_ERR(priv, "Error updating beacon\n");
	}

	mutex_unlock(&priv->mutex);
}
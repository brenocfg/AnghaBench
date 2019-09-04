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
struct sk_buff {scalar_t__ data; } ;
struct iwl_station_priv {struct iwl_rxon_context* ctx; } ;
struct iwl_scale_tbl_info {int is_SGI; int is_ht40; int is_dup; int ant_type; int lq_type; } ;
struct iwl_rxon_context {int dummy; } ;
struct iwl_priv {scalar_t__ band; TYPE_2__* lib; } ;
struct iwl_op_mode {int dummy; } ;
struct iwl_link_quality_cmd {TYPE_3__* rs_table; } ;
struct iwl_lq_sta {scalar_t__ missed_rate_counter; size_t active_tbl; int total_success; int total_failed; int last_rate_n_flags; scalar_t__ stay_in_tbl; struct iwl_scale_tbl_info* lq_info; struct iwl_link_quality_cmd lq; int /*<<< orphan*/  drv; } ;
struct TYPE_10__ {int antenna; int ampdu_len; int ampdu_ack_len; TYPE_4__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_5__ status; } ;
struct ieee80211_supported_band {size_t band; } ;
struct ieee80211_sta {scalar_t__* supp_rates; scalar_t__ drv_priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  enum mac80211_rate_control_flags { ____Placeholder_mac80211_rate_control_flags } mac80211_rate_control_flags ;
struct TYPE_9__ {int flags; int idx; int count; } ;
struct TYPE_8__ {int /*<<< orphan*/  rate_n_flags; } ;
struct TYPE_7__ {TYPE_1__* bt_params; } ;
struct TYPE_6__ {scalar_t__ advanced_bt_coexist; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_DUP_DATA ; 
 int IEEE80211_TX_RC_GREEN_FIELD ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int IEEE80211_TX_STAT_ACK ; 
 int IEEE80211_TX_STAT_AMPDU ; 
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_priv*,char*,...) ; 
 int /*<<< orphan*/  IWL_DEBUG_RATE_LIMIT (struct iwl_priv*,char*) ; 
 int IWL_FIRST_OFDM_RATE ; 
 scalar_t__ IWL_MISSED_RATE_MAX ; 
 struct iwl_priv* IWL_OP_MODE_GET_DVM (struct iwl_op_mode*) ; 
 int IWL_RATE_9M_INDEX ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int RATE_MCS_CODE_MSK ; 
 int RATE_MCS_GF_MSK ; 
 int RATE_MCS_HT_MSK ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_send_lq_cmd (struct iwl_priv*,struct iwl_rxon_context*,struct iwl_link_quality_cmd*,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  rs_bt_update_lq (struct iwl_priv*,struct iwl_rxon_context*,struct iwl_lq_sta*) ; 
 int /*<<< orphan*/  rs_collect_tx_data (struct iwl_scale_tbl_info*,int,int,int) ; 
 int /*<<< orphan*/  rs_get_tbl_info_from_mcs (int,scalar_t__,struct iwl_scale_tbl_info*,int*) ; 
 int /*<<< orphan*/  rs_rate_scale_perform (struct iwl_priv*,struct sk_buff*,struct ieee80211_sta*,struct iwl_lq_sta*) ; 
 int /*<<< orphan*/  rs_stay_in_table (struct iwl_lq_sta*,int) ; 
 scalar_t__ table_type_matches (struct iwl_scale_tbl_info*,struct iwl_scale_tbl_info*) ; 

__attribute__((used)) static void rs_tx_status(void *priv_r, struct ieee80211_supported_band *sband,
			 struct ieee80211_sta *sta, void *priv_sta,
			 struct sk_buff *skb)
{
	int legacy_success;
	int retries;
	int rs_index, mac_index, i;
	struct iwl_lq_sta *lq_sta = priv_sta;
	struct iwl_link_quality_cmd *table;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct iwl_op_mode *op_mode = (struct iwl_op_mode *)priv_r;
	struct iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	enum mac80211_rate_control_flags mac_flags;
	u32 tx_rate;
	struct iwl_scale_tbl_info tbl_type;
	struct iwl_scale_tbl_info *curr_tbl, *other_tbl, *tmp_tbl;
	struct iwl_station_priv *sta_priv = (void *)sta->drv_priv;
	struct iwl_rxon_context *ctx = sta_priv->ctx;

	IWL_DEBUG_RATE_LIMIT(priv, "get frame ack response, update rate scale window\n");

	/* Treat uninitialized rate scaling data same as non-existing. */
	if (!lq_sta) {
		IWL_DEBUG_RATE(priv, "Station rate scaling not created yet.\n");
		return;
	} else if (!lq_sta->drv) {
		IWL_DEBUG_RATE(priv, "Rate scaling not initialized yet.\n");
		return;
	}

	if (!ieee80211_is_data(hdr->frame_control) ||
	    info->flags & IEEE80211_TX_CTL_NO_ACK)
		return;

	/* This packet was aggregated but doesn't carry status info */
	if ((info->flags & IEEE80211_TX_CTL_AMPDU) &&
	    !(info->flags & IEEE80211_TX_STAT_AMPDU))
		return;

	/*
	 * Ignore this Tx frame response if its initial rate doesn't match
	 * that of latest Link Quality command.  There may be stragglers
	 * from a previous Link Quality command, but we're no longer interested
	 * in those; they're either from the "active" mode while we're trying
	 * to check "search" mode, or a prior "search" mode after we've moved
	 * to a new "search" mode (which might become the new "active" mode).
	 */
	table = &lq_sta->lq;
	tx_rate = le32_to_cpu(table->rs_table[0].rate_n_flags);
	rs_get_tbl_info_from_mcs(tx_rate, priv->band, &tbl_type, &rs_index);
	if (priv->band == NL80211_BAND_5GHZ)
		rs_index -= IWL_FIRST_OFDM_RATE;
	mac_flags = info->status.rates[0].flags;
	mac_index = info->status.rates[0].idx;
	/* For HT packets, map MCS to PLCP */
	if (mac_flags & IEEE80211_TX_RC_MCS) {
		mac_index &= RATE_MCS_CODE_MSK;	/* Remove # of streams */
		if (mac_index >= (IWL_RATE_9M_INDEX - IWL_FIRST_OFDM_RATE))
			mac_index++;
		/*
		 * mac80211 HT index is always zero-indexed; we need to move
		 * HT OFDM rates after CCK rates in 2.4 GHz band
		 */
		if (priv->band == NL80211_BAND_2GHZ)
			mac_index += IWL_FIRST_OFDM_RATE;
	}
	/* Here we actually compare this rate to the latest LQ command */
	if ((mac_index < 0) ||
	    (tbl_type.is_SGI != !!(mac_flags & IEEE80211_TX_RC_SHORT_GI)) ||
	    (tbl_type.is_ht40 != !!(mac_flags & IEEE80211_TX_RC_40_MHZ_WIDTH)) ||
	    (tbl_type.is_dup != !!(mac_flags & IEEE80211_TX_RC_DUP_DATA)) ||
	    (tbl_type.ant_type != info->status.antenna) ||
	    (!!(tx_rate & RATE_MCS_HT_MSK) != !!(mac_flags & IEEE80211_TX_RC_MCS)) ||
	    (!!(tx_rate & RATE_MCS_GF_MSK) != !!(mac_flags & IEEE80211_TX_RC_GREEN_FIELD)) ||
	    (rs_index != mac_index)) {
		IWL_DEBUG_RATE(priv, "initial rate %d does not match %d (0x%x)\n", mac_index, rs_index, tx_rate);
		/*
		 * Since rates mis-match, the last LQ command may have failed.
		 * After IWL_MISSED_RATE_MAX mis-matches, resync the uCode with
		 * ... driver.
		 */
		lq_sta->missed_rate_counter++;
		if (lq_sta->missed_rate_counter > IWL_MISSED_RATE_MAX) {
			lq_sta->missed_rate_counter = 0;
			iwl_send_lq_cmd(priv, ctx, &lq_sta->lq, CMD_ASYNC, false);
		}
		/* Regardless, ignore this status info for outdated rate */
		return;
	} else
		/* Rate did match, so reset the missed_rate_counter */
		lq_sta->missed_rate_counter = 0;

	/* Figure out if rate scale algorithm is in active or search table */
	if (table_type_matches(&tbl_type,
				&(lq_sta->lq_info[lq_sta->active_tbl]))) {
		curr_tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
		other_tbl = &(lq_sta->lq_info[1 - lq_sta->active_tbl]);
	} else if (table_type_matches(&tbl_type,
				&lq_sta->lq_info[1 - lq_sta->active_tbl])) {
		curr_tbl = &(lq_sta->lq_info[1 - lq_sta->active_tbl]);
		other_tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
	} else {
		IWL_DEBUG_RATE(priv, "Neither active nor search matches tx rate\n");
		tmp_tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
		IWL_DEBUG_RATE(priv, "active- lq:%x, ant:%x, SGI:%d\n",
			tmp_tbl->lq_type, tmp_tbl->ant_type, tmp_tbl->is_SGI);
		tmp_tbl = &(lq_sta->lq_info[1 - lq_sta->active_tbl]);
		IWL_DEBUG_RATE(priv, "search- lq:%x, ant:%x, SGI:%d\n",
			tmp_tbl->lq_type, tmp_tbl->ant_type, tmp_tbl->is_SGI);
		IWL_DEBUG_RATE(priv, "actual- lq:%x, ant:%x, SGI:%d\n",
			tbl_type.lq_type, tbl_type.ant_type, tbl_type.is_SGI);
		/*
		 * no matching table found, let's by-pass the data collection
		 * and continue to perform rate scale to find the rate table
		 */
		rs_stay_in_table(lq_sta, true);
		goto done;
	}

	/*
	 * Updating the frame history depends on whether packets were
	 * aggregated.
	 *
	 * For aggregation, all packets were transmitted at the same rate, the
	 * first index into rate scale table.
	 */
	if (info->flags & IEEE80211_TX_STAT_AMPDU) {
		tx_rate = le32_to_cpu(table->rs_table[0].rate_n_flags);
		rs_get_tbl_info_from_mcs(tx_rate, priv->band, &tbl_type,
				&rs_index);
		rs_collect_tx_data(curr_tbl, rs_index,
				   info->status.ampdu_len,
				   info->status.ampdu_ack_len);

		/* Update success/fail counts if not searching for new mode */
		if (lq_sta->stay_in_tbl) {
			lq_sta->total_success += info->status.ampdu_ack_len;
			lq_sta->total_failed += (info->status.ampdu_len -
					info->status.ampdu_ack_len);
		}
	} else {
	/*
	 * For legacy, update frame history with for each Tx retry.
	 */
		retries = info->status.rates[0].count - 1;
		/* HW doesn't send more than 15 retries */
		retries = min(retries, 15);

		/* The last transmission may have been successful */
		legacy_success = !!(info->flags & IEEE80211_TX_STAT_ACK);
		/* Collect data for each rate used during failed TX attempts */
		for (i = 0; i <= retries; ++i) {
			tx_rate = le32_to_cpu(table->rs_table[i].rate_n_flags);
			rs_get_tbl_info_from_mcs(tx_rate, priv->band,
					&tbl_type, &rs_index);
			/*
			 * Only collect stats if retried rate is in the same RS
			 * table as active/search.
			 */
			if (table_type_matches(&tbl_type, curr_tbl))
				tmp_tbl = curr_tbl;
			else if (table_type_matches(&tbl_type, other_tbl))
				tmp_tbl = other_tbl;
			else
				continue;
			rs_collect_tx_data(tmp_tbl, rs_index, 1,
					   i < retries ? 0 : legacy_success);
		}

		/* Update success/fail counts if not searching for new mode */
		if (lq_sta->stay_in_tbl) {
			lq_sta->total_success += legacy_success;
			lq_sta->total_failed += retries + (1 - legacy_success);
		}
	}
	/* The last TX rate is cached in lq_sta; it's set in if/else above */
	lq_sta->last_rate_n_flags = tx_rate;
done:
	/* See if there's a better rate or modulation mode to try. */
	if (sta && sta->supp_rates[sband->band])
		rs_rate_scale_perform(priv, skb, sta, lq_sta);

	if (priv->lib->bt_params && priv->lib->bt_params->advanced_bt_coexist)
		rs_bt_update_lq(priv, ctx, lq_sta);
}
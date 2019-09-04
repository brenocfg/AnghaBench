#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct iwl_station_priv {struct iwl_rxon_context* ctx; } ;
struct iwl_scale_tbl_info {int ant_type; int current_rate; } ;
struct iwl_rxon_context {int dummy; } ;
struct iwl_priv {TYPE_2__* stations; int /*<<< orphan*/  band; TYPE_1__* nvm_data; } ;
struct TYPE_7__ {size_t sta_id; } ;
struct iwl_lq_sta {int last_txrate_idx; size_t active_tbl; TYPE_3__ lq; struct iwl_scale_tbl_info* lq_info; int /*<<< orphan*/  search_better_tbl; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct TYPE_8__ {int plcp; } ;
struct TYPE_6__ {TYPE_3__* lq; } ;
struct TYPE_5__ {size_t valid_tx_ant; } ;

/* Variables and functions */
 int IWL_FIRST_CCK_RATE ; 
 int IWL_LAST_CCK_RATE ; 
 int IWL_RATE_COUNT ; 
 int RATE_MCS_ANT_POS ; 
 int RATE_MCS_CCK_MSK ; 
 int first_antenna (size_t) ; 
 TYPE_4__* iwl_rates ; 
 int /*<<< orphan*/  iwl_send_lq_cmd (struct iwl_priv*,struct iwl_rxon_context*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int rate_n_flags_from_tbl (struct iwl_priv*,struct iwl_scale_tbl_info*,int,size_t) ; 
 int /*<<< orphan*/  rs_fill_link_cmd (int /*<<< orphan*/ *,struct iwl_lq_sta*,int) ; 
 int /*<<< orphan*/  rs_get_tbl_info_from_mcs (int,int /*<<< orphan*/ ,struct iwl_scale_tbl_info*,int*) ; 
 int /*<<< orphan*/  rs_is_valid_ant (size_t,int) ; 
 int /*<<< orphan*/  rs_set_expected_tpt_table (struct iwl_lq_sta*,struct iwl_scale_tbl_info*) ; 
 int /*<<< orphan*/  rs_toggle_antenna (size_t,int*,struct iwl_scale_tbl_info*) ; 
 size_t rs_use_green (struct ieee80211_sta*) ; 

__attribute__((used)) static void rs_initialize_lq(struct iwl_priv *priv,
			     struct ieee80211_sta *sta,
			     struct iwl_lq_sta *lq_sta)
{
	struct iwl_scale_tbl_info *tbl;
	int rate_idx;
	int i;
	u32 rate;
	u8 use_green = rs_use_green(sta);
	u8 active_tbl = 0;
	u8 valid_tx_ant;
	struct iwl_station_priv *sta_priv;
	struct iwl_rxon_context *ctx;

	if (!sta || !lq_sta)
		return;

	sta_priv = (void *)sta->drv_priv;
	ctx = sta_priv->ctx;

	i = lq_sta->last_txrate_idx;

	valid_tx_ant = priv->nvm_data->valid_tx_ant;

	if (!lq_sta->search_better_tbl)
		active_tbl = lq_sta->active_tbl;
	else
		active_tbl = 1 - lq_sta->active_tbl;

	tbl = &(lq_sta->lq_info[active_tbl]);

	if ((i < 0) || (i >= IWL_RATE_COUNT))
		i = 0;

	rate = iwl_rates[i].plcp;
	tbl->ant_type = first_antenna(valid_tx_ant);
	rate |= tbl->ant_type << RATE_MCS_ANT_POS;

	if (i >= IWL_FIRST_CCK_RATE && i <= IWL_LAST_CCK_RATE)
		rate |= RATE_MCS_CCK_MSK;

	rs_get_tbl_info_from_mcs(rate, priv->band, tbl, &rate_idx);
	if (!rs_is_valid_ant(valid_tx_ant, tbl->ant_type))
	    rs_toggle_antenna(valid_tx_ant, &rate, tbl);

	rate = rate_n_flags_from_tbl(priv, tbl, rate_idx, use_green);
	tbl->current_rate = rate;
	rs_set_expected_tpt_table(lq_sta, tbl);
	rs_fill_link_cmd(NULL, lq_sta, rate);
	priv->stations[lq_sta->lq.sta_id].lq = &lq_sta->lq;
	iwl_send_lq_cmd(priv, ctx, &lq_sta->lq, 0, true);
}
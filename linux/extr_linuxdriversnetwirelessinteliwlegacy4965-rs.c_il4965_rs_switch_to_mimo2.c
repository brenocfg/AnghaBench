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
typedef  int u16 ;
struct il_scale_tbl_info {int is_ht40; int current_rate; int /*<<< orphan*/  max_search; scalar_t__ action; int /*<<< orphan*/  is_dup; int /*<<< orphan*/  lq_type; } ;
struct TYPE_3__ {int tx_chains_num; } ;
struct il_priv {TYPE_1__ hw_params; } ;
struct il_lq_sta {int is_green; int active_mimo2_rate; int /*<<< orphan*/  is_dup; } ;
struct TYPE_4__ {int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {scalar_t__ smps_mode; TYPE_2__ ht_cap; } ;
struct ieee80211_conf {int dummy; } ;
typedef  int s8 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_RATE (char*,...) ; 
 scalar_t__ IEEE80211_SMPS_STATIC ; 
 int /*<<< orphan*/  IL_MAX_SEARCH ; 
 int /*<<< orphan*/  LQ_MIMO2 ; 
 int RATE_INVALID ; 
 int /*<<< orphan*/  conf_is_ht (struct ieee80211_conf*) ; 
 int il4965_rate_n_flags_from_tbl (struct il_priv*,struct il_scale_tbl_info*,int,int) ; 
 int il4965_rs_get_best_rate (struct il_priv*,struct il_lq_sta*,struct il_scale_tbl_info*,int,int) ; 
 int /*<<< orphan*/  il4965_rs_set_expected_tpt_table (struct il_lq_sta*,struct il_scale_tbl_info*) ; 
 scalar_t__ il_is_ht40_tx_allowed (struct il_priv*,TYPE_2__*) ; 

__attribute__((used)) static int
il4965_rs_switch_to_mimo2(struct il_priv *il, struct il_lq_sta *lq_sta,
			  struct ieee80211_conf *conf,
			  struct ieee80211_sta *sta,
			  struct il_scale_tbl_info *tbl, int idx)
{
	u16 rate_mask;
	s32 rate;
	s8 is_green = lq_sta->is_green;

	if (!conf_is_ht(conf) || !sta->ht_cap.ht_supported)
		return -1;

	if (sta->smps_mode == IEEE80211_SMPS_STATIC)
		return -1;

	/* Need both Tx chains/antennas to support MIMO */
	if (il->hw_params.tx_chains_num < 2)
		return -1;

	D_RATE("LQ: try to switch to MIMO2\n");

	tbl->lq_type = LQ_MIMO2;
	tbl->is_dup = lq_sta->is_dup;
	tbl->action = 0;
	tbl->max_search = IL_MAX_SEARCH;
	rate_mask = lq_sta->active_mimo2_rate;

	if (il_is_ht40_tx_allowed(il, &sta->ht_cap))
		tbl->is_ht40 = 1;
	else
		tbl->is_ht40 = 0;

	il4965_rs_set_expected_tpt_table(lq_sta, tbl);

	rate = il4965_rs_get_best_rate(il, lq_sta, tbl, rate_mask, idx);

	D_RATE("LQ: MIMO2 best rate %d mask %X\n", rate, rate_mask);
	if (rate == RATE_INVALID || !((1 << rate) & rate_mask)) {
		D_RATE("Can't switch with idx %d rate mask %x\n", rate,
		       rate_mask);
		return -1;
	}
	tbl->current_rate =
	    il4965_rate_n_flags_from_tbl(il, tbl, rate, is_green);

	D_RATE("LQ: Switch to new mcs %X idx is green %X\n", tbl->current_rate,
	       is_green);
	return 0;
}
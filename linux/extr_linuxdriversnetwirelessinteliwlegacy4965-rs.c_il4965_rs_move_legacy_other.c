#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct il_scale_tbl_info {int action; int /*<<< orphan*/  lq_type; int /*<<< orphan*/  ant_type; int /*<<< orphan*/  is_SGI; int /*<<< orphan*/  current_rate; struct il_rate_scale_data* win; } ;
struct il_rate_scale_data {int /*<<< orphan*/  success_ratio; } ;
struct TYPE_2__ {int valid_tx_ant; int tx_chains_num; } ;
struct il_priv {TYPE_1__ hw_params; } ;
struct il_lq_sta {size_t active_tbl; int search_better_tbl; scalar_t__ action_counter; struct il_scale_tbl_info* lq_info; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANT_AB ; 
 int /*<<< orphan*/  ANT_AC ; 
 int /*<<< orphan*/  ANT_BC ; 
 int /*<<< orphan*/  D_RATE (char*) ; 
#define  IL_LEGACY_SWITCH_ANTENNA1 133 
#define  IL_LEGACY_SWITCH_ANTENNA2 132 
#define  IL_LEGACY_SWITCH_MIMO2_AB 131 
#define  IL_LEGACY_SWITCH_MIMO2_AC 130 
#define  IL_LEGACY_SWITCH_MIMO2_BC 129 
#define  IL_LEGACY_SWITCH_SISO 128 
 int /*<<< orphan*/  IL_RS_GOOD_RATIO ; 
 int /*<<< orphan*/  LQ_NONE ; 
 int RATE_COUNT ; 
 int /*<<< orphan*/  il4965_rs_is_valid_ant (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_rs_set_expected_tpt_table (struct il_lq_sta*,struct il_scale_tbl_info*) ; 
 int il4965_rs_switch_to_mimo2 (struct il_priv*,struct il_lq_sta*,struct ieee80211_conf*,struct ieee80211_sta*,struct il_scale_tbl_info*,int) ; 
 int il4965_rs_switch_to_siso (struct il_priv*,struct il_lq_sta*,struct ieee80211_conf*,struct ieee80211_sta*,struct il_scale_tbl_info*,int) ; 
 int /*<<< orphan*/  il4965_rs_toggle_antenna (int,int /*<<< orphan*/ *,struct il_scale_tbl_info*) ; 
 int /*<<< orphan*/  memcpy (struct il_scale_tbl_info*,struct il_scale_tbl_info*,int) ; 

__attribute__((used)) static int
il4965_rs_move_legacy_other(struct il_priv *il, struct il_lq_sta *lq_sta,
			    struct ieee80211_conf *conf,
			    struct ieee80211_sta *sta, int idx)
{
	struct il_scale_tbl_info *tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
	struct il_scale_tbl_info *search_tbl =
	    &(lq_sta->lq_info[(1 - lq_sta->active_tbl)]);
	struct il_rate_scale_data *win = &(tbl->win[idx]);
	u32 sz =
	    (sizeof(struct il_scale_tbl_info) -
	     (sizeof(struct il_rate_scale_data) * RATE_COUNT));
	u8 start_action;
	u8 valid_tx_ant = il->hw_params.valid_tx_ant;
	u8 tx_chains_num = il->hw_params.tx_chains_num;
	int ret = 0;
	u8 update_search_tbl_counter = 0;

	tbl->action = IL_LEGACY_SWITCH_SISO;

	start_action = tbl->action;
	for (;;) {
		lq_sta->action_counter++;
		switch (tbl->action) {
		case IL_LEGACY_SWITCH_ANTENNA1:
		case IL_LEGACY_SWITCH_ANTENNA2:
			D_RATE("LQ: Legacy toggle Antenna\n");

			if ((tbl->action == IL_LEGACY_SWITCH_ANTENNA1 &&
			     tx_chains_num <= 1) ||
			    (tbl->action == IL_LEGACY_SWITCH_ANTENNA2 &&
			     tx_chains_num <= 2))
				break;

			/* Don't change antenna if success has been great */
			if (win->success_ratio >= IL_RS_GOOD_RATIO)
				break;

			/* Set up search table to try other antenna */
			memcpy(search_tbl, tbl, sz);

			if (il4965_rs_toggle_antenna
			    (valid_tx_ant, &search_tbl->current_rate,
			     search_tbl)) {
				update_search_tbl_counter = 1;
				il4965_rs_set_expected_tpt_table(lq_sta,
								 search_tbl);
				goto out;
			}
			break;
		case IL_LEGACY_SWITCH_SISO:
			D_RATE("LQ: Legacy switch to SISO\n");

			/* Set up search table to try SISO */
			memcpy(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;
			ret =
			    il4965_rs_switch_to_siso(il, lq_sta, conf, sta,
						     search_tbl, idx);
			if (!ret) {
				lq_sta->action_counter = 0;
				goto out;
			}

			break;
		case IL_LEGACY_SWITCH_MIMO2_AB:
		case IL_LEGACY_SWITCH_MIMO2_AC:
		case IL_LEGACY_SWITCH_MIMO2_BC:
			D_RATE("LQ: Legacy switch to MIMO2\n");

			/* Set up search table to try MIMO */
			memcpy(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;

			if (tbl->action == IL_LEGACY_SWITCH_MIMO2_AB)
				search_tbl->ant_type = ANT_AB;
			else if (tbl->action == IL_LEGACY_SWITCH_MIMO2_AC)
				search_tbl->ant_type = ANT_AC;
			else
				search_tbl->ant_type = ANT_BC;

			if (!il4965_rs_is_valid_ant
			    (valid_tx_ant, search_tbl->ant_type))
				break;

			ret =
			    il4965_rs_switch_to_mimo2(il, lq_sta, conf, sta,
						      search_tbl, idx);
			if (!ret) {
				lq_sta->action_counter = 0;
				goto out;
			}
			break;
		}
		tbl->action++;
		if (tbl->action > IL_LEGACY_SWITCH_MIMO2_BC)
			tbl->action = IL_LEGACY_SWITCH_ANTENNA1;

		if (tbl->action == start_action)
			break;

	}
	search_tbl->lq_type = LQ_NONE;
	return 0;

out:
	lq_sta->search_better_tbl = 1;
	tbl->action++;
	if (tbl->action > IL_LEGACY_SWITCH_MIMO2_BC)
		tbl->action = IL_LEGACY_SWITCH_ANTENNA1;
	if (update_search_tbl_counter)
		search_tbl->action = tbl->action;
	return 0;

}
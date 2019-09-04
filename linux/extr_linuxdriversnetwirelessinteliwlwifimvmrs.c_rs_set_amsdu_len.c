#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ index; } ;
struct iwl_scale_tbl_info {TYPE_1__ rate; } ;
struct iwl_mvm_sta {int amsdu_enabled; int /*<<< orphan*/  max_amsdu_len; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  max_amsdu_len; } ;
typedef  enum rs_action { ____Placeholder_rs_action } rs_action ;

/* Variables and functions */
 scalar_t__ IWL_RATE_MCS_5_INDEX ; 
 int RS_ACTION_DOWNSCALE ; 
 int /*<<< orphan*/  is_ht (TYPE_1__*) ; 
 int /*<<< orphan*/  is_vht (TYPE_1__*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 

__attribute__((used)) static void rs_set_amsdu_len(struct iwl_mvm *mvm, struct ieee80211_sta *sta,
			     struct iwl_scale_tbl_info *tbl,
			     enum rs_action scale_action)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

	/*
	 * In case TLC offload is not active amsdu_enabled is either 0xFFFF
	 * or 0, since there is no per-TID alg.
	 */
	if ((!is_vht(&tbl->rate) && !is_ht(&tbl->rate)) ||
	    tbl->rate.index < IWL_RATE_MCS_5_INDEX ||
	    scale_action == RS_ACTION_DOWNSCALE)
		mvmsta->amsdu_enabled = 0;
	else
		mvmsta->amsdu_enabled = 0xFFFF;

	mvmsta->max_amsdu_len = sta->max_amsdu_len;
}
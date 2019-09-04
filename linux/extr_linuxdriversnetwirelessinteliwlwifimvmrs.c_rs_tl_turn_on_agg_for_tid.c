#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm {int dummy; } ;
struct iwl_lq_sta {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IWL_DEBUG_HT (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 int ieee80211_start_tx_ba_session (struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_session (struct ieee80211_sta*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_tl_turn_on_agg_for_tid(struct iwl_mvm *mvm,
				     struct iwl_lq_sta *lq_data, u8 tid,
				     struct ieee80211_sta *sta)
{
	int ret = -EAGAIN;

	IWL_DEBUG_HT(mvm, "Starting Tx agg: STA: %pM tid: %d\n",
		     sta->addr, tid);

	/* start BA session until the peer sends del BA */
	ret = ieee80211_start_tx_ba_session(sta, tid, 0);
	if (ret == -EAGAIN) {
		/*
		 * driver and mac80211 is out of sync
		 * this might be cause by reloading firmware
		 * stop the tx ba session here
		 */
		IWL_ERR(mvm, "Fail start Tx agg on tid: %d\n",
			tid);
		ieee80211_stop_tx_ba_session(sta, tid);
	}
	return ret;
}
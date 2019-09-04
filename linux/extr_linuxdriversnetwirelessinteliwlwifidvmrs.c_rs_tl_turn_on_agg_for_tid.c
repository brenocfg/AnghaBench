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
struct iwl_priv {scalar_t__ bt_traffic_load; } ;
struct iwl_lq_sta {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IWL_BT_COEX_TRAFFIC_LOAD_HIGH ; 
 int /*<<< orphan*/  IWL_DEBUG_COEX (struct iwl_priv*,char*,scalar_t__) ; 
 int /*<<< orphan*/  IWL_DEBUG_HT (struct iwl_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*,int /*<<< orphan*/ ) ; 
 int ieee80211_start_tx_ba_session (struct ieee80211_sta*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_stop_tx_ba_session (struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_tl_get_load (struct iwl_lq_sta*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rs_tl_turn_on_agg_for_tid(struct iwl_priv *priv,
				      struct iwl_lq_sta *lq_data, u8 tid,
				      struct ieee80211_sta *sta)
{
	int ret = -EAGAIN;

	/*
	 * Don't create TX aggregation sessions when in high
	 * BT traffic, as they would just be disrupted by BT.
	 */
	if (priv->bt_traffic_load >= IWL_BT_COEX_TRAFFIC_LOAD_HIGH) {
		IWL_DEBUG_COEX(priv,
			       "BT traffic (%d), no aggregation allowed\n",
			       priv->bt_traffic_load);
		return ret;
	}

	rs_tl_get_load(lq_data, tid);

	IWL_DEBUG_HT(priv, "Starting Tx agg: STA: %pM tid: %d\n",
			sta->addr, tid);
	ret = ieee80211_start_tx_ba_session(sta, tid, 5000);
	if (ret == -EAGAIN) {
		/*
		 * driver and mac80211 is out of sync
		 * this might be cause by reloading firmware
		 * stop the tx ba session here
		 */
		IWL_ERR(priv, "Fail start Tx agg on tid: %d\n",
			tid);
		ieee80211_stop_tx_ba_session(sta, tid);
	}
	return ret;
}
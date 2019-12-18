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
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  mtx; } ;
struct sta_info {scalar_t__ ptk_idx; TYPE_3__ sta; TYPE_2__ ampdu_mlme; } ;
struct TYPE_8__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_4__ hw; } ;
struct TYPE_5__ {int flags; } ;
struct ieee80211_key {int flags; int /*<<< orphan*/  sdata; TYPE_1__ conf; struct sta_info* sta; struct ieee80211_local* local; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGG_STOP_LOCAL_REQUEST ; 
 int /*<<< orphan*/  AMPDU_AGGREGATION ; 
 int /*<<< orphan*/  AMPDU_KEYBORDER_SUPPORT ; 
 int IEEE80211_KEY_FLAG_NO_AUTO_TX ; 
 int IEEE80211_NUM_TIDS ; 
 scalar_t__ INVALID_PTK_KEYIDX ; 
 int KEY_FLAG_TAINTED ; 
 int KEY_FLAG_UPLOADED_TO_HARDWARE ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_CAN_REPLACE_PTK0 ; 
 int /*<<< orphan*/  WLAN_STA_BLOCK_BA ; 
 int /*<<< orphan*/  ___ieee80211_stop_tx_ba_session (struct sta_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_key_lock (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_clear_fast_xmit (struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_flush_queues (struct ieee80211_local*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ieee80211_hw_check (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_sta_tear_down_BA_sessions (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_ext_feature_isset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_pairwise_rekey(struct ieee80211_key *old,
				     struct ieee80211_key *new)
{
	struct ieee80211_local *local = new->local;
	struct sta_info *sta = new->sta;
	int i;

	assert_key_lock(local);

	if (new->conf.flags & IEEE80211_KEY_FLAG_NO_AUTO_TX) {
		/* Extended Key ID key install, initial one or rekey */

		if (sta->ptk_idx != INVALID_PTK_KEYIDX &&
		    !ieee80211_hw_check(&local->hw, AMPDU_KEYBORDER_SUPPORT)) {
			/* Aggregation Sessions with Extended Key ID must not
			 * mix MPDUs with different keyIDs within one A-MPDU.
			 * Tear down running Tx aggregation sessions and block
			 * new Rx/Tx aggregation requests during rekey to
			 * ensure there are no A-MPDUs when the driver is not
			 * supporting A-MPDU key borders. (Blocking Tx only
			 * would be sufficient but WLAN_STA_BLOCK_BA gets the
			 * job done for the few ms we need it.)
			 */
			set_sta_flag(sta, WLAN_STA_BLOCK_BA);
			mutex_lock(&sta->ampdu_mlme.mtx);
			for (i = 0; i <  IEEE80211_NUM_TIDS; i++)
				___ieee80211_stop_tx_ba_session(sta, i,
								AGG_STOP_LOCAL_REQUEST);
			mutex_unlock(&sta->ampdu_mlme.mtx);
		}
	} else if (old) {
		/* Rekey without Extended Key ID.
		 * Aggregation sessions are OK when running on SW crypto.
		 * A broken remote STA may cause issues not observed with HW
		 * crypto, though.
		 */
		if (!(old->flags & KEY_FLAG_UPLOADED_TO_HARDWARE))
			return;

		/* Stop Tx till we are on the new key */
		old->flags |= KEY_FLAG_TAINTED;
		ieee80211_clear_fast_xmit(sta);
		if (ieee80211_hw_check(&local->hw, AMPDU_AGGREGATION)) {
			set_sta_flag(sta, WLAN_STA_BLOCK_BA);
			ieee80211_sta_tear_down_BA_sessions(sta,
							    AGG_STOP_LOCAL_REQUEST);
		}
		if (!wiphy_ext_feature_isset(local->hw.wiphy,
					     NL80211_EXT_FEATURE_CAN_REPLACE_PTK0)) {
			pr_warn_ratelimited("Rekeying PTK for STA %pM but driver can't safely do that.",
					    sta->sta.addr);
			/* Flushing the driver queues *may* help prevent
			 * the clear text leaks and freezes.
			 */
			ieee80211_flush_queues(local, old->sdata, false);
		}
	}
}
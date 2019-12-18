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
struct sta_info {int /*<<< orphan*/  ptk_idx; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  keyidx; } ;
struct ieee80211_key {TYPE_1__ conf; struct ieee80211_local* local; struct sta_info* sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMPDU_KEYBORDER_SUPPORT ; 
 int /*<<< orphan*/  WLAN_STA_BLOCK_BA ; 
 int /*<<< orphan*/  assert_key_lock (struct ieee80211_local*) ; 
 int /*<<< orphan*/  clear_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_check_fast_xmit (struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ieee80211_set_tx_key(struct ieee80211_key *key)
{
	struct sta_info *sta = key->sta;
	struct ieee80211_local *local = key->local;

	assert_key_lock(local);

	sta->ptk_idx = key->conf.keyidx;

	if (!ieee80211_hw_check(&local->hw, AMPDU_KEYBORDER_SUPPORT))
		clear_sta_flag(sta, WLAN_STA_BLOCK_BA);
	ieee80211_check_fast_xmit(sta);

	return 0;
}
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
struct tid_ampdu_tx {int /*<<< orphan*/  state; } ;
struct sta_info {struct ieee80211_sub_if_data* sdata; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_AGG_STATE_DRV_READY ; 
 int /*<<< orphan*/  HT_AGG_STATE_RESPONSE_RECEIVED ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_agg_tx_operational (struct ieee80211_local*,struct sta_info*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ieee80211_start_tx_ba_cb(struct sta_info *sta, int tid,
			      struct tid_ampdu_tx *tid_tx)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct ieee80211_local *local = sdata->local;

	if (WARN_ON(test_and_set_bit(HT_AGG_STATE_DRV_READY, &tid_tx->state)))
		return;

	if (test_bit(HT_AGG_STATE_RESPONSE_RECEIVED, &tid_tx->state))
		ieee80211_agg_tx_operational(local, sta, tid);
}
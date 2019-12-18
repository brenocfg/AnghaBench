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
struct ieee80211_local {int /*<<< orphan*/  hw_roc_done; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_api_remain_on_channel_expired (struct ieee80211_local*) ; 

void ieee80211_remain_on_channel_expired(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	trace_api_remain_on_channel_expired(local);

	ieee80211_queue_work(hw, &local->hw_roc_done);
}
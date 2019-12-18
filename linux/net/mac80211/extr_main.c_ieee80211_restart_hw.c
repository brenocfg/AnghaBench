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
struct ieee80211_local {int in_reconfig; int /*<<< orphan*/  restart_work; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MAX_QUEUE_MAP ; 
 int /*<<< orphan*/  IEEE80211_QUEUE_STOP_REASON_SUSPEND ; 
 int /*<<< orphan*/  barrier () ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues_by_reason (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_freezable_wq ; 
 int /*<<< orphan*/  trace_api_restart_hw (struct ieee80211_local*) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*) ; 

void ieee80211_restart_hw(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	trace_api_restart_hw(local);

	wiphy_info(hw->wiphy,
		   "Hardware restart was requested\n");

	/* use this reason, ieee80211_reconfig will unblock it */
	ieee80211_stop_queues_by_reason(hw, IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_REASON_SUSPEND,
					false);

	/*
	 * Stop all Rx during the reconfig. We don't want state changes
	 * or driver callbacks while this is in progress.
	 */
	local->in_reconfig = true;
	barrier();

	queue_work(system_freezable_wq, &local->restart_work);
}
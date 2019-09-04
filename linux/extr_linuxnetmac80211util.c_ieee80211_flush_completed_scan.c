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
struct ieee80211_local {int /*<<< orphan*/  scan_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  scanning; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_ABORTED ; 
 int /*<<< orphan*/  SCAN_COMPLETED ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_flush_completed_scan(struct ieee80211_local *local,
					   bool aborted)
{
	/* It's possible that we don't handle the scan completion in
	 * time during suspend, so if it's still marked as completed
	 * here, queue the work and flush it to clean things up.
	 * Instead of calling the worker function directly here, we
	 * really queue it to avoid potential races with other flows
	 * scheduling the same work.
	 */
	if (test_bit(SCAN_COMPLETED, &local->scanning)) {
		/* If coming from reconfiguration failure, abort the scan so
		 * we don't attempt to continue a partial HW scan - which is
		 * possible otherwise if (e.g.) the 2.4 GHz portion was the
		 * completed scan, and a 5 GHz portion is still pending.
		 */
		if (aborted)
			set_bit(SCAN_ABORTED, &local->scanning);
		ieee80211_queue_delayed_work(&local->hw, &local->scan_work, 0);
		flush_delayed_work(&local->scan_work);
	}
}
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
struct ieee80211_local {int /*<<< orphan*/  scan_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  scan_info; int /*<<< orphan*/  scanning; } ;
struct ieee80211_hw {int dummy; } ;
struct cfg80211_scan_info {int /*<<< orphan*/  aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_ABORTED ; 
 int /*<<< orphan*/  SCAN_COMPLETED ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct cfg80211_scan_info*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_api_scan_completed (struct ieee80211_local*,int /*<<< orphan*/ ) ; 

void ieee80211_scan_completed(struct ieee80211_hw *hw,
			      struct cfg80211_scan_info *info)
{
	struct ieee80211_local *local = hw_to_local(hw);

	trace_api_scan_completed(local, info->aborted);

	set_bit(SCAN_COMPLETED, &local->scanning);
	if (info->aborted)
		set_bit(SCAN_ABORTED, &local->scanning);

	memcpy(&local->scan_info, info, sizeof(*info));

	ieee80211_queue_delayed_work(&local->hw, &local->scan_work, 0);
}
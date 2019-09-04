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
struct ieee80211_local {int dummy; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_sched_scan_results (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  trace_api_sched_scan_results (struct ieee80211_local*) ; 

void ieee80211_sched_scan_results(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	trace_api_sched_scan_results(local);

	cfg80211_sched_scan_results(hw->wiphy, 0);
}
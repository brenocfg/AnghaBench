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
struct il_priv {int /*<<< orphan*/ * scan_request; int /*<<< orphan*/ * scan_vif; int /*<<< orphan*/  hw; } ;
struct cfg80211_scan_info {int aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SCAN (char*) ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,struct cfg80211_scan_info*) ; 

__attribute__((used)) static void
il_complete_scan(struct il_priv *il, bool aborted)
{
	struct cfg80211_scan_info info = {
		.aborted = aborted,
	};

	/* check if scan was requested from mac80211 */
	if (il->scan_request) {
		D_SCAN("Complete scan in mac80211\n");
		ieee80211_scan_completed(il->hw, &info);
	}

	il->scan_vif = NULL;
	il->scan_request = NULL;
}
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
typedef  enum nl80211_dfs_regions { ____Placeholder_nl80211_dfs_regions } nl80211_dfs_regions ;

/* Variables and functions */
#define  NL80211_DFS_ETSI 131 
#define  NL80211_DFS_FCC 130 
#define  NL80211_DFS_JP 129 
#define  NL80211_DFS_UNSET 128 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

bool reg_supported_dfs_region(enum nl80211_dfs_regions dfs_region)
{
	switch (dfs_region) {
	case NL80211_DFS_UNSET:
	case NL80211_DFS_FCC:
	case NL80211_DFS_ETSI:
	case NL80211_DFS_JP:
		return true;
	default:
		pr_debug("Ignoring unknown DFS master region: %d\n", dfs_region);
		return false;
	}
}
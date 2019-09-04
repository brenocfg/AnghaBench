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
struct wiphy {int /*<<< orphan*/  regd; } ;
struct ieee80211_regdomain {scalar_t__ dfs_region; } ;

/* Variables and functions */
 scalar_t__ NL80211_DFS_ETSI ; 
 int /*<<< orphan*/  cfg80211_regdomain ; 
 struct ieee80211_regdomain* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool regulatory_pre_cac_allowed(struct wiphy *wiphy)
{
	const struct ieee80211_regdomain *regd = NULL;
	const struct ieee80211_regdomain *wiphy_regd = NULL;
	bool pre_cac_allowed = false;

	rcu_read_lock();

	regd = rcu_dereference(cfg80211_regdomain);
	wiphy_regd = rcu_dereference(wiphy->regd);
	if (!wiphy_regd) {
		if (regd->dfs_region == NL80211_DFS_ETSI)
			pre_cac_allowed = true;

		rcu_read_unlock();

		return pre_cac_allowed;
	}

	if (regd->dfs_region == wiphy_regd->dfs_region &&
	    wiphy_regd->dfs_region == NL80211_DFS_ETSI)
		pre_cac_allowed = true;

	rcu_read_unlock();

	return pre_cac_allowed;
}
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
 int /*<<< orphan*/  cfg80211_regdomain ; 
 struct ieee80211_regdomain* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool reg_dfs_domain_same(struct wiphy *wiphy1, struct wiphy *wiphy2)
{
	const struct ieee80211_regdomain *wiphy1_regd = NULL;
	const struct ieee80211_regdomain *wiphy2_regd = NULL;
	const struct ieee80211_regdomain *cfg80211_regd = NULL;
	bool dfs_domain_same;

	rcu_read_lock();

	cfg80211_regd = rcu_dereference(cfg80211_regdomain);
	wiphy1_regd = rcu_dereference(wiphy1->regd);
	if (!wiphy1_regd)
		wiphy1_regd = cfg80211_regd;

	wiphy2_regd = rcu_dereference(wiphy2->regd);
	if (!wiphy2_regd)
		wiphy2_regd = cfg80211_regd;

	dfs_domain_same = wiphy1_regd->dfs_region == wiphy2_regd->dfs_region;

	rcu_read_unlock();

	return dfs_domain_same;
}
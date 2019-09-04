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
struct ieee80211_regdomain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  cfg80211_regdomain ; 
 struct ieee80211_regdomain const* cfg80211_world_regdom ; 
 int /*<<< orphan*/  core_request_world ; 
 struct ieee80211_regdomain* get_cfg80211_regdom () ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  rcu_free_regdom (struct ieee80211_regdomain const*) ; 
 int /*<<< orphan*/  reg_update_last_request (int /*<<< orphan*/ *) ; 
 struct ieee80211_regdomain const world_regdom ; 

__attribute__((used)) static void reset_regdomains(bool full_reset,
			     const struct ieee80211_regdomain *new_regdom)
{
	const struct ieee80211_regdomain *r;

	ASSERT_RTNL();

	r = get_cfg80211_regdom();

	/* avoid freeing static information or freeing something twice */
	if (r == cfg80211_world_regdom)
		r = NULL;
	if (cfg80211_world_regdom == &world_regdom)
		cfg80211_world_regdom = NULL;
	if (r == &world_regdom)
		r = NULL;

	rcu_free_regdom(r);
	rcu_free_regdom(cfg80211_world_regdom);

	cfg80211_world_regdom = &world_regdom;
	rcu_assign_pointer(cfg80211_regdomain, new_regdom);

	if (!full_reset)
		return;

	reg_update_last_request(&core_request_world);
}
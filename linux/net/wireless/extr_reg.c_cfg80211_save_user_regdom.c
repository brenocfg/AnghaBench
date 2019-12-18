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
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_user_regdom ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_copy_regd (struct ieee80211_regdomain const*) ; 

__attribute__((used)) static void cfg80211_save_user_regdom(const struct ieee80211_regdomain *rd)
{
	ASSERT_RTNL();

	if (!IS_ERR(cfg80211_user_regdom))
		kfree(cfg80211_user_regdom);
	cfg80211_user_regdom = reg_copy_regd(rd);
}
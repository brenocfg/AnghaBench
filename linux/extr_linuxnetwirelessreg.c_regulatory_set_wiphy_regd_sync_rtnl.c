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
struct wiphy {int dummy; } ;
struct ieee80211_regdomain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int __regulatory_set_wiphy_regd (struct wiphy*,struct ieee80211_regdomain*) ; 
 int /*<<< orphan*/  reg_process_self_managed_hints () ; 

int regulatory_set_wiphy_regd_sync_rtnl(struct wiphy *wiphy,
					struct ieee80211_regdomain *rd)
{
	int ret;

	ASSERT_RTNL();

	ret = __regulatory_set_wiphy_regd(wiphy, rd);
	if (ret)
		return ret;

	/* process the request immediately */
	reg_process_self_managed_hints();
	return 0;
}
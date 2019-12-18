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
 int __regulatory_set_wiphy_regd (struct wiphy*,struct ieee80211_regdomain*) ; 
 int /*<<< orphan*/  reg_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int regulatory_set_wiphy_regd(struct wiphy *wiphy,
			      struct ieee80211_regdomain *rd)
{
	int ret = __regulatory_set_wiphy_regd(wiphy, rd);

	if (ret)
		return ret;

	schedule_work(&reg_work);
	return 0;
}
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
typedef  int u32 ;
struct cfg80211_registered_device {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int EINVAL ; 

int cfg80211_validate_beacon_int(struct cfg80211_registered_device *rdev,
				 enum nl80211_iftype iftype, u32 beacon_int)
{
	/*
	 * This is just a basic pre-condition check; if interface combinations
	 * are possible the driver must already be checking those with a call
	 * to cfg80211_check_combinations(), in which case we'll validate more
	 * through the cfg80211_calculate_bi_data() call and code in
	 * cfg80211_iter_combinations().
	 */

	if (beacon_int < 10 || beacon_int > 10000)
		return -EINVAL;

	return 0;
}
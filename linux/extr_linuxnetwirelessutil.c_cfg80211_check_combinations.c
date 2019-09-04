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
struct iface_combination_params {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int cfg80211_iter_combinations (struct wiphy*,struct iface_combination_params*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cfg80211_iter_sum_ifcombs ; 

int cfg80211_check_combinations(struct wiphy *wiphy,
				struct iface_combination_params *params)
{
	int err, num = 0;

	err = cfg80211_iter_combinations(wiphy, params,
					 cfg80211_iter_sum_ifcombs, &num);
	if (err)
		return err;
	if (num == 0)
		return -EBUSY;

	return 0;
}
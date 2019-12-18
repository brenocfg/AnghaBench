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
struct cfg80211_registered_device {int /*<<< orphan*/  rfkill_block; int /*<<< orphan*/  rfkill; } ;

/* Variables and functions */
 scalar_t__ rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

void wiphy_rfkill_set_hw_state(struct wiphy *wiphy, bool blocked)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);

	if (rfkill_set_hw_state(rdev->rfkill, blocked))
		schedule_work(&rdev->rfkill_block);
}
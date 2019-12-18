#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  poll; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  rfkill; TYPE_2__ rfkill_ops; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  rfkill_poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_rfkill_poll ; 
 int /*<<< orphan*/  rfkill_resume_polling (int /*<<< orphan*/ ) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

void wiphy_rfkill_start_polling(struct wiphy *wiphy)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);

	if (!rdev->ops->rfkill_poll)
		return;
	rdev->rfkill_ops.poll = cfg80211_rfkill_poll;
	rfkill_resume_polling(rdev->rfkill);
}
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
struct wireless_dev {scalar_t__ iftype; int is_running; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  opencount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 scalar_t__ NL80211_IFTYPE_NAN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  rdev_stop_nan (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_running (struct wireless_dev*) ; 

void cfg80211_stop_nan(struct cfg80211_registered_device *rdev,
		       struct wireless_dev *wdev)
{
	ASSERT_RTNL();

	if (WARN_ON(wdev->iftype != NL80211_IFTYPE_NAN))
		return;

	if (!wdev_running(wdev))
		return;

	rdev_stop_nan(rdev, wdev);
	wdev->is_running = false;

	rdev->opencount--;
}
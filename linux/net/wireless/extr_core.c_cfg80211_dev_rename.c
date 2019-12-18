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
struct TYPE_3__ {TYPE_2__* debugfsdir; int /*<<< orphan*/  dev; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  NL80211_CMD_NEW_WIPHY ; 
 int cfg80211_dev_check_name (struct cfg80211_registered_device*,char*) ; 
 int /*<<< orphan*/  debugfs_rename (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int device_rename (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nl80211_notify_wiphy (struct cfg80211_registered_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_name (TYPE_1__*) ; 

int cfg80211_dev_rename(struct cfg80211_registered_device *rdev,
			char *newname)
{
	int result;

	ASSERT_RTNL();

	/* Ignore nop renames */
	if (strcmp(newname, wiphy_name(&rdev->wiphy)) == 0)
		return 0;

	result = cfg80211_dev_check_name(rdev, newname);
	if (result < 0)
		return result;

	result = device_rename(&rdev->wiphy.dev, newname);
	if (result)
		return result;

	if (rdev->wiphy.debugfsdir)
		debugfs_rename(rdev->wiphy.debugfsdir->d_parent,
			       rdev->wiphy.debugfsdir,
			       rdev->wiphy.debugfsdir->d_parent, newname);

	nl80211_notify_wiphy(rdev, NL80211_CMD_NEW_WIPHY);

	return 0;
}
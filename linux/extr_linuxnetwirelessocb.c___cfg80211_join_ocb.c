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
struct TYPE_4__ {int /*<<< orphan*/  chan; } ;
struct wireless_dev {scalar_t__ iftype; TYPE_2__ chandef; } ;
struct ocb_setup {TYPE_2__ chandef; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  join_ocb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_WDEV_LOCK (struct wireless_dev*) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ NL80211_IFTYPE_OCB ; 
 scalar_t__ WARN_ON (int) ; 
 int rdev_join_ocb (struct cfg80211_registered_device*,struct net_device*,struct ocb_setup*) ; 

int __cfg80211_join_ocb(struct cfg80211_registered_device *rdev,
			struct net_device *dev,
			struct ocb_setup *setup)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	int err;

	ASSERT_WDEV_LOCK(wdev);

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_OCB)
		return -EOPNOTSUPP;

	if (!rdev->ops->join_ocb)
		return -EOPNOTSUPP;

	if (WARN_ON(!setup->chandef.chan))
		return -EINVAL;

	err = rdev_join_ocb(rdev, dev, setup);
	if (!err)
		wdev->chandef = setup->chandef;

	return err;
}
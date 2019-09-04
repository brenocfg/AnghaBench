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
struct wireless_dev {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 int __cfg80211_leave_ibss (struct cfg80211_registered_device*,struct net_device*,int) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

int cfg80211_leave_ibss(struct cfg80211_registered_device *rdev,
			struct net_device *dev, bool nowext)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	int err;

	wdev_lock(wdev);
	err = __cfg80211_leave_ibss(rdev, dev, nowext);
	wdev_unlock(wdev);

	return err;
}
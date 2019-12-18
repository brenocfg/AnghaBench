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
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cfg80211_leave (struct cfg80211_registered_device*,struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

void cfg80211_leave(struct cfg80211_registered_device *rdev,
		    struct wireless_dev *wdev)
{
	wdev_lock(wdev);
	__cfg80211_leave(rdev, wdev);
	wdev_unlock(wdev);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_monitor_channel; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  cfg80211_has_monitors_only (struct cfg80211_registered_device*) ; 
 int rdev_set_monitor_channel (struct cfg80211_registered_device*,struct cfg80211_chan_def*) ; 

int cfg80211_set_monitor_channel(struct cfg80211_registered_device *rdev,
				 struct cfg80211_chan_def *chandef)
{
	if (!rdev->ops->set_monitor_channel)
		return -EOPNOTSUPP;
	if (!cfg80211_has_monitors_only(rdev))
		return -EBUSY;

	return rdev_set_monitor_channel(rdev, chandef);
}
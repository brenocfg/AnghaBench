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
struct wiphy {int dummy; } ;
struct cfg80211_registered_device {TYPE_1__* cur_cmd_info; } ;
struct TYPE_2__ {unsigned int snd_portid; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

unsigned int cfg80211_vendor_cmd_get_sender(struct wiphy *wiphy)
{
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);

	if (WARN_ON(!rdev->cur_cmd_info))
		return 0;

	return rdev->cur_cmd_info->snd_portid;
}
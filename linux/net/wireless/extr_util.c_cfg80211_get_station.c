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
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {int /*<<< orphan*/  wiphy; } ;
struct station_info {int dummy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  get_station; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  memset (struct station_info*,int /*<<< orphan*/ ,int) ; 
 int rdev_get_station (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/  const*,struct station_info*) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

int cfg80211_get_station(struct net_device *dev, const u8 *mac_addr,
			 struct station_info *sinfo)
{
	struct cfg80211_registered_device *rdev;
	struct wireless_dev *wdev;

	wdev = dev->ieee80211_ptr;
	if (!wdev)
		return -EOPNOTSUPP;

	rdev = wiphy_to_rdev(wdev->wiphy);
	if (!rdev->ops->get_station)
		return -EOPNOTSUPP;

	memset(sinfo, 0, sizeof(*sinfo));

	return rdev_get_station(rdev, dev, mac_addr, sinfo);
}
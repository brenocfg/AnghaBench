#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {scalar_t__ iftype; TYPE_3__* current_bss; int /*<<< orphan*/  wiphy; } ;
struct station_info {int filled; int /*<<< orphan*/  txrate; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_6__ {TYPE_2__ pub; } ;
struct TYPE_4__ {int /*<<< orphan*/  get_station; } ;

/* Variables and functions */
 int BIT_ULL (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  NL80211_STA_INFO_TX_BITRATE ; 
 int cfg80211_calculate_bitrate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfg80211_sinfo_release_content (struct station_info*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int rdev_get_station (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ *,struct station_info*) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_wext_giwrate(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_param *rate, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct station_info sinfo = {};
	u8 addr[ETH_ALEN];
	int err;

	if (wdev->iftype != NL80211_IFTYPE_STATION)
		return -EOPNOTSUPP;

	if (!rdev->ops->get_station)
		return -EOPNOTSUPP;

	err = 0;
	wdev_lock(wdev);
	if (wdev->current_bss)
		memcpy(addr, wdev->current_bss->pub.bssid, ETH_ALEN);
	else
		err = -EOPNOTSUPP;
	wdev_unlock(wdev);
	if (err)
		return err;

	err = rdev_get_station(rdev, dev, addr, &sinfo);
	if (err)
		return err;

	if (!(sinfo.filled & BIT_ULL(NL80211_STA_INFO_TX_BITRATE))) {
		err = -EOPNOTSUPP;
		goto free;
	}

	rate->value = 100000 * cfg80211_calculate_bitrate(&sinfo.txrate);

free:
	cfg80211_sinfo_release_content(&sinfo);
	return err;
}
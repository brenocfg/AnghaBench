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
struct wireless_dev {int iftype; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_freq {int e; int /*<<< orphan*/  m; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct cfg80211_chan_def {TYPE_2__* chan; } ;
struct TYPE_4__ {int /*<<< orphan*/  center_freq; } ;
struct TYPE_3__ {int /*<<< orphan*/  get_channel; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_MONITOR 129 
#define  NL80211_IFTYPE_STATION 128 
 int cfg80211_ibss_wext_giwfreq (struct net_device*,struct iw_request_info*,struct iw_freq*,char*) ; 
 int cfg80211_mgd_wext_giwfreq (struct net_device*,struct iw_request_info*,struct iw_freq*,char*) ; 
 int rdev_get_channel (struct cfg80211_registered_device*,struct wireless_dev*,struct cfg80211_chan_def*) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_wext_giwfreq(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_freq *freq, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct cfg80211_chan_def chandef = {};
	int ret;

	switch (wdev->iftype) {
	case NL80211_IFTYPE_STATION:
		return cfg80211_mgd_wext_giwfreq(dev, info, freq, extra);
	case NL80211_IFTYPE_ADHOC:
		return cfg80211_ibss_wext_giwfreq(dev, info, freq, extra);
	case NL80211_IFTYPE_MONITOR:
		if (!rdev->ops->get_channel)
			return -EINVAL;

		ret = rdev_get_channel(rdev, wdev, &chandef);
		if (ret)
			return ret;
		freq->m = chandef.chan->center_freq;
		freq->e = 6;
		return 0;
	default:
		return -EINVAL;
	}
}
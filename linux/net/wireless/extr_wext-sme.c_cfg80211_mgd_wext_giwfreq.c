#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct ieee80211_channel* channel; } ;
struct TYPE_8__ {TYPE_3__ connect; } ;
struct wireless_dev {scalar_t__ iftype; TYPE_4__ wext; TYPE_2__* current_bss; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_freq {int e; int /*<<< orphan*/  m; } ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
struct TYPE_5__ {struct ieee80211_channel* channel; } ;
struct TYPE_6__ {TYPE_1__ pub; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

int cfg80211_mgd_wext_giwfreq(struct net_device *dev,
			      struct iw_request_info *info,
			      struct iw_freq *freq, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct ieee80211_channel *chan = NULL;

	/* call only for station! */
	if (WARN_ON(wdev->iftype != NL80211_IFTYPE_STATION))
		return -EINVAL;

	wdev_lock(wdev);
	if (wdev->current_bss)
		chan = wdev->current_bss->pub.channel;
	else if (wdev->wext.connect.channel)
		chan = wdev->wext.connect.channel;
	wdev_unlock(wdev);

	if (chan) {
		freq->m = chan->center_freq;
		freq->e = 6;
		return 0;
	}

	/* no channel if not joining */
	return -EINVAL;
}
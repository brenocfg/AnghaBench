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
typedef  void* u32 ;
struct wireless_dev {TYPE_1__* wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int value; int /*<<< orphan*/  fixed; scalar_t__ disabled; } ;
struct cfg80211_registered_device {int dummy; } ;
struct TYPE_2__ {int frag_threshold; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WIPHY_PARAM_FRAG_THRESHOLD ; 
 int rdev_set_wiphy_params (struct cfg80211_registered_device*,int /*<<< orphan*/ ) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (TYPE_1__*) ; 

int cfg80211_wext_siwfrag(struct net_device *dev,
			  struct iw_request_info *info,
			  struct iw_param *frag, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	u32 ofrag = wdev->wiphy->frag_threshold;
	int err;

	if (frag->disabled || !frag->fixed)
		wdev->wiphy->frag_threshold = (u32) -1;
	else if (frag->value < 256)
		return -EINVAL;
	else {
		/* Fragment length must be even, so strip LSB. */
		wdev->wiphy->frag_threshold = frag->value & ~0x1;
	}

	err = rdev_set_wiphy_params(rdev, WIPHY_PARAM_FRAG_THRESHOLD);
	if (err)
		wdev->wiphy->frag_threshold = ofrag;

	return err;
}
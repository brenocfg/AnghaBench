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
struct wireless_dev {int ps; int ps_timeout; scalar_t__ iftype; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; scalar_t__ disabled; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_power_mgmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  IW_POWER_ALL_R 130 
#define  IW_POWER_MODE 129 
#define  IW_POWER_ON 128 
 int IW_POWER_TIMEOUT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int rdev_set_power_mgmt (struct cfg80211_registered_device*,struct net_device*,int,int) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_wext_siwpower(struct net_device *dev,
				  struct iw_request_info *info,
				  struct iw_param *wrq, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	bool ps = wdev->ps;
	int timeout = wdev->ps_timeout;
	int err;

	if (wdev->iftype != NL80211_IFTYPE_STATION)
		return -EINVAL;

	if (!rdev->ops->set_power_mgmt)
		return -EOPNOTSUPP;

	if (wrq->disabled) {
		ps = false;
	} else {
		switch (wrq->flags & IW_POWER_MODE) {
		case IW_POWER_ON:       /* If not specified */
		case IW_POWER_MODE:     /* If set all mask */
		case IW_POWER_ALL_R:    /* If explicitely state all */
			ps = true;
			break;
		default:                /* Otherwise we ignore */
			return -EINVAL;
		}

		if (wrq->flags & ~(IW_POWER_MODE | IW_POWER_TIMEOUT))
			return -EINVAL;

		if (wrq->flags & IW_POWER_TIMEOUT)
			timeout = wrq->value / 1000;
	}

	err = rdev_set_power_mgmt(rdev, dev, ps, timeout);
	if (err)
		return err;

	wdev->ps = ps;
	wdev->ps_timeout = timeout;

	return 0;

}
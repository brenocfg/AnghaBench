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
struct wireless_dev {scalar_t__ iftype; int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sa_data; } ;
struct iw_pmksa {int cmd; int /*<<< orphan*/  pmkid; TYPE_1__ bssid; } ;
struct cfg80211_registered_device {TYPE_2__* ops; } ;
struct cfg80211_pmksa {int /*<<< orphan*/  pmkid; int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  flush_pmksa; int /*<<< orphan*/  del_pmksa; int /*<<< orphan*/  set_pmksa; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  IW_PMKSA_ADD 130 
#define  IW_PMKSA_FLUSH 129 
#define  IW_PMKSA_REMOVE 128 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  memset (struct cfg80211_pmksa*,int /*<<< orphan*/ ,int) ; 
 int rdev_del_pmksa (struct cfg80211_registered_device*,struct net_device*,struct cfg80211_pmksa*) ; 
 int rdev_flush_pmksa (struct cfg80211_registered_device*,struct net_device*) ; 
 int rdev_set_pmksa (struct cfg80211_registered_device*,struct net_device*,struct cfg80211_pmksa*) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_wext_siwpmksa(struct net_device *dev,
				  struct iw_request_info *info,
				  struct iw_point *data, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	struct cfg80211_pmksa cfg_pmksa;
	struct iw_pmksa *pmksa = (struct iw_pmksa *)extra;

	memset(&cfg_pmksa, 0, sizeof(struct cfg80211_pmksa));

	if (wdev->iftype != NL80211_IFTYPE_STATION)
		return -EINVAL;

	cfg_pmksa.bssid = pmksa->bssid.sa_data;
	cfg_pmksa.pmkid = pmksa->pmkid;

	switch (pmksa->cmd) {
	case IW_PMKSA_ADD:
		if (!rdev->ops->set_pmksa)
			return -EOPNOTSUPP;

		return rdev_set_pmksa(rdev, dev, &cfg_pmksa);

	case IW_PMKSA_REMOVE:
		if (!rdev->ops->del_pmksa)
			return -EOPNOTSUPP;

		return rdev_del_pmksa(rdev, dev, &cfg_pmksa);

	case IW_PMKSA_FLUSH:
		if (!rdev->ops->flush_pmksa)
			return -EOPNOTSUPP;

		return rdev_flush_pmksa(rdev, dev);

	default:
		return -EOPNOTSUPP;
	}
}
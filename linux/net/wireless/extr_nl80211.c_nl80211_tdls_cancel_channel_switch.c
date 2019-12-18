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
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {int iftype; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int features; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; TYPE_2__ wiphy; TYPE_1__* ops; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {struct wireless_dev* ieee80211_ptr; TYPE_2__ wiphy; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  tdls_cancel_channel_switch; int /*<<< orphan*/  tdls_channel_switch; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_MAC ; 
 int NL80211_FEATURE_TDLS_CHANNEL_SWITCH ; 
#define  NL80211_IFTYPE_P2P_CLIENT 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/ * nla_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdev_tdls_cancel_channel_switch (struct net_device*,struct net_device*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_tdls_cancel_channel_switch(struct sk_buff *skb,
					      struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	const u8 *addr;

	if (!rdev->ops->tdls_channel_switch ||
	    !rdev->ops->tdls_cancel_channel_switch ||
	    !(rdev->wiphy.features & NL80211_FEATURE_TDLS_CHANNEL_SWITCH))
		return -EOPNOTSUPP;

	switch (dev->ieee80211_ptr->iftype) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_P2P_CLIENT:
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (!info->attrs[NL80211_ATTR_MAC])
		return -EINVAL;

	addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	wdev_lock(wdev);
	rdev_tdls_cancel_channel_switch(rdev, dev, addr);
	wdev_unlock(wdev);

	return 0;
}
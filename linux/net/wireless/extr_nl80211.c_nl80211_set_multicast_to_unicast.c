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
struct wireless_dev {scalar_t__ iftype; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct genl_info {struct nlattr** attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_multicast_to_unicast; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_MULTICAST_TO_UNICAST_ENABLED ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_P2P_GO ; 
 int nla_get_flag (struct nlattr const*) ; 
 int rdev_set_multicast_to_unicast (struct net_device*,struct net_device*,int) ; 

__attribute__((used)) static int nl80211_set_multicast_to_unicast(struct sk_buff *skb,
					    struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	const struct nlattr *nla;
	bool enabled;

	if (!rdev->ops->set_multicast_to_unicast)
		return -EOPNOTSUPP;

	if (wdev->iftype != NL80211_IFTYPE_AP &&
	    wdev->iftype != NL80211_IFTYPE_P2P_GO)
		return -EOPNOTSUPP;

	nla = info->attrs[NL80211_ATTR_MULTICAST_TO_UNICAST_ENABLED];
	enabled = nla_get_flag(nla);

	return rdev_set_multicast_to_unicast(rdev, dev, enabled);
}
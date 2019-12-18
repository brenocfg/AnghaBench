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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  wiphy; TYPE_1__* ieee80211_ptr; } ;
struct genl_info {struct net_device** user_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ieee80211_ptr; } ;
struct cfg80211_acl_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ iftype; int /*<<< orphan*/  beacon_interval; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct cfg80211_acl_data*) ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_P2P_GO ; 
 int PTR_ERR (struct cfg80211_acl_data*) ; 
 int /*<<< orphan*/  kfree (struct cfg80211_acl_data*) ; 
 struct cfg80211_acl_data* parse_acl_data (int /*<<< orphan*/ *,struct genl_info*) ; 
 int rdev_set_mac_acl (struct net_device*,struct net_device*,struct cfg80211_acl_data*) ; 

__attribute__((used)) static int nl80211_set_mac_acl(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct cfg80211_acl_data *acl;
	int err;

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_AP &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_GO)
		return -EOPNOTSUPP;

	if (!dev->ieee80211_ptr->beacon_interval)
		return -EINVAL;

	acl = parse_acl_data(&rdev->wiphy, info);
	if (IS_ERR(acl))
		return PTR_ERR(acl);

	err = rdev_set_mac_acl(rdev, dev, acl);

	kfree(acl);

	return err;
}
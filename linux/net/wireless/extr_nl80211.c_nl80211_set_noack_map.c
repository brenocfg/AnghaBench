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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_device {TYPE_1__* ops; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_noack_map; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_NOACK_MAP ; 
 int /*<<< orphan*/  nla_get_u16 (int /*<<< orphan*/ ) ; 
 int rdev_set_noack_map (struct net_device*,struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_set_noack_map(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	u16 noack_map;

	if (!info->attrs[NL80211_ATTR_NOACK_MAP])
		return -EINVAL;

	if (!rdev->ops->set_noack_map)
		return -EOPNOTSUPP;

	noack_map = nla_get_u16(info->attrs[NL80211_ATTR_NOACK_MAP]);

	return rdev_set_noack_map(rdev, dev, noack_map);
}
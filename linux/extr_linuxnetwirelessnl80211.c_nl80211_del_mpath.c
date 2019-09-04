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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct net_device {TYPE_1__* ops; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  del_mpath; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_MAC ; 
 int /*<<< orphan*/ * nla_data (scalar_t__) ; 
 int rdev_del_mpath (struct net_device*,struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nl80211_del_mpath(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	u8 *dst = NULL;

	if (info->attrs[NL80211_ATTR_MAC])
		dst = nla_data(info->attrs[NL80211_ATTR_MAC]);

	if (!rdev->ops->del_mpath)
		return -EOPNOTSUPP;

	return rdev_del_mpath(rdev, dev, dst);
}
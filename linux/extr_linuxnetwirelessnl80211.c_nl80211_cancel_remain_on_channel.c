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
typedef  int /*<<< orphan*/  u64 ;
struct wireless_dev {TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct wireless_dev** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  cancel_remain_on_channel; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_COOKIE ; 
 int /*<<< orphan*/  nla_get_u64 (int /*<<< orphan*/ ) ; 
 int rdev_cancel_remain_on_channel (struct wireless_dev*,struct wireless_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_cancel_remain_on_channel(struct sk_buff *skb,
					    struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct wireless_dev *wdev = info->user_ptr[1];
	u64 cookie;

	if (!info->attrs[NL80211_ATTR_COOKIE])
		return -EINVAL;

	if (!rdev->ops->cancel_remain_on_channel)
		return -EOPNOTSUPP;

	cookie = nla_get_u64(info->attrs[NL80211_ATTR_COOKIE]);

	return rdev_cancel_remain_on_channel(rdev, wdev, cookie);
}
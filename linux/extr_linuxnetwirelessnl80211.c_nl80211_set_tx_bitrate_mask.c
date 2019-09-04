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
struct net_device {TYPE_1__* ops; } ;
struct genl_info {struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; } ;
struct cfg80211_bitrate_mask {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_bitrate_mask; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int nl80211_parse_tx_bitrate_mask (struct genl_info*,struct cfg80211_bitrate_mask*) ; 
 int rdev_set_bitrate_mask (struct net_device*,struct net_device*,int /*<<< orphan*/ *,struct cfg80211_bitrate_mask*) ; 

__attribute__((used)) static int nl80211_set_tx_bitrate_mask(struct sk_buff *skb,
				       struct genl_info *info)
{
	struct cfg80211_bitrate_mask mask;
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	int err;

	if (!rdev->ops->set_bitrate_mask)
		return -EOPNOTSUPP;

	err = nl80211_parse_tx_bitrate_mask(info, &mask);
	if (err)
		return err;

	return rdev_set_bitrate_mask(rdev, dev, NULL, &mask);
}
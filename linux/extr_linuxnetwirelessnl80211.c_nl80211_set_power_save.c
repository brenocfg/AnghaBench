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
typedef  scalar_t__ u8 ;
struct wireless_dev {int ps; int /*<<< orphan*/  ps_timeout; } ;
struct sk_buff {int dummy; } ;
struct net_device {TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_power_mgmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_PS_STATE ; 
 scalar_t__ NL80211_PS_DISABLED ; 
 scalar_t__ NL80211_PS_ENABLED ; 
 scalar_t__ nla_get_u32 (int /*<<< orphan*/ ) ; 
 int rdev_set_power_mgmt (struct net_device*,struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_set_power_save(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct wireless_dev *wdev;
	struct net_device *dev = info->user_ptr[1];
	u8 ps_state;
	bool state;
	int err;

	if (!info->attrs[NL80211_ATTR_PS_STATE])
		return -EINVAL;

	ps_state = nla_get_u32(info->attrs[NL80211_ATTR_PS_STATE]);

	if (ps_state != NL80211_PS_DISABLED && ps_state != NL80211_PS_ENABLED)
		return -EINVAL;

	wdev = dev->ieee80211_ptr;

	if (!rdev->ops->set_power_mgmt)
		return -EOPNOTSUPP;

	state = (ps_state == NL80211_PS_ENABLED) ? true : false;

	if (state == wdev->ps)
		return 0;

	err = rdev_set_power_mgmt(rdev, dev, state, wdev->ps_timeout);
	if (!err)
		wdev->ps = state;
	return err;
}
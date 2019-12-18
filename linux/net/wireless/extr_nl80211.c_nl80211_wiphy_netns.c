#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct genl_info {scalar_t__* attrs; struct cfg80211_registered_device** user_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct net*) ; 
 size_t NL80211_ATTR_NETNS_FD ; 
 size_t NL80211_ATTR_PID ; 
 int PTR_ERR (struct net*) ; 
 int cfg80211_switch_netns (struct cfg80211_registered_device*,struct net*) ; 
 struct net* get_net_ns_by_fd (int /*<<< orphan*/ ) ; 
 struct net* get_net_ns_by_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  nla_get_u32 (scalar_t__) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nl80211_wiphy_netns(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net *net;
	int err;

	if (info->attrs[NL80211_ATTR_PID]) {
		u32 pid = nla_get_u32(info->attrs[NL80211_ATTR_PID]);

		net = get_net_ns_by_pid(pid);
	} else if (info->attrs[NL80211_ATTR_NETNS_FD]) {
		u32 fd = nla_get_u32(info->attrs[NL80211_ATTR_NETNS_FD]);

		net = get_net_ns_by_fd(fd);
	} else {
		return -EINVAL;
	}

	if (IS_ERR(net))
		return PTR_ERR(net);

	err = 0;

	/* check if anything to do */
	if (!net_eq(wiphy_net(&rdev->wiphy), net))
		err = cfg80211_switch_netns(rdev, net);

	put_net(net);
	return err;
}
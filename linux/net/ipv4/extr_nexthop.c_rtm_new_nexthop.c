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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nh_config {int dummy; } ;
struct nexthop {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nexthop*) ; 
 int PTR_ERR (struct nexthop*) ; 
 struct nexthop* nexthop_add (struct net*,struct nh_config*,struct netlink_ext_ack*) ; 
 int rtm_to_nh_config (struct net*,struct sk_buff*,struct nlmsghdr*,struct nh_config*,struct netlink_ext_ack*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtm_new_nexthop(struct sk_buff *skb, struct nlmsghdr *nlh,
			   struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct nh_config cfg;
	struct nexthop *nh;
	int err;

	err = rtm_to_nh_config(net, skb, nlh, &cfg, extack);
	if (!err) {
		nh = nexthop_add(net, &cfg, extack);
		if (IS_ERR(nh))
			err = PTR_ERR(nh);
	}

	return err;
}
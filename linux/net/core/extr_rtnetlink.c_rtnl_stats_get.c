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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct if_stats_msg {scalar_t__ ifindex; int /*<<< orphan*/  filter_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  RTM_NEWSTATS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct net_device* __dev_get_by_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  if_nlmsg_stats_size (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netlink_strict_get_check (struct sk_buff*) ; 
 struct if_stats_msg* nlmsg_data (struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtnl_fill_statsinfo (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 int rtnl_valid_stats_req (struct nlmsghdr*,int /*<<< orphan*/ ,int,struct netlink_ext_ack*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtnl_stats_get(struct sk_buff *skb, struct nlmsghdr *nlh,
			  struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct net_device *dev = NULL;
	int idxattr = 0, prividx = 0;
	struct if_stats_msg *ifsm;
	struct sk_buff *nskb;
	u32 filter_mask;
	int err;

	err = rtnl_valid_stats_req(nlh, netlink_strict_get_check(skb),
				   false, extack);
	if (err)
		return err;

	ifsm = nlmsg_data(nlh);
	if (ifsm->ifindex > 0)
		dev = __dev_get_by_index(net, ifsm->ifindex);
	else
		return -EINVAL;

	if (!dev)
		return -ENODEV;

	filter_mask = ifsm->filter_mask;
	if (!filter_mask)
		return -EINVAL;

	nskb = nlmsg_new(if_nlmsg_stats_size(dev, filter_mask), GFP_KERNEL);
	if (!nskb)
		return -ENOBUFS;

	err = rtnl_fill_statsinfo(nskb, dev, RTM_NEWSTATS,
				  NETLINK_CB(skb).portid, nlh->nlmsg_seq, 0,
				  0, filter_mask, &idxattr, &prividx);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in if_nlmsg_stats_size */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(nskb);
	} else {
		err = rtnl_unicast(nskb, net, NETLINK_CB(skb).portid);
	}

	return err;
}
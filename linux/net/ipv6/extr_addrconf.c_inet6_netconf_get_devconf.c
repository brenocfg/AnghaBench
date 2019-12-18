#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct ipv6_devconf* devconf_dflt; struct ipv6_devconf* devconf_all; } ;
struct net {TYPE_1__ ipv6; } ;
struct ipv6_devconf {int dummy; } ;
struct inet6_dev {struct ipv6_devconf cnf; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NETCONFA_ALL ; 
 size_t NETCONFA_IFINDEX ; 
#define  NETCONFA_IFINDEX_ALL 129 
#define  NETCONFA_IFINDEX_DEFAULT 128 
 int /*<<< orphan*/  NETCONFA_MAX ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  RTM_NEWNETCONF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct net_device* dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int inet6_netconf_fill_devconf (struct sk_buff*,int,struct ipv6_devconf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_netconf_msgsize_devconf (int /*<<< orphan*/ ) ; 
 int inet6_netconf_valid_get_req (struct sk_buff*,struct nlmsghdr*,struct nlattr**,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nla_get_s32 (struct nlattr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet6_netconf_get_devconf(struct sk_buff *in_skb,
				     struct nlmsghdr *nlh,
				     struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(in_skb->sk);
	struct nlattr *tb[NETCONFA_MAX+1];
	struct inet6_dev *in6_dev = NULL;
	struct net_device *dev = NULL;
	struct sk_buff *skb;
	struct ipv6_devconf *devconf;
	int ifindex;
	int err;

	err = inet6_netconf_valid_get_req(in_skb, nlh, tb, extack);
	if (err < 0)
		return err;

	if (!tb[NETCONFA_IFINDEX])
		return -EINVAL;

	err = -EINVAL;
	ifindex = nla_get_s32(tb[NETCONFA_IFINDEX]);
	switch (ifindex) {
	case NETCONFA_IFINDEX_ALL:
		devconf = net->ipv6.devconf_all;
		break;
	case NETCONFA_IFINDEX_DEFAULT:
		devconf = net->ipv6.devconf_dflt;
		break;
	default:
		dev = dev_get_by_index(net, ifindex);
		if (!dev)
			return -EINVAL;
		in6_dev = in6_dev_get(dev);
		if (!in6_dev)
			goto errout;
		devconf = &in6_dev->cnf;
		break;
	}

	err = -ENOBUFS;
	skb = nlmsg_new(inet6_netconf_msgsize_devconf(NETCONFA_ALL), GFP_KERNEL);
	if (!skb)
		goto errout;

	err = inet6_netconf_fill_devconf(skb, ifindex, devconf,
					 NETLINK_CB(in_skb).portid,
					 nlh->nlmsg_seq, RTM_NEWNETCONF, 0,
					 NETCONFA_ALL);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in inet6_netconf_msgsize_devconf() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}
	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
errout:
	if (in6_dev)
		in6_dev_put(in6_dev);
	if (dev)
		dev_put(dev);
	return err;
}
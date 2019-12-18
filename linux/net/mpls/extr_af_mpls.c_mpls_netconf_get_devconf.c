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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct mpls_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NETCONFA_ALL ; 
 size_t NETCONFA_IFINDEX ; 
 int /*<<< orphan*/  NETCONFA_MAX ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  RTM_NEWNETCONF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct mpls_dev* mpls_dev_get (struct net_device*) ; 
 int mpls_netconf_fill_devconf (struct sk_buff*,struct mpls_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpls_netconf_msgsize_devconf (int /*<<< orphan*/ ) ; 
 int mpls_netconf_valid_get_req (struct sk_buff*,struct nlmsghdr*,struct nlattr**,struct netlink_ext_ack*) ; 
 int nla_get_s32 (struct nlattr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpls_netconf_get_devconf(struct sk_buff *in_skb,
				    struct nlmsghdr *nlh,
				    struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(in_skb->sk);
	struct nlattr *tb[NETCONFA_MAX + 1];
	struct net_device *dev;
	struct mpls_dev *mdev;
	struct sk_buff *skb;
	int ifindex;
	int err;

	err = mpls_netconf_valid_get_req(in_skb, nlh, tb, extack);
	if (err < 0)
		goto errout;

	err = -EINVAL;
	if (!tb[NETCONFA_IFINDEX])
		goto errout;

	ifindex = nla_get_s32(tb[NETCONFA_IFINDEX]);
	dev = __dev_get_by_index(net, ifindex);
	if (!dev)
		goto errout;

	mdev = mpls_dev_get(dev);
	if (!mdev)
		goto errout;

	err = -ENOBUFS;
	skb = nlmsg_new(mpls_netconf_msgsize_devconf(NETCONFA_ALL), GFP_KERNEL);
	if (!skb)
		goto errout;

	err = mpls_netconf_fill_devconf(skb, mdev,
					NETLINK_CB(in_skb).portid,
					nlh->nlmsg_seq, RTM_NEWNETCONF, 0,
					NETCONFA_ALL);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in mpls_netconf_msgsize_devconf() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout;
	}
	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
errout:
	return err;
}
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
struct inet6_ifaddr {int dummy; } ;
struct inet6_fill_args {int netnsid; int /*<<< orphan*/  flags; int /*<<< orphan*/  event; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct in6_addr {int dummy; } ;
struct ifaddrmsg {scalar_t__ ifa_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IFA_ADDRESS ; 
 size_t IFA_LOCAL ; 
 int /*<<< orphan*/  IFA_MAX ; 
 size_t IFA_TARGET_NETNSID ; 
 scalar_t__ IS_ERR (struct net*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int PTR_ERR (struct net*) ; 
 int /*<<< orphan*/  RTM_NEWADDR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct net_device* dev_get_by_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct in6_addr* extract_addr (struct nlattr*,struct nlattr*,struct in6_addr**) ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 int inet6_fill_ifaddr (struct sk_buff*,struct inet6_ifaddr*,struct inet6_fill_args*) ; 
 int /*<<< orphan*/  inet6_ifaddr_msgsize () ; 
 int inet6_rtm_valid_getaddr_req (struct sk_buff*,struct nlmsghdr*,struct nlattr**,struct netlink_ext_ack*) ; 
 struct inet6_ifaddr* ipv6_get_ifaddr (struct net*,struct in6_addr*,struct net_device*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nla_get_s32 (struct nlattr*) ; 
 struct ifaddrmsg* nlmsg_data (struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 struct net* rtnl_get_net_ns_capable (int /*<<< orphan*/ ,int) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet6_rtm_getaddr(struct sk_buff *in_skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(in_skb->sk);
	struct inet6_fill_args fillargs = {
		.portid = NETLINK_CB(in_skb).portid,
		.seq = nlh->nlmsg_seq,
		.event = RTM_NEWADDR,
		.flags = 0,
		.netnsid = -1,
	};
	struct net *tgt_net = net;
	struct ifaddrmsg *ifm;
	struct nlattr *tb[IFA_MAX+1];
	struct in6_addr *addr = NULL, *peer;
	struct net_device *dev = NULL;
	struct inet6_ifaddr *ifa;
	struct sk_buff *skb;
	int err;

	err = inet6_rtm_valid_getaddr_req(in_skb, nlh, tb, extack);
	if (err < 0)
		return err;

	if (tb[IFA_TARGET_NETNSID]) {
		fillargs.netnsid = nla_get_s32(tb[IFA_TARGET_NETNSID]);

		tgt_net = rtnl_get_net_ns_capable(NETLINK_CB(in_skb).sk,
						  fillargs.netnsid);
		if (IS_ERR(tgt_net))
			return PTR_ERR(tgt_net);
	}

	addr = extract_addr(tb[IFA_ADDRESS], tb[IFA_LOCAL], &peer);
	if (!addr)
		return -EINVAL;

	ifm = nlmsg_data(nlh);
	if (ifm->ifa_index)
		dev = dev_get_by_index(tgt_net, ifm->ifa_index);

	ifa = ipv6_get_ifaddr(tgt_net, addr, dev, 1);
	if (!ifa) {
		err = -EADDRNOTAVAIL;
		goto errout;
	}

	skb = nlmsg_new(inet6_ifaddr_msgsize(), GFP_KERNEL);
	if (!skb) {
		err = -ENOBUFS;
		goto errout_ifa;
	}

	err = inet6_fill_ifaddr(skb, ifa, &fillargs);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in inet6_ifaddr_msgsize() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout_ifa;
	}
	err = rtnl_unicast(skb, tgt_net, NETLINK_CB(in_skb).portid);
errout_ifa:
	in6_ifa_put(ifa);
errout:
	if (dev)
		dev_put(dev);
	if (fillargs.netnsid >= 0)
		put_net(tgt_net);

	return err;
}
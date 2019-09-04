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
struct in6_addr {int dummy; } ;
struct ifaddrmsg {scalar_t__ ifa_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IFA_ADDRESS ; 
 size_t IFA_LOCAL ; 
 int /*<<< orphan*/  IFA_MAX ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  RTM_NEWADDR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct net_device* dev_get_by_index (struct net*,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct in6_addr* extract_addr (struct nlattr*,struct nlattr*,struct in6_addr**) ; 
 int /*<<< orphan*/  ifa_ipv6_policy ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 int inet6_fill_ifaddr (struct sk_buff*,struct inet6_ifaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_ifaddr_msgsize () ; 
 struct inet6_ifaddr* ipv6_get_ifaddr (struct net*,struct in6_addr*,struct net_device*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct ifaddrmsg* nlmsg_data (struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlmsg_parse (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int rtnl_unicast (struct sk_buff*,struct net*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet6_rtm_getaddr(struct sk_buff *in_skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(in_skb->sk);
	struct ifaddrmsg *ifm;
	struct nlattr *tb[IFA_MAX+1];
	struct in6_addr *addr = NULL, *peer;
	struct net_device *dev = NULL;
	struct inet6_ifaddr *ifa;
	struct sk_buff *skb;
	int err;

	err = nlmsg_parse(nlh, sizeof(*ifm), tb, IFA_MAX, ifa_ipv6_policy,
			  extack);
	if (err < 0)
		return err;

	addr = extract_addr(tb[IFA_ADDRESS], tb[IFA_LOCAL], &peer);
	if (!addr)
		return -EINVAL;

	ifm = nlmsg_data(nlh);
	if (ifm->ifa_index)
		dev = dev_get_by_index(net, ifm->ifa_index);

	ifa = ipv6_get_ifaddr(net, addr, dev, 1);
	if (!ifa) {
		err = -EADDRNOTAVAIL;
		goto errout;
	}

	skb = nlmsg_new(inet6_ifaddr_msgsize(), GFP_KERNEL);
	if (!skb) {
		err = -ENOBUFS;
		goto errout_ifa;
	}

	err = inet6_fill_ifaddr(skb, ifa, NETLINK_CB(in_skb).portid,
				nlh->nlmsg_seq, RTM_NEWADDR, 0);
	if (err < 0) {
		/* -EMSGSIZE implies BUG in inet6_ifaddr_msgsize() */
		WARN_ON(err == -EMSGSIZE);
		kfree_skb(skb);
		goto errout_ifa;
	}
	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
errout_ifa:
	in6_ifa_put(ifa);
errout:
	if (dev)
		dev_put(dev);
	return err;
}
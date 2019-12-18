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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct net_device {int ifindex; } ;
struct inet6_fill_args {scalar_t__ netnsid; int /*<<< orphan*/  flags; int /*<<< orphan*/  event; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct ifaddrmsg {int dummy; } ;
struct ifacaddr6 {int /*<<< orphan*/  aca_tstamp; int /*<<< orphan*/  aca_cstamp; int /*<<< orphan*/  aca_addr; int /*<<< orphan*/  aca_rt; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFA_ANYCAST ; 
 int /*<<< orphan*/  IFA_F_PERMANENT ; 
 int IFA_SITE ; 
 int /*<<< orphan*/  IFA_TARGET_NETNSID ; 
 int /*<<< orphan*/  INFINITY_LIFE_TIME ; 
 int /*<<< orphan*/  RT_SCOPE_SITE ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 struct net_device* fib6_info_nh_dev (int /*<<< orphan*/ ) ; 
 int ipv6_addr_scope (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_in6_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_s32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ put_cacheinfo (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ifaddrmsg (struct nlmsghdr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int inet6_fill_ifacaddr(struct sk_buff *skb, struct ifacaddr6 *ifaca,
			       struct inet6_fill_args *args)
{
	struct net_device *dev = fib6_info_nh_dev(ifaca->aca_rt);
	int ifindex = dev ? dev->ifindex : 1;
	struct nlmsghdr  *nlh;
	u8 scope = RT_SCOPE_UNIVERSE;

	if (ipv6_addr_scope(&ifaca->aca_addr) & IFA_SITE)
		scope = RT_SCOPE_SITE;

	nlh = nlmsg_put(skb, args->portid, args->seq, args->event,
			sizeof(struct ifaddrmsg), args->flags);
	if (!nlh)
		return -EMSGSIZE;

	if (args->netnsid >= 0 &&
	    nla_put_s32(skb, IFA_TARGET_NETNSID, args->netnsid))
		return -EMSGSIZE;

	put_ifaddrmsg(nlh, 128, IFA_F_PERMANENT, scope, ifindex);
	if (nla_put_in6_addr(skb, IFA_ANYCAST, &ifaca->aca_addr) < 0 ||
	    put_cacheinfo(skb, ifaca->aca_cstamp, ifaca->aca_tstamp,
			  INFINITY_LIFE_TIME, INFINITY_LIFE_TIME) < 0) {
		nlmsg_cancel(skb, nlh);
		return -EMSGSIZE;
	}

	nlmsg_end(skb, nlh);
	return 0;
}
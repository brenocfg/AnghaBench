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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct inet6_ifaddr {int flags; scalar_t__ prefered_lft; scalar_t__ valid_lft; long tstamp; int rt_priority; int /*<<< orphan*/  cstamp; int /*<<< orphan*/  addr; int /*<<< orphan*/  peer_addr; TYPE_2__* idev; int /*<<< orphan*/  scope; int /*<<< orphan*/  prefix_len; } ;
struct inet6_fill_args {scalar_t__ netnsid; int /*<<< orphan*/  flags; int /*<<< orphan*/  event; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct ifaddrmsg {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 long HZ ; 
 int /*<<< orphan*/  IFA_ADDRESS ; 
 int /*<<< orphan*/  IFA_FLAGS ; 
 int IFA_F_PERMANENT ; 
 int /*<<< orphan*/  IFA_LOCAL ; 
 int /*<<< orphan*/  IFA_RT_PRIORITY ; 
 int /*<<< orphan*/  IFA_TARGET_NETNSID ; 
 scalar_t__ INFINITY_LIFE_TIME ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 
 long jiffies ; 
 scalar_t__ nla_put_in6_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_s32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ put_cacheinfo (struct sk_buff*,int /*<<< orphan*/ ,long,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  put_ifaddrmsg (struct nlmsghdr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_scope (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet6_fill_ifaddr(struct sk_buff *skb, struct inet6_ifaddr *ifa,
			     struct inet6_fill_args *args)
{
	struct nlmsghdr  *nlh;
	u32 preferred, valid;

	nlh = nlmsg_put(skb, args->portid, args->seq, args->event,
			sizeof(struct ifaddrmsg), args->flags);
	if (!nlh)
		return -EMSGSIZE;

	put_ifaddrmsg(nlh, ifa->prefix_len, ifa->flags, rt_scope(ifa->scope),
		      ifa->idev->dev->ifindex);

	if (args->netnsid >= 0 &&
	    nla_put_s32(skb, IFA_TARGET_NETNSID, args->netnsid))
		goto error;

	if (!((ifa->flags&IFA_F_PERMANENT) &&
	      (ifa->prefered_lft == INFINITY_LIFE_TIME))) {
		preferred = ifa->prefered_lft;
		valid = ifa->valid_lft;
		if (preferred != INFINITY_LIFE_TIME) {
			long tval = (jiffies - ifa->tstamp)/HZ;
			if (preferred > tval)
				preferred -= tval;
			else
				preferred = 0;
			if (valid != INFINITY_LIFE_TIME) {
				if (valid > tval)
					valid -= tval;
				else
					valid = 0;
			}
		}
	} else {
		preferred = INFINITY_LIFE_TIME;
		valid = INFINITY_LIFE_TIME;
	}

	if (!ipv6_addr_any(&ifa->peer_addr)) {
		if (nla_put_in6_addr(skb, IFA_LOCAL, &ifa->addr) < 0 ||
		    nla_put_in6_addr(skb, IFA_ADDRESS, &ifa->peer_addr) < 0)
			goto error;
	} else
		if (nla_put_in6_addr(skb, IFA_ADDRESS, &ifa->addr) < 0)
			goto error;

	if (ifa->rt_priority &&
	    nla_put_u32(skb, IFA_RT_PRIORITY, ifa->rt_priority))
		goto error;

	if (put_cacheinfo(skb, ifa->cstamp, ifa->tstamp, preferred, valid) < 0)
		goto error;

	if (nla_put_u32(skb, IFA_FLAGS, ifa->flags) < 0)
		goto error;

	nlmsg_end(skb, nlh);
	return 0;

error:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}
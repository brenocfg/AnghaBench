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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ifaddrmsg {int /*<<< orphan*/  ifa_prefixlen; int /*<<< orphan*/  ifa_index; int /*<<< orphan*/  ifa_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IFA_ADDRESS ; 
 size_t IFA_FLAGS ; 
 int /*<<< orphan*/  IFA_F_MANAGETEMPADDR ; 
 size_t IFA_LOCAL ; 
 int /*<<< orphan*/  IFA_MAX ; 
 struct in6_addr* extract_addr (struct nlattr*,struct nlattr*,struct in6_addr**) ; 
 int /*<<< orphan*/  ifa_ipv6_policy ; 
 int inet6_addr_del (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in6_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 struct ifaddrmsg* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse_deprecated (struct nlmsghdr*,int,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
inet6_rtm_deladdr(struct sk_buff *skb, struct nlmsghdr *nlh,
		  struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	struct ifaddrmsg *ifm;
	struct nlattr *tb[IFA_MAX+1];
	struct in6_addr *pfx, *peer_pfx;
	u32 ifa_flags;
	int err;

	err = nlmsg_parse_deprecated(nlh, sizeof(*ifm), tb, IFA_MAX,
				     ifa_ipv6_policy, extack);
	if (err < 0)
		return err;

	ifm = nlmsg_data(nlh);
	pfx = extract_addr(tb[IFA_ADDRESS], tb[IFA_LOCAL], &peer_pfx);
	if (!pfx)
		return -EINVAL;

	ifa_flags = tb[IFA_FLAGS] ? nla_get_u32(tb[IFA_FLAGS]) : ifm->ifa_flags;

	/* We ignore other flags so far. */
	ifa_flags &= IFA_F_MANAGETEMPADDR;

	return inet6_addr_del(net, ifm->ifa_index, ifa_flags, pfx,
			      ifm->ifa_prefixlen);
}
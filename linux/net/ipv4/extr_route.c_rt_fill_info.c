#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct rtvia {int* rtvia_addr; scalar_t__ rtvia_family; } ;
struct rtmsg {int rtm_dst_len; int rtm_src_len; int rtm_table; int rtm_flags; int /*<<< orphan*/  rtm_protocol; int /*<<< orphan*/  rtm_scope; int /*<<< orphan*/  rtm_type; int /*<<< orphan*/  rtm_tos; scalar_t__ rtm_family; } ;
struct TYPE_6__ {int tclassid; unsigned long expires; int error; TYPE_1__* dev; } ;
struct rtable {int rt_flags; scalar_t__ rt_gw_family; scalar_t__ rt_gw4; int rt_pmtu; TYPE_2__ dst; scalar_t__ rt_mtu_locked; int /*<<< orphan*/  rt_gw6; scalar_t__ rt_uses_gateway; int /*<<< orphan*/  rt_type; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct flowi4 {scalar_t__ saddr; int flowi4_mark; int flowi4_iif; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi4_uid; int /*<<< orphan*/  flowi4_tos; } ;
typedef  int /*<<< orphan*/  metrics ;
typedef  scalar_t__ __be32 ;
struct TYPE_7__ {int flags; } ;
struct TYPE_5__ {int ifindex; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int BIT (int) ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  INVALID_UID ; 
 TYPE_4__* IPCB (struct sk_buff*) ; 
 int IPSKB_DOREDIRECT ; 
 scalar_t__ IPV4_DEVCONF_ALL (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC_FORWARDING ; 
 int RTAX_LOCK ; 
 int RTAX_MAX ; 
 int RTAX_MTU ; 
 int /*<<< orphan*/  RTA_DST ; 
 int /*<<< orphan*/  RTA_FLOW ; 
 int /*<<< orphan*/  RTA_GATEWAY ; 
 int /*<<< orphan*/  RTA_IIF ; 
 int /*<<< orphan*/  RTA_MARK ; 
 int /*<<< orphan*/  RTA_OIF ; 
 int /*<<< orphan*/  RTA_PREFSRC ; 
 int /*<<< orphan*/  RTA_SRC ; 
 int /*<<< orphan*/  RTA_TABLE ; 
 int /*<<< orphan*/  RTA_UID ; 
 int /*<<< orphan*/  RTA_VIA ; 
 int RTCF_DOREDIRECT ; 
 int RTCF_NOTIFY ; 
 int RTM_F_CLONED ; 
 int RTM_F_NOTIFY ; 
 int /*<<< orphan*/  RTM_NEWROUTE ; 
 int /*<<< orphan*/  RTPROT_UNSPEC ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int RT_TABLE_COMPAT ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/ * dst_metrics_ptr (TYPE_2__*) ; 
 int from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipmr_get_route (struct net*,struct sk_buff*,scalar_t__,int /*<<< orphan*/ ,struct rtmsg*,int) ; 
 int /*<<< orphan*/  ipv4_is_local_multicast (scalar_t__) ; 
 scalar_t__ ipv4_is_multicast (scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 struct rtvia* nla_data (struct nlattr*) ; 
 scalar_t__ nla_put_in_addr (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct rtmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int,int,int /*<<< orphan*/ ,int,unsigned int) ; 
 scalar_t__ rt_is_input_route (struct rtable*) ; 
 scalar_t__ rtnetlink_put_metrics (struct sk_buff*,int*) ; 
 scalar_t__ rtnl_put_cacheinfo (struct sk_buff*,TYPE_2__*,int /*<<< orphan*/ ,unsigned long,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt_fill_info(struct net *net, __be32 dst, __be32 src,
			struct rtable *rt, u32 table_id, struct flowi4 *fl4,
			struct sk_buff *skb, u32 portid, u32 seq,
			unsigned int flags)
{
	struct rtmsg *r;
	struct nlmsghdr *nlh;
	unsigned long expires = 0;
	u32 error;
	u32 metrics[RTAX_MAX];

	nlh = nlmsg_put(skb, portid, seq, RTM_NEWROUTE, sizeof(*r), flags);
	if (!nlh)
		return -EMSGSIZE;

	r = nlmsg_data(nlh);
	r->rtm_family	 = AF_INET;
	r->rtm_dst_len	= 32;
	r->rtm_src_len	= 0;
	r->rtm_tos	= fl4 ? fl4->flowi4_tos : 0;
	r->rtm_table	= table_id < 256 ? table_id : RT_TABLE_COMPAT;
	if (nla_put_u32(skb, RTA_TABLE, table_id))
		goto nla_put_failure;
	r->rtm_type	= rt->rt_type;
	r->rtm_scope	= RT_SCOPE_UNIVERSE;
	r->rtm_protocol = RTPROT_UNSPEC;
	r->rtm_flags	= (rt->rt_flags & ~0xFFFF) | RTM_F_CLONED;
	if (rt->rt_flags & RTCF_NOTIFY)
		r->rtm_flags |= RTM_F_NOTIFY;
	if (IPCB(skb)->flags & IPSKB_DOREDIRECT)
		r->rtm_flags |= RTCF_DOREDIRECT;

	if (nla_put_in_addr(skb, RTA_DST, dst))
		goto nla_put_failure;
	if (src) {
		r->rtm_src_len = 32;
		if (nla_put_in_addr(skb, RTA_SRC, src))
			goto nla_put_failure;
	}
	if (rt->dst.dev &&
	    nla_put_u32(skb, RTA_OIF, rt->dst.dev->ifindex))
		goto nla_put_failure;
#ifdef CONFIG_IP_ROUTE_CLASSID
	if (rt->dst.tclassid &&
	    nla_put_u32(skb, RTA_FLOW, rt->dst.tclassid))
		goto nla_put_failure;
#endif
	if (fl4 && !rt_is_input_route(rt) &&
	    fl4->saddr != src) {
		if (nla_put_in_addr(skb, RTA_PREFSRC, fl4->saddr))
			goto nla_put_failure;
	}
	if (rt->rt_uses_gateway) {
		if (rt->rt_gw_family == AF_INET &&
		    nla_put_in_addr(skb, RTA_GATEWAY, rt->rt_gw4)) {
			goto nla_put_failure;
		} else if (rt->rt_gw_family == AF_INET6) {
			int alen = sizeof(struct in6_addr);
			struct nlattr *nla;
			struct rtvia *via;

			nla = nla_reserve(skb, RTA_VIA, alen + 2);
			if (!nla)
				goto nla_put_failure;

			via = nla_data(nla);
			via->rtvia_family = AF_INET6;
			memcpy(via->rtvia_addr, &rt->rt_gw6, alen);
		}
	}

	expires = rt->dst.expires;
	if (expires) {
		unsigned long now = jiffies;

		if (time_before(now, expires))
			expires -= now;
		else
			expires = 0;
	}

	memcpy(metrics, dst_metrics_ptr(&rt->dst), sizeof(metrics));
	if (rt->rt_pmtu && expires)
		metrics[RTAX_MTU - 1] = rt->rt_pmtu;
	if (rt->rt_mtu_locked && expires)
		metrics[RTAX_LOCK - 1] |= BIT(RTAX_MTU);
	if (rtnetlink_put_metrics(skb, metrics) < 0)
		goto nla_put_failure;

	if (fl4) {
		if (fl4->flowi4_mark &&
		    nla_put_u32(skb, RTA_MARK, fl4->flowi4_mark))
			goto nla_put_failure;

		if (!uid_eq(fl4->flowi4_uid, INVALID_UID) &&
		    nla_put_u32(skb, RTA_UID,
				from_kuid_munged(current_user_ns(),
						 fl4->flowi4_uid)))
			goto nla_put_failure;

		if (rt_is_input_route(rt)) {
#ifdef CONFIG_IP_MROUTE
			if (ipv4_is_multicast(dst) &&
			    !ipv4_is_local_multicast(dst) &&
			    IPV4_DEVCONF_ALL(net, MC_FORWARDING)) {
				int err = ipmr_get_route(net, skb,
							 fl4->saddr, fl4->daddr,
							 r, portid);

				if (err <= 0) {
					if (err == 0)
						return 0;
					goto nla_put_failure;
				}
			} else
#endif
				if (nla_put_u32(skb, RTA_IIF, fl4->flowi4_iif))
					goto nla_put_failure;
		}
	}

	error = rt->dst.error;

	if (rtnl_put_cacheinfo(skb, &rt->dst, 0, expires, error) < 0)
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}
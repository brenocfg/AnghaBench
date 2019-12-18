#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct in6_addr {int dummy; } ;
struct rt6_info {int rt6i_flags; int /*<<< orphan*/  dst; struct in6_addr rt6i_gateway; int /*<<< orphan*/  from; } ;
struct rd_msg {int /*<<< orphan*/  dest; int /*<<< orphan*/  target; int /*<<< orphan*/  opt; } ;
struct netevent_redirect {struct neighbour* neigh; int /*<<< orphan*/ * daddr; int /*<<< orphan*/ * new; int /*<<< orphan*/ * old; } ;
struct neighbour {scalar_t__ primary_key; } ;
struct ndisc_options {scalar_t__ nd_opts_tgt_lladdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  accept_redirects; scalar_t__ forwarding; } ;
struct inet6_dev {TYPE_1__ cnf; } ;
struct fib6_result {TYPE_2__* f6i; int /*<<< orphan*/  fib6_type; int /*<<< orphan*/  fib6_flags; scalar_t__ nh; } ;
struct fib6_nh_match_arg {scalar_t__ match; struct in6_addr* gw; int /*<<< orphan*/  dev; } ;
struct dst_entry {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  fib6_type; int /*<<< orphan*/  fib6_flags; scalar_t__ fib6_nh; scalar_t__ nh; } ;

/* Variables and functions */
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_UNICAST ; 
 int /*<<< orphan*/  NDISC_REDIRECT ; 
 int NEIGH_UPDATE_F_ISROUTER ; 
 int NEIGH_UPDATE_F_OVERRIDE ; 
 int NEIGH_UPDATE_F_OVERRIDE_ISROUTER ; 
 int NEIGH_UPDATE_F_WEAK_OVERRIDE ; 
 int /*<<< orphan*/  NETEVENT_REDIRECT ; 
 int /*<<< orphan*/  NUD_STALE ; 
 int RTF_CACHE ; 
 int RTF_DYNAMIC ; 
 int RTF_GATEWAY ; 
 int RTF_REJECT ; 
 int RTF_UP ; 
 struct inet6_dev* __in6_dev_get (int /*<<< orphan*/ ) ; 
 struct neighbour* __neigh_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  call_netevent_notifiers (int /*<<< orphan*/ ,struct netevent_redirect*) ; 
 int /*<<< orphan*/  dst_confirm_neigh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release_immediate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fib6_nh_find_match ; 
 scalar_t__ icmp6_hdr (struct sk_buff*) ; 
 struct rt6_info* ip6_rt_cache_alloc (struct fib6_result*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ipv6_addr_is_multicast (int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  nd_tbl ; 
 int /*<<< orphan*/ * ndisc_opt_addr_data (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndisc_parse_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ndisc_options*) ; 
 int /*<<< orphan*/  ndisc_update (int /*<<< orphan*/ ,struct neighbour*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ndisc_options*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*) ; 
 int /*<<< orphan*/  nexthop_for_each_fib6_nh (scalar_t__,int /*<<< orphan*/ ,struct fib6_nh_match_arg*) ; 
 TYPE_2__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ rt6_insert_exception (struct rt6_info*,struct fib6_result*) ; 
 int skb_tail_pointer (struct sk_buff*) ; 
 int skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static void rt6_do_redirect(struct dst_entry *dst, struct sock *sk, struct sk_buff *skb)
{
	struct netevent_redirect netevent;
	struct rt6_info *rt, *nrt = NULL;
	struct fib6_result res = {};
	struct ndisc_options ndopts;
	struct inet6_dev *in6_dev;
	struct neighbour *neigh;
	struct rd_msg *msg;
	int optlen, on_link;
	u8 *lladdr;

	optlen = skb_tail_pointer(skb) - skb_transport_header(skb);
	optlen -= sizeof(*msg);

	if (optlen < 0) {
		net_dbg_ratelimited("rt6_do_redirect: packet too short\n");
		return;
	}

	msg = (struct rd_msg *)icmp6_hdr(skb);

	if (ipv6_addr_is_multicast(&msg->dest)) {
		net_dbg_ratelimited("rt6_do_redirect: destination address is multicast\n");
		return;
	}

	on_link = 0;
	if (ipv6_addr_equal(&msg->dest, &msg->target)) {
		on_link = 1;
	} else if (ipv6_addr_type(&msg->target) !=
		   (IPV6_ADDR_UNICAST|IPV6_ADDR_LINKLOCAL)) {
		net_dbg_ratelimited("rt6_do_redirect: target address is not link-local unicast\n");
		return;
	}

	in6_dev = __in6_dev_get(skb->dev);
	if (!in6_dev)
		return;
	if (in6_dev->cnf.forwarding || !in6_dev->cnf.accept_redirects)
		return;

	/* RFC2461 8.1:
	 *	The IP source address of the Redirect MUST be the same as the current
	 *	first-hop router for the specified ICMP Destination Address.
	 */

	if (!ndisc_parse_options(skb->dev, msg->opt, optlen, &ndopts)) {
		net_dbg_ratelimited("rt6_redirect: invalid ND options\n");
		return;
	}

	lladdr = NULL;
	if (ndopts.nd_opts_tgt_lladdr) {
		lladdr = ndisc_opt_addr_data(ndopts.nd_opts_tgt_lladdr,
					     skb->dev);
		if (!lladdr) {
			net_dbg_ratelimited("rt6_redirect: invalid link-layer address length\n");
			return;
		}
	}

	rt = (struct rt6_info *) dst;
	if (rt->rt6i_flags & RTF_REJECT) {
		net_dbg_ratelimited("rt6_redirect: source isn't a valid nexthop for redirect target\n");
		return;
	}

	/* Redirect received -> path was valid.
	 * Look, redirects are sent only in response to data packets,
	 * so that this nexthop apparently is reachable. --ANK
	 */
	dst_confirm_neigh(&rt->dst, &ipv6_hdr(skb)->saddr);

	neigh = __neigh_lookup(&nd_tbl, &msg->target, skb->dev, 1);
	if (!neigh)
		return;

	/*
	 *	We have finally decided to accept it.
	 */

	ndisc_update(skb->dev, neigh, lladdr, NUD_STALE,
		     NEIGH_UPDATE_F_WEAK_OVERRIDE|
		     NEIGH_UPDATE_F_OVERRIDE|
		     (on_link ? 0 : (NEIGH_UPDATE_F_OVERRIDE_ISROUTER|
				     NEIGH_UPDATE_F_ISROUTER)),
		     NDISC_REDIRECT, &ndopts);

	rcu_read_lock();
	res.f6i = rcu_dereference(rt->from);
	if (!res.f6i)
		goto out;

	if (res.f6i->nh) {
		struct fib6_nh_match_arg arg = {
			.dev = dst->dev,
			.gw = &rt->rt6i_gateway,
		};

		nexthop_for_each_fib6_nh(res.f6i->nh,
					 fib6_nh_find_match, &arg);

		/* fib6_info uses a nexthop that does not have fib6_nh
		 * using the dst->dev. Should be impossible
		 */
		if (!arg.match)
			goto out;
		res.nh = arg.match;
	} else {
		res.nh = res.f6i->fib6_nh;
	}

	res.fib6_flags = res.f6i->fib6_flags;
	res.fib6_type = res.f6i->fib6_type;
	nrt = ip6_rt_cache_alloc(&res, &msg->dest, NULL);
	if (!nrt)
		goto out;

	nrt->rt6i_flags = RTF_GATEWAY|RTF_UP|RTF_DYNAMIC|RTF_CACHE;
	if (on_link)
		nrt->rt6i_flags &= ~RTF_GATEWAY;

	nrt->rt6i_gateway = *(struct in6_addr *)neigh->primary_key;

	/* rt6_insert_exception() will take care of duplicated exceptions */
	if (rt6_insert_exception(nrt, &res)) {
		dst_release_immediate(&nrt->dst);
		goto out;
	}

	netevent.old = &rt->dst;
	netevent.new = &nrt->dst;
	netevent.daddr = &msg->dest;
	netevent.neigh = neigh;
	call_netevent_notifiers(NETEVENT_REDIRECT, &netevent);

out:
	rcu_read_unlock();
	neigh_release(neigh);
}
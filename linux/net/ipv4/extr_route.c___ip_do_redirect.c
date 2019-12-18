#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; struct net_device* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  obsolete; int /*<<< orphan*/  dev; } ;
struct rtable {scalar_t__ rt_gw_family; scalar_t__ rt_gw4; TYPE_2__ dst; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;
struct neighbour {int nud_state; } ;
struct iphdr {scalar_t__ daddr; scalar_t__ saddr; } ;
struct in_device {int dummy; } ;
struct flowi4 {int /*<<< orphan*/  daddr; } ;
struct fib_result {int dummy; } ;
struct fib_nh_common {int dummy; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_5__ {scalar_t__ gateway; } ;
struct TYPE_8__ {int code; TYPE_1__ un; } ;
struct TYPE_7__ {scalar_t__ saddr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  DST_OBSOLETE_KILL ; 
 struct fib_nh_common* FIB_RES_NHC (struct fib_result) ; 
#define  ICMP_REDIR_HOST 131 
#define  ICMP_REDIR_HOSTTOS 130 
#define  ICMP_REDIR_NET 129 
#define  ICMP_REDIR_NETTOS 128 
 scalar_t__ IN_DEV_LOG_MARTIANS (struct in_device*) ; 
 int /*<<< orphan*/  IN_DEV_RX_REDIRECTS (struct in_device*) ; 
 scalar_t__ IN_DEV_SEC_REDIRECTS (struct in_device*) ; 
 int /*<<< orphan*/  IN_DEV_SHARED_MEDIA (struct in_device*) ; 
 int /*<<< orphan*/  IS_ERR (struct neighbour*) ; 
 int /*<<< orphan*/  NETEVENT_NEIGH_UPDATE ; 
 int NUD_VALID ; 
 scalar_t__ RTN_UNICAST ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 
 struct neighbour* __ipv4_neigh_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  arp_tbl ; 
 int /*<<< orphan*/  call_netevent_notifiers (int /*<<< orphan*/ ,struct neighbour*) ; 
 struct net* dev_net (struct net_device*) ; 
 scalar_t__ fib_lookup (struct net*,struct flowi4*,struct fib_result*,int /*<<< orphan*/ ) ; 
 TYPE_4__* icmp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  inet_addr_onlink (struct in_device*,scalar_t__,scalar_t__) ; 
 scalar_t__ inet_addr_type (struct net*,scalar_t__) ; 
 scalar_t__ ip_fib_check_default (scalar_t__,struct net_device*) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ip_rt_gc_timeout ; 
 scalar_t__ ipv4_is_lbcast (scalar_t__) ; 
 scalar_t__ ipv4_is_multicast (scalar_t__) ; 
 scalar_t__ ipv4_is_zeronet (scalar_t__) ; 
 scalar_t__ jiffies ; 
 struct neighbour* neigh_create (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  update_or_create_fnhe (struct fib_nh_common*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void __ip_do_redirect(struct rtable *rt, struct sk_buff *skb, struct flowi4 *fl4,
			     bool kill_route)
{
	__be32 new_gw = icmp_hdr(skb)->un.gateway;
	__be32 old_gw = ip_hdr(skb)->saddr;
	struct net_device *dev = skb->dev;
	struct in_device *in_dev;
	struct fib_result res;
	struct neighbour *n;
	struct net *net;

	switch (icmp_hdr(skb)->code & 7) {
	case ICMP_REDIR_NET:
	case ICMP_REDIR_NETTOS:
	case ICMP_REDIR_HOST:
	case ICMP_REDIR_HOSTTOS:
		break;

	default:
		return;
	}

	if (rt->rt_gw_family != AF_INET || rt->rt_gw4 != old_gw)
		return;

	in_dev = __in_dev_get_rcu(dev);
	if (!in_dev)
		return;

	net = dev_net(dev);
	if (new_gw == old_gw || !IN_DEV_RX_REDIRECTS(in_dev) ||
	    ipv4_is_multicast(new_gw) || ipv4_is_lbcast(new_gw) ||
	    ipv4_is_zeronet(new_gw))
		goto reject_redirect;

	if (!IN_DEV_SHARED_MEDIA(in_dev)) {
		if (!inet_addr_onlink(in_dev, new_gw, old_gw))
			goto reject_redirect;
		if (IN_DEV_SEC_REDIRECTS(in_dev) && ip_fib_check_default(new_gw, dev))
			goto reject_redirect;
	} else {
		if (inet_addr_type(net, new_gw) != RTN_UNICAST)
			goto reject_redirect;
	}

	n = __ipv4_neigh_lookup(rt->dst.dev, new_gw);
	if (!n)
		n = neigh_create(&arp_tbl, &new_gw, rt->dst.dev);
	if (!IS_ERR(n)) {
		if (!(n->nud_state & NUD_VALID)) {
			neigh_event_send(n, NULL);
		} else {
			if (fib_lookup(net, fl4, &res, 0) == 0) {
				struct fib_nh_common *nhc = FIB_RES_NHC(res);

				update_or_create_fnhe(nhc, fl4->daddr, new_gw,
						0, false,
						jiffies + ip_rt_gc_timeout);
			}
			if (kill_route)
				rt->dst.obsolete = DST_OBSOLETE_KILL;
			call_netevent_notifiers(NETEVENT_NEIGH_UPDATE, n);
		}
		neigh_release(n);
	}
	return;

reject_redirect:
#ifdef CONFIG_IP_ROUTE_VERBOSE
	if (IN_DEV_LOG_MARTIANS(in_dev)) {
		const struct iphdr *iph = (const struct iphdr *) skb->data;
		__be32 daddr = iph->daddr;
		__be32 saddr = iph->saddr;

		net_info_ratelimited("Redirect from %pI4 on %s about %pI4 ignored\n"
				     "  Advised path = %pI4 -> %pI4\n",
				     &old_gw, dev->name, &new_gw,
				     &saddr, &daddr);
	}
#endif
	;
}
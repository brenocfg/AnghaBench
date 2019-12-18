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
struct sock {int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {int /*<<< orphan*/  mark; int /*<<< orphan*/  sk; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct flowi6 {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi6_uid; int /*<<< orphan*/  flowi6_mark; int /*<<< orphan*/  flowi6_oif; } ;
struct dst_entry {int error; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {unsigned int hard_header_len; int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HH_DATA_ALIGN (unsigned int) ; 
 TYPE_3__* IP6CB (struct sk_buff*) ; 
 int IP6SKB_XFRM_TRANSFORMED ; 
 int /*<<< orphan*/  IP6_INC_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTNOROUTES ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_MULTICAST ; 
 scalar_t__ IS_ERR (struct dst_entry*) ; 
 int PTR_ERR (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  flowi6_to_flowi (struct flowi6*) ; 
 int /*<<< orphan*/  ip6_dst_idev (struct dst_entry*) ; 
 struct dst_entry* ip6_route_output (struct net*,struct sock*,struct flowi6*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sock* sk_to_full_sk (int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net_uid (struct net*,struct sock*) ; 
 scalar_t__ xfrm_decode_session (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dst_entry* xfrm_lookup (struct net*,struct dst_entry*,int /*<<< orphan*/ ,struct sock*,int /*<<< orphan*/ ) ; 

int ip6_route_me_harder(struct net *net, struct sk_buff *skb)
{
	const struct ipv6hdr *iph = ipv6_hdr(skb);
	struct sock *sk = sk_to_full_sk(skb->sk);
	unsigned int hh_len;
	struct dst_entry *dst;
	int strict = (ipv6_addr_type(&iph->daddr) &
		      (IPV6_ADDR_MULTICAST | IPV6_ADDR_LINKLOCAL));
	struct flowi6 fl6 = {
		.flowi6_oif = sk && sk->sk_bound_dev_if ? sk->sk_bound_dev_if :
			strict ? skb_dst(skb)->dev->ifindex : 0,
		.flowi6_mark = skb->mark,
		.flowi6_uid = sock_net_uid(net, sk),
		.daddr = iph->daddr,
		.saddr = iph->saddr,
	};
	int err;

	dst = ip6_route_output(net, sk, &fl6);
	err = dst->error;
	if (err) {
		IP6_INC_STATS(net, ip6_dst_idev(dst), IPSTATS_MIB_OUTNOROUTES);
		net_dbg_ratelimited("ip6_route_me_harder: No more route\n");
		dst_release(dst);
		return err;
	}

	/* Drop old route. */
	skb_dst_drop(skb);

	skb_dst_set(skb, dst);

#ifdef CONFIG_XFRM
	if (!(IP6CB(skb)->flags & IP6SKB_XFRM_TRANSFORMED) &&
	    xfrm_decode_session(skb, flowi6_to_flowi(&fl6), AF_INET6) == 0) {
		skb_dst_set(skb, NULL);
		dst = xfrm_lookup(net, dst, flowi6_to_flowi(&fl6), sk, 0);
		if (IS_ERR(dst))
			return PTR_ERR(dst);
		skb_dst_set(skb, dst);
	}
#endif

	/* Change in oif may mean change in hh_len. */
	hh_len = skb_dst(skb)->dev->hard_header_len;
	if (skb_headroom(skb) < hh_len &&
	    pskb_expand_head(skb, HH_DATA_ALIGN(hh_len - skb_headroom(skb)),
			     0, GFP_ATOMIC))
		return -ENOMEM;

	return 0;
}
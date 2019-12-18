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
typedef  int u32 ;
struct sock {int dummy; } ;
struct sk_buff {int len; int priority; int /*<<< orphan*/  dev; scalar_t__ ignore_df; int /*<<< orphan*/  mark; void* protocol; scalar_t__ sk; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ipv6hdr {int hop_limit; struct in6_addr daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  nexthdr; void* payload_len; } ;
struct ipv6_txoptions {scalar_t__ opt_nflen; scalar_t__ opt_flen; } ;
struct ipv6_pinfo {int hop_limit; } ;
struct flowi6 {int /*<<< orphan*/  saddr; int /*<<< orphan*/  flowlabel; int /*<<< orphan*/  flowi6_proto; struct in6_addr daddr; } ;
struct dst_entry {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ETH_P_IPV6 ; 
 int /*<<< orphan*/  IP6_INC_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP6_UPD_PO_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IPSTATS_MIB_FRAGFAILS ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUT ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 int LL_RESERVED_SPACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,struct sock*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_LOCAL_OUT ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_output ; 
 void* htons (int) ; 
 struct ipv6_pinfo* inet6_sk (struct sock const*) ; 
 int /*<<< orphan*/  ip6_autoflowlabel (struct net*,struct ipv6_pinfo const*) ; 
 int ip6_dst_hoplimit (struct dst_entry*) ; 
 int /*<<< orphan*/  ip6_dst_idev (struct dst_entry*) ; 
 int /*<<< orphan*/  ip6_flow_hdr (struct ipv6hdr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_make_flowlabel (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flowi6*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_local_error (struct sock*,int,struct flowi6*,int) ; 
 int /*<<< orphan*/  ipv6_push_frag_opts (struct sk_buff*,struct ipv6_txoptions*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_push_nfrag_opts (struct sk_buff*,struct ipv6_txoptions*,int /*<<< orphan*/ *,struct in6_addr**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* l3mdev_ip6_out (struct sock*,struct sk_buff*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,scalar_t__) ; 
 struct net* sock_net (struct sock const*) ; 
 scalar_t__ unlikely (int) ; 

int ip6_xmit(const struct sock *sk, struct sk_buff *skb, struct flowi6 *fl6,
	     __u32 mark, struct ipv6_txoptions *opt, int tclass, u32 priority)
{
	struct net *net = sock_net(sk);
	const struct ipv6_pinfo *np = inet6_sk(sk);
	struct in6_addr *first_hop = &fl6->daddr;
	struct dst_entry *dst = skb_dst(skb);
	unsigned int head_room;
	struct ipv6hdr *hdr;
	u8  proto = fl6->flowi6_proto;
	int seg_len = skb->len;
	int hlimit = -1;
	u32 mtu;

	head_room = sizeof(struct ipv6hdr) + LL_RESERVED_SPACE(dst->dev);
	if (opt)
		head_room += opt->opt_nflen + opt->opt_flen;

	if (unlikely(skb_headroom(skb) < head_room)) {
		struct sk_buff *skb2 = skb_realloc_headroom(skb, head_room);
		if (!skb2) {
			IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
				      IPSTATS_MIB_OUTDISCARDS);
			kfree_skb(skb);
			return -ENOBUFS;
		}
		if (skb->sk)
			skb_set_owner_w(skb2, skb->sk);
		consume_skb(skb);
		skb = skb2;
	}

	if (opt) {
		seg_len += opt->opt_nflen + opt->opt_flen;

		if (opt->opt_flen)
			ipv6_push_frag_opts(skb, opt, &proto);

		if (opt->opt_nflen)
			ipv6_push_nfrag_opts(skb, opt, &proto, &first_hop,
					     &fl6->saddr);
	}

	skb_push(skb, sizeof(struct ipv6hdr));
	skb_reset_network_header(skb);
	hdr = ipv6_hdr(skb);

	/*
	 *	Fill in the IPv6 header
	 */
	if (np)
		hlimit = np->hop_limit;
	if (hlimit < 0)
		hlimit = ip6_dst_hoplimit(dst);

	ip6_flow_hdr(hdr, tclass, ip6_make_flowlabel(net, skb, fl6->flowlabel,
				ip6_autoflowlabel(net, np), fl6));

	hdr->payload_len = htons(seg_len);
	hdr->nexthdr = proto;
	hdr->hop_limit = hlimit;

	hdr->saddr = fl6->saddr;
	hdr->daddr = *first_hop;

	skb->protocol = htons(ETH_P_IPV6);
	skb->priority = priority;
	skb->mark = mark;

	mtu = dst_mtu(dst);
	if ((skb->len <= mtu) || skb->ignore_df || skb_is_gso(skb)) {
		IP6_UPD_PO_STATS(net, ip6_dst_idev(skb_dst(skb)),
			      IPSTATS_MIB_OUT, skb->len);

		/* if egress device is enslaved to an L3 master device pass the
		 * skb to its handler for processing
		 */
		skb = l3mdev_ip6_out((struct sock *)sk, skb);
		if (unlikely(!skb))
			return 0;

		/* hooks should never assume socket lock is held.
		 * we promote our socket to non const
		 */
		return NF_HOOK(NFPROTO_IPV6, NF_INET_LOCAL_OUT,
			       net, (struct sock *)sk, skb, NULL, dst->dev,
			       dst_output);
	}

	skb->dev = dst->dev;
	/* ipv6_local_error() does not require socket lock,
	 * we promote our socket to non const
	 */
	ipv6_local_error((struct sock *)sk, EMSGSIZE, fl6, mtu);

	IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)), IPSTATS_MIB_FRAGFAILS);
	kfree_skb(skb);
	return -EMSGSIZE;
}
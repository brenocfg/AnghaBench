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
struct sock {int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct rtable {int /*<<< orphan*/  dst; } ;
struct net_device {unsigned int hard_header_len; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  tos; int /*<<< orphan*/  daddr; scalar_t__ saddr; } ;
struct flowi4 {int /*<<< orphan*/  flowi4_flags; int /*<<< orphan*/  flowi4_mark; int /*<<< orphan*/  flowi4_oif; int /*<<< orphan*/  flowi4_tos; scalar_t__ saddr; int /*<<< orphan*/  daddr; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ __be32 ;
struct TYPE_2__ {int error; struct net_device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FLOWI_FLAG_ANYSRC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HH_DATA_ALIGN (unsigned int) ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int PTR_ERR (struct rtable*) ; 
 unsigned int RTN_LOCAL ; 
 unsigned int RTN_UNICAST ; 
 unsigned int RTN_UNSPEC ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 unsigned int inet_addr_type_dev_table (struct net*,struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  inet_sk_flowi_flags (struct sock const*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 struct rtable* ip_route_output_key (struct net*,struct flowi4*) ; 
 int /*<<< orphan*/  l3mdev_master_ifindex (struct net_device*) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ *) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 struct sock* skb_to_full_sk (struct sk_buff*) ; 

int ip_route_me_harder(struct net *net, struct sk_buff *skb, unsigned int addr_type)
{
	const struct iphdr *iph = ip_hdr(skb);
	struct rtable *rt;
	struct flowi4 fl4 = {};
	__be32 saddr = iph->saddr;
	const struct sock *sk = skb_to_full_sk(skb);
	__u8 flags = sk ? inet_sk_flowi_flags(sk) : 0;
	struct net_device *dev = skb_dst(skb)->dev;
	unsigned int hh_len;

	if (addr_type == RTN_UNSPEC)
		addr_type = inet_addr_type_dev_table(net, dev, saddr);
	if (addr_type == RTN_LOCAL || addr_type == RTN_UNICAST)
		flags |= FLOWI_FLAG_ANYSRC;
	else
		saddr = 0;

	/* some non-standard hacks like ipt_REJECT.c:send_reset() can cause
	 * packets with foreign saddr to appear on the NF_INET_LOCAL_OUT hook.
	 */
	fl4.daddr = iph->daddr;
	fl4.saddr = saddr;
	fl4.flowi4_tos = RT_TOS(iph->tos);
	fl4.flowi4_oif = sk ? sk->sk_bound_dev_if : 0;
	if (!fl4.flowi4_oif)
		fl4.flowi4_oif = l3mdev_master_ifindex(dev);
	fl4.flowi4_mark = skb->mark;
	fl4.flowi4_flags = flags;
	rt = ip_route_output_key(net, &fl4);
	if (IS_ERR(rt))
		return PTR_ERR(rt);

	/* Drop old route. */
	skb_dst_drop(skb);
	skb_dst_set(skb, &rt->dst);

	if (skb_dst(skb)->error)
		return skb_dst(skb)->error;

#ifdef CONFIG_XFRM
	if (!(IPCB(skb)->flags & IPSKB_XFRM_TRANSFORMED) &&
	    xfrm_decode_session(skb, flowi4_to_flowi(&fl4), AF_INET) == 0) {
		struct dst_entry *dst = skb_dst(skb);
		skb_dst_set(skb, NULL);
		dst = xfrm_lookup(net, dst, flowi4_to_flowi(&fl4), sk, 0);
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
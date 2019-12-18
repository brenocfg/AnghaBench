#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {unsigned long _skb_refdst; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct rtable {TYPE_4__ dst; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  saddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  faddr; scalar_t__ srr; } ;
struct TYPE_8__ {TYPE_1__ opt; } ;
struct TYPE_9__ {TYPE_2__ opt; } ;
struct icmp_bxm {TYPE_3__ replyopts; } ;
struct flowi4 {int fl4_icmp_type; int fl4_icmp_code; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi4_oif; int /*<<< orphan*/  flowi4_proto; int /*<<< orphan*/  flowi4_tos; int /*<<< orphan*/  flowi4_uid; int /*<<< orphan*/  flowi4_mark; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EPERM ; 
 struct rtable* ERR_PTR (int) ; 
 int /*<<< orphan*/  IPPROTO_ICMP ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int PTR_ERR (struct rtable*) ; 
 scalar_t__ RTN_LOCAL ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFRM_LOOKUP_ICMP ; 
 struct rtable* __ip_route_output_key (struct net*,struct flowi4*) ; 
 int /*<<< orphan*/  dst_release (TYPE_4__*) ; 
 int /*<<< orphan*/  flowi4_to_flowi (struct flowi4*) ; 
 scalar_t__ inet_addr_type_dev_table (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ip_route_input (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtable* ip_route_output_key (struct net*,struct flowi4*) ; 
 struct rtable* ip_route_output_key_hash (struct net*,struct flowi4*,struct sk_buff*) ; 
 int /*<<< orphan*/  l3mdev_master_ifindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct flowi4*,struct flowi4*,int) ; 
 int /*<<< orphan*/  memset (struct flowi4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_skb_classify_flow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_5__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net_uid (struct net*,int /*<<< orphan*/ *) ; 
 int xfrm_decode_session_reverse (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xfrm_lookup (struct net*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rtable *icmp_route_lookup(struct net *net,
					struct flowi4 *fl4,
					struct sk_buff *skb_in,
					const struct iphdr *iph,
					__be32 saddr, u8 tos, u32 mark,
					int type, int code,
					struct icmp_bxm *param)
{
	struct rtable *rt, *rt2;
	struct flowi4 fl4_dec;
	int err;

	memset(fl4, 0, sizeof(*fl4));
	fl4->daddr = (param->replyopts.opt.opt.srr ?
		      param->replyopts.opt.opt.faddr : iph->saddr);
	fl4->saddr = saddr;
	fl4->flowi4_mark = mark;
	fl4->flowi4_uid = sock_net_uid(net, NULL);
	fl4->flowi4_tos = RT_TOS(tos);
	fl4->flowi4_proto = IPPROTO_ICMP;
	fl4->fl4_icmp_type = type;
	fl4->fl4_icmp_code = code;
	fl4->flowi4_oif = l3mdev_master_ifindex(skb_dst(skb_in)->dev);

	security_skb_classify_flow(skb_in, flowi4_to_flowi(fl4));
	rt = ip_route_output_key_hash(net, fl4, skb_in);
	if (IS_ERR(rt))
		return rt;

	/* No need to clone since we're just using its address. */
	rt2 = rt;

	rt = (struct rtable *) xfrm_lookup(net, &rt->dst,
					   flowi4_to_flowi(fl4), NULL, 0);
	if (!IS_ERR(rt)) {
		if (rt != rt2)
			return rt;
	} else if (PTR_ERR(rt) == -EPERM) {
		rt = NULL;
	} else
		return rt;

	err = xfrm_decode_session_reverse(skb_in, flowi4_to_flowi(&fl4_dec), AF_INET);
	if (err)
		goto relookup_failed;

	if (inet_addr_type_dev_table(net, skb_dst(skb_in)->dev,
				     fl4_dec.saddr) == RTN_LOCAL) {
		rt2 = __ip_route_output_key(net, &fl4_dec);
		if (IS_ERR(rt2))
			err = PTR_ERR(rt2);
	} else {
		struct flowi4 fl4_2 = {};
		unsigned long orefdst;

		fl4_2.daddr = fl4_dec.saddr;
		rt2 = ip_route_output_key(net, &fl4_2);
		if (IS_ERR(rt2)) {
			err = PTR_ERR(rt2);
			goto relookup_failed;
		}
		/* Ugh! */
		orefdst = skb_in->_skb_refdst; /* save old refdst */
		skb_dst_set(skb_in, NULL);
		err = ip_route_input(skb_in, fl4_dec.daddr, fl4_dec.saddr,
				     RT_TOS(tos), rt2->dst.dev);

		dst_release(&rt2->dst);
		rt2 = skb_rtable(skb_in);
		skb_in->_skb_refdst = orefdst; /* restore old refdst */
	}

	if (err)
		goto relookup_failed;

	rt2 = (struct rtable *) xfrm_lookup(net, &rt2->dst,
					    flowi4_to_flowi(&fl4_dec), NULL,
					    XFRM_LOOKUP_ICMP);
	if (!IS_ERR(rt2)) {
		dst_release(&rt->dst);
		memcpy(fl4, &fl4_dec, sizeof(*fl4));
		rt = rt2;
	} else if (PTR_ERR(rt2) == -EPERM) {
		if (rt)
			dst_release(&rt->dst);
		return rt2;
	} else {
		err = PTR_ERR(rt2);
		goto relookup_failed;
	}
	return rt;

relookup_failed:
	if (rt)
		return rt;
	return ERR_PTR(err);
}
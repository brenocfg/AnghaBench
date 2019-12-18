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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ dev; } ;
struct TYPE_3__ {scalar_t__ dev; } ;
struct rt6_info {TYPE_1__ dst; } ;
struct ipv6hdr {int dummy; } ;
struct inet6_skb_parm {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  dev_net (scalar_t__) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_rt_put (struct rt6_info*) ; 
 int ip6_tnl_err (struct sk_buff*,int /*<<< orphan*/ ,struct inet6_skb_parm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ pskb_may_pull (struct sk_buff*,int) ; 
 struct rt6_info* rt6_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static int
ip6ip6_err(struct sk_buff *skb, struct inet6_skb_parm *opt,
	   u8 type, u8 code, int offset, __be32 info)
{
	__u32 rel_info = ntohl(info);
	int err, rel_msg = 0;
	u8 rel_type = type;
	u8 rel_code = code;

	err = ip6_tnl_err(skb, IPPROTO_IPV6, opt, &rel_type, &rel_code,
			  &rel_msg, &rel_info, offset);
	if (err < 0)
		return err;

	if (rel_msg && pskb_may_pull(skb, offset + sizeof(struct ipv6hdr))) {
		struct rt6_info *rt;
		struct sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);

		if (!skb2)
			return 0;

		skb_dst_drop(skb2);
		skb_pull(skb2, offset);
		skb_reset_network_header(skb2);

		/* Try to guess incoming interface */
		rt = rt6_lookup(dev_net(skb->dev), &ipv6_hdr(skb2)->saddr,
				NULL, 0, skb2, 0);

		if (rt && rt->dst.dev)
			skb2->dev = rt->dst.dev;

		icmpv6_send(skb2, rel_type, rel_code, rel_info);

		ip6_rt_put(rt);

		kfree_skb(skb2);
	}

	return 0;
}
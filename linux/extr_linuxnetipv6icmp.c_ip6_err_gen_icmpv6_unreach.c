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
typedef  unsigned int u32 ;
struct sk_buff {unsigned int len; scalar_t__ data; scalar_t__ dev; } ;
struct TYPE_4__ {scalar_t__ dev; } ;
struct rt6_info {TYPE_1__ dst; } ;
struct ipv6hdr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ICMPV6_ADDR_UNREACH ; 
 int /*<<< orphan*/  ICMPV6_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMPV6_EXC_HOPLIMIT ; 
 int /*<<< orphan*/  ICMPV6_TIME_EXCEED ; 
 int ICMP_TIME_EXCEEDED ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  dev_net (scalar_t__) ; 
 int /*<<< orphan*/  icmp6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct in6_addr*) ; 
 int /*<<< orphan*/  ip6_rt_put (struct rt6_info*) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_addr_set_v4mapped (int /*<<< orphan*/ ,struct in6_addr*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 struct rt6_info* rt6_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

int ip6_err_gen_icmpv6_unreach(struct sk_buff *skb, int nhs, int type,
			       unsigned int data_len)
{
	struct in6_addr temp_saddr;
	struct rt6_info *rt;
	struct sk_buff *skb2;
	u32 info = 0;

	if (!pskb_may_pull(skb, nhs + sizeof(struct ipv6hdr) + 8))
		return 1;

	/* RFC 4884 (partial) support for ICMP extensions */
	if (data_len < 128 || (data_len & 7) || skb->len < data_len)
		data_len = 0;

	skb2 = data_len ? skb_copy(skb, GFP_ATOMIC) : skb_clone(skb, GFP_ATOMIC);

	if (!skb2)
		return 1;

	skb_dst_drop(skb2);
	skb_pull(skb2, nhs);
	skb_reset_network_header(skb2);

	rt = rt6_lookup(dev_net(skb->dev), &ipv6_hdr(skb2)->saddr, NULL, 0,
			skb, 0);

	if (rt && rt->dst.dev)
		skb2->dev = rt->dst.dev;

	ipv6_addr_set_v4mapped(ip_hdr(skb)->saddr, &temp_saddr);

	if (data_len) {
		/* RFC 4884 (partial) support :
		 * insert 0 padding at the end, before the extensions
		 */
		__skb_push(skb2, nhs);
		skb_reset_network_header(skb2);
		memmove(skb2->data, skb2->data + nhs, data_len - nhs);
		memset(skb2->data + data_len - nhs, 0, nhs);
		/* RFC 4884 4.5 : Length is measured in 64-bit words,
		 * and stored in reserved[0]
		 */
		info = (data_len/8) << 24;
	}
	if (type == ICMP_TIME_EXCEEDED)
		icmp6_send(skb2, ICMPV6_TIME_EXCEED, ICMPV6_EXC_HOPLIMIT,
			   info, &temp_saddr);
	else
		icmp6_send(skb2, ICMPV6_DEST_UNREACH, ICMPV6_ADDR_UNREACH,
			   info, &temp_saddr);
	if (rt)
		ip6_rt_put(rt);

	kfree_skb(skb2);

	return 0;
}
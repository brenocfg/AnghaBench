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
struct sk_buff {unsigned int len; } ;
struct iphdr {int version; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  ihl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ip_fast_csum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,unsigned int) ; 
 int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_mc_check_iphdr(struct sk_buff *skb)
{
	const struct iphdr *iph;
	unsigned int len;
	unsigned int offset = skb_network_offset(skb) + sizeof(*iph);

	if (!pskb_may_pull(skb, offset))
		return -EINVAL;

	iph = ip_hdr(skb);

	if (iph->version != 4 || ip_hdrlen(skb) < sizeof(*iph))
		return -EINVAL;

	offset += ip_hdrlen(skb) - sizeof(*iph);

	if (!pskb_may_pull(skb, offset))
		return -EINVAL;

	iph = ip_hdr(skb);

	if (unlikely(ip_fast_csum((u8 *)iph, iph->ihl)))
		return -EINVAL;

	len = skb_network_offset(skb) + ntohs(iph->tot_len);
	if (skb->len < len || len < offset)
		return -EINVAL;

	skb_set_transport_header(skb, offset);

	return 0;
}
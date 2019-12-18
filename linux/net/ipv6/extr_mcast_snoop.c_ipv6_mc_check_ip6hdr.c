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
struct sk_buff {unsigned int len; } ;
struct ipv6hdr {int version; int /*<<< orphan*/  payload_len; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,unsigned int) ; 
 int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int ipv6_mc_check_ip6hdr(struct sk_buff *skb)
{
	const struct ipv6hdr *ip6h;
	unsigned int len;
	unsigned int offset = skb_network_offset(skb) + sizeof(*ip6h);

	if (!pskb_may_pull(skb, offset))
		return -EINVAL;

	ip6h = ipv6_hdr(skb);

	if (ip6h->version != 6)
		return -EINVAL;

	len = offset + ntohs(ip6h->payload_len);
	if (skb->len < len || len <= offset)
		return -EINVAL;

	skb_set_transport_header(skb, offset);

	return 0;
}
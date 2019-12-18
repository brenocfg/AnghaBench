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
struct sk_buff {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int version; scalar_t__ protocol; int ihl; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_IPV6 ; 
 struct iphdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct ipv6hdr*) ; 
 unsigned int skb_network_offset (struct sk_buff const*) ; 

__attribute__((used)) static struct iphdr *cake_get_iphdr(const struct sk_buff *skb,
				    struct ipv6hdr *buf)
{
	unsigned int offset = skb_network_offset(skb);
	struct iphdr *iph;

	iph = skb_header_pointer(skb, offset, sizeof(struct iphdr), buf);

	if (!iph)
		return NULL;

	if (iph->version == 4 && iph->protocol == IPPROTO_IPV6)
		return skb_header_pointer(skb, offset + iph->ihl * 4,
					  sizeof(struct ipv6hdr), buf);

	else if (iph->version == 4)
		return iph;

	else if (iph->version == 6)
		return skb_header_pointer(skb, offset, sizeof(struct ipv6hdr),
					  buf);

	return NULL;
}
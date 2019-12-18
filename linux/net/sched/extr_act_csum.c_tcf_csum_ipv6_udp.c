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
typedef  int u16 ;
struct udphdr {scalar_t__ check; int /*<<< orphan*/  len; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; void* csum; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_2__ {int gso_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 scalar_t__ CSUM_MANGLED_0 ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IPPROTO_UDPLITE ; 
 int SKB_GSO_UDP ; 
 scalar_t__ csum_ipv6_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 
 void* csum_partial (struct udphdr*,int,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 struct udphdr* tcf_csum_skb_nextlayer (struct sk_buff*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int tcf_csum_ipv6_udp(struct sk_buff *skb, unsigned int ihl,
			     unsigned int ipl, int udplite)
{
	struct udphdr *udph;
	const struct ipv6hdr *ip6h;
	u16 ul;

	if (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_UDP)
		return 1;

	/*
	 * Support both UDP and UDPLITE checksum algorithms, Don't use
	 * udph->len to get the real length without any protocol check,
	 * UDPLITE uses udph->len for another thing,
	 * Use ip6h->payload_len + sizeof(*ip6h) ... , or just ipl.
	 */

	udph = tcf_csum_skb_nextlayer(skb, ihl, ipl, sizeof(*udph));
	if (udph == NULL)
		return 0;

	ip6h = ipv6_hdr(skb);
	ul = ntohs(udph->len);

	udph->check = 0;

	if (udplite) {
		if (ul == 0)
			skb->csum = csum_partial(udph, ipl - ihl, 0);

		else if ((ul >= sizeof(*udph)) && (ul <= ipl - ihl))
			skb->csum = csum_partial(udph, ul, 0);

		else
			goto ignore_obscure_skb;
	} else {
		if (ul != ipl - ihl)
			goto ignore_obscure_skb;

		skb->csum = csum_partial(udph, ul, 0);
	}

	udph->check = csum_ipv6_magic(&ip6h->saddr, &ip6h->daddr, ul,
				      udplite ? IPPROTO_UDPLITE : IPPROTO_UDP,
				      skb->csum);

	if (!udph->check)
		udph->check = CSUM_MANGLED_0;

	skb->ip_summed = CHECKSUM_NONE;

ignore_obscure_skb:
	return 1;
}
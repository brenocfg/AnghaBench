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
struct iphdr {int /*<<< orphan*/  protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_2__ {int gso_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 scalar_t__ CSUM_MANGLED_0 ; 
 int SKB_GSO_UDP ; 
 void* csum_partial (struct udphdr*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ csum_tcpudp_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 struct udphdr* tcf_csum_skb_nextlayer (struct sk_buff*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int tcf_csum_ipv4_udp(struct sk_buff *skb, unsigned int ihl,
			     unsigned int ipl, int udplite)
{
	struct udphdr *udph;
	const struct iphdr *iph;
	u16 ul;

	if (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_UDP)
		return 1;

	/*
	 * Support both UDP and UDPLITE checksum algorithms, Don't use
	 * udph->len to get the real length without any protocol check,
	 * UDPLITE uses udph->len for another thing,
	 * Use iph->tot_len, or just ipl.
	 */

	udph = tcf_csum_skb_nextlayer(skb, ihl, ipl, sizeof(*udph));
	if (udph == NULL)
		return 0;

	iph = ip_hdr(skb);
	ul = ntohs(udph->len);

	if (udplite || udph->check) {

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

		udph->check = csum_tcpudp_magic(iph->saddr, iph->daddr,
						ul, iph->protocol,
						skb->csum);

		if (!udph->check)
			udph->check = CSUM_MANGLED_0;
	}

	skb->ip_summed = CHECKSUM_NONE;

ignore_obscure_skb:
	return 1;
}
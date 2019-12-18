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
struct udphdr {scalar_t__ check; } ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ data; } ;
struct nf_conntrack_tuple {int dummy; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  __udp_manip_pkt (struct sk_buff*,unsigned int,struct udphdr*,struct nf_conntrack_tuple const*,int,int) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static bool udp_manip_pkt(struct sk_buff *skb,
			  unsigned int iphdroff, unsigned int hdroff,
			  const struct nf_conntrack_tuple *tuple,
			  enum nf_nat_manip_type maniptype)
{
	struct udphdr *hdr;
	bool do_csum;

	if (skb_ensure_writable(skb, hdroff + sizeof(*hdr)))
		return false;

	hdr = (struct udphdr *)(skb->data + hdroff);
	do_csum = hdr->check || skb->ip_summed == CHECKSUM_PARTIAL;

	__udp_manip_pkt(skb, iphdroff, hdr, tuple, maniptype, do_csum);
	return true;
}
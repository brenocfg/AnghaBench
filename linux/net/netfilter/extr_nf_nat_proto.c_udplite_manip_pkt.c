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
struct udphdr {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct nf_conntrack_tuple {int dummy; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;

/* Variables and functions */
 int /*<<< orphan*/  __udp_manip_pkt (struct sk_buff*,unsigned int,struct udphdr*,struct nf_conntrack_tuple const*,int,int) ; 
 scalar_t__ skb_ensure_writable (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static bool udplite_manip_pkt(struct sk_buff *skb,
			      unsigned int iphdroff, unsigned int hdroff,
			      const struct nf_conntrack_tuple *tuple,
			      enum nf_nat_manip_type maniptype)
{
#ifdef CONFIG_NF_CT_PROTO_UDPLITE
	struct udphdr *hdr;

	if (skb_ensure_writable(skb, hdroff + sizeof(*hdr)))
		return false;

	hdr = (struct udphdr *)(skb->data + hdroff);
	__udp_manip_pkt(skb, iphdroff, hdr, tuple, maniptype, true);
#endif
	return true;
}
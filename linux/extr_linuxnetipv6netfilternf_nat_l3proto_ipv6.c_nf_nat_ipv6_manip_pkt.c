#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct nf_nat_l4proto {int /*<<< orphan*/  (* manip_pkt ) (struct sk_buff*,int /*<<< orphan*/ *,unsigned int,int,struct nf_conntrack_tuple const*,int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  in6; } ;
struct TYPE_8__ {TYPE_3__ u3; } ;
struct TYPE_5__ {int /*<<< orphan*/  in6; } ;
struct TYPE_6__ {TYPE_1__ u3; } ;
struct nf_conntrack_tuple {TYPE_4__ dst; TYPE_2__ src; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  nexthdr; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  int __be16 ;

/* Variables and functions */
 int NF_NAT_MANIP_SRC ; 
 int htons (int) ; 
 int ipv6_skip_exthdr (struct sk_buff*,unsigned int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nf_nat_l3proto_ipv6 ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,int /*<<< orphan*/ *,unsigned int,int,struct nf_conntrack_tuple const*,int) ; 

__attribute__((used)) static bool nf_nat_ipv6_manip_pkt(struct sk_buff *skb,
				  unsigned int iphdroff,
				  const struct nf_nat_l4proto *l4proto,
				  const struct nf_conntrack_tuple *target,
				  enum nf_nat_manip_type maniptype)
{
	struct ipv6hdr *ipv6h;
	__be16 frag_off;
	int hdroff;
	u8 nexthdr;

	if (!skb_make_writable(skb, iphdroff + sizeof(*ipv6h)))
		return false;

	ipv6h = (void *)skb->data + iphdroff;
	nexthdr = ipv6h->nexthdr;
	hdroff = ipv6_skip_exthdr(skb, iphdroff + sizeof(*ipv6h),
				  &nexthdr, &frag_off);
	if (hdroff < 0)
		goto manip_addr;

	if ((frag_off & htons(~0x7)) == 0 &&
	    !l4proto->manip_pkt(skb, &nf_nat_l3proto_ipv6, iphdroff, hdroff,
				target, maniptype))
		return false;

	/* must reload, offset might have changed */
	ipv6h = (void *)skb->data + iphdroff;

manip_addr:
	if (maniptype == NF_NAT_MANIP_SRC)
		ipv6h->saddr = target->src.u3.in6;
	else
		ipv6h->daddr = target->dst.u3.in6;

	return true;
}
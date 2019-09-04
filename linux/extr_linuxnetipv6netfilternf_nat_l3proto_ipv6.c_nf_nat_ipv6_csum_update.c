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
struct sk_buff {scalar_t__ data; } ;
struct in6_addr {int /*<<< orphan*/  s6_addr32; } ;
struct TYPE_7__ {struct in6_addr in6; } ;
struct TYPE_8__ {TYPE_3__ u3; } ;
struct TYPE_5__ {struct in6_addr in6; } ;
struct TYPE_6__ {TYPE_1__ u3; } ;
struct nf_conntrack_tuple {TYPE_4__ dst; TYPE_2__ src; } ;
struct ipv6hdr {struct in6_addr daddr; struct in6_addr saddr; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
 int NF_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  inet_proto_csum_replace16 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nf_nat_ipv6_csum_update(struct sk_buff *skb,
				    unsigned int iphdroff, __sum16 *check,
				    const struct nf_conntrack_tuple *t,
				    enum nf_nat_manip_type maniptype)
{
	const struct ipv6hdr *ipv6h = (struct ipv6hdr *)(skb->data + iphdroff);
	const struct in6_addr *oldip, *newip;

	if (maniptype == NF_NAT_MANIP_SRC) {
		oldip = &ipv6h->saddr;
		newip = &t->src.u3.in6;
	} else {
		oldip = &ipv6h->daddr;
		newip = &t->dst.u3.in6;
	}
	inet_proto_csum_replace16(check, skb, oldip->s6_addr32,
				  newip->s6_addr32, true);
}
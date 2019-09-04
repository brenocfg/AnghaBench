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
struct TYPE_5__ {int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {TYPE_1__ u3; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip; } ;
struct TYPE_7__ {TYPE_4__ u3; } ;
struct nf_conntrack_tuple {TYPE_2__ dst; TYPE_3__ src; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  int /*<<< orphan*/  __sum16 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NF_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  inet_proto_csum_replace4 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nf_nat_ipv4_csum_update(struct sk_buff *skb,
				    unsigned int iphdroff, __sum16 *check,
				    const struct nf_conntrack_tuple *t,
				    enum nf_nat_manip_type maniptype)
{
	struct iphdr *iph = (struct iphdr *)(skb->data + iphdroff);
	__be32 oldip, newip;

	if (maniptype == NF_NAT_MANIP_SRC) {
		oldip = iph->saddr;
		newip = t->src.u3.ip;
	} else {
		oldip = iph->daddr;
		newip = t->dst.u3.ip;
	}
	inet_proto_csum_replace4(check, skb, oldip, newip, true);
}
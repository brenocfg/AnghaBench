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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int l3num; } ;
struct nf_conntrack_tuple {TYPE_1__ src; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 int /*<<< orphan*/  nf_nat_ipv4_csum_update (struct sk_buff*,unsigned int,int /*<<< orphan*/ *,struct nf_conntrack_tuple const*,int) ; 
 int /*<<< orphan*/  nf_nat_ipv6_csum_update (struct sk_buff*,unsigned int,int /*<<< orphan*/ *,struct nf_conntrack_tuple const*,int) ; 

__attribute__((used)) static void nf_csum_update(struct sk_buff *skb,
			   unsigned int iphdroff, __sum16 *check,
			   const struct nf_conntrack_tuple *t,
			   enum nf_nat_manip_type maniptype)
{
	switch (t->src.l3num) {
	case NFPROTO_IPV4:
		nf_nat_ipv4_csum_update(skb, iphdroff, check, t, maniptype);
		return;
	case NFPROTO_IPV6:
		nf_nat_ipv6_csum_update(skb, iphdroff, check, t, maniptype);
		return;
	}
}
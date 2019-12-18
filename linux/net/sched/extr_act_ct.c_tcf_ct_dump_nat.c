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
struct TYPE_8__ {int /*<<< orphan*/  all; } ;
struct TYPE_7__ {int /*<<< orphan*/  all; } ;
struct TYPE_6__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  ip; } ;
struct TYPE_5__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  ip; } ;
struct nf_nat_range2 {int flags; TYPE_4__ max_proto; TYPE_3__ min_proto; TYPE_2__ max_addr; TYPE_1__ min_addr; } ;
struct tcf_ct_params {int ct_action; scalar_t__ ipv4_range; struct nf_nat_range2 range; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int NF_NAT_RANGE_MAP_IPS ; 
 int NF_NAT_RANGE_PROTO_SPECIFIED ; 
 int TCA_CT_ACT_NAT ; 
 int TCA_CT_ACT_NAT_DST ; 
 int TCA_CT_ACT_NAT_SRC ; 
 int /*<<< orphan*/  TCA_CT_NAT_IPV4_MAX ; 
 int /*<<< orphan*/  TCA_CT_NAT_IPV4_MIN ; 
 int /*<<< orphan*/  TCA_CT_NAT_IPV6_MAX ; 
 int /*<<< orphan*/  TCA_CT_NAT_IPV6_MIN ; 
 int /*<<< orphan*/  TCA_CT_NAT_PORT_MAX ; 
 int /*<<< orphan*/  TCA_CT_NAT_PORT_MIN ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_in6_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_in_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcf_ct_dump_nat(struct sk_buff *skb, struct tcf_ct_params *p)
{
	struct nf_nat_range2 *range = &p->range;

	if (!(p->ct_action & TCA_CT_ACT_NAT))
		return 0;

	if (!(p->ct_action & (TCA_CT_ACT_NAT_SRC | TCA_CT_ACT_NAT_DST)))
		return 0;

	if (range->flags & NF_NAT_RANGE_MAP_IPS) {
		if (p->ipv4_range) {
			if (nla_put_in_addr(skb, TCA_CT_NAT_IPV4_MIN,
					    range->min_addr.ip))
				return -1;
			if (nla_put_in_addr(skb, TCA_CT_NAT_IPV4_MAX,
					    range->max_addr.ip))
				return -1;
		} else {
			if (nla_put_in6_addr(skb, TCA_CT_NAT_IPV6_MIN,
					     &range->min_addr.in6))
				return -1;
			if (nla_put_in6_addr(skb, TCA_CT_NAT_IPV6_MAX,
					     &range->max_addr.in6))
				return -1;
		}
	}

	if (range->flags & NF_NAT_RANGE_PROTO_SPECIFIED) {
		if (nla_put_be16(skb, TCA_CT_NAT_PORT_MIN,
				 range->min_proto.all))
			return -1;
		if (nla_put_be16(skb, TCA_CT_NAT_PORT_MAX,
				 range->max_proto.all))
			return -1;
	}

	return 0;
}
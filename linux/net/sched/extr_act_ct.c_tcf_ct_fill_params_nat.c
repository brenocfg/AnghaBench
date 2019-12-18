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
struct TYPE_8__ {void* all; } ;
struct TYPE_7__ {void* all; } ;
struct TYPE_6__ {void* ip; void* in6; } ;
struct TYPE_5__ {void* in6; void* ip; } ;
struct nf_nat_range2 {TYPE_4__ min_proto; TYPE_3__ max_proto; int /*<<< orphan*/  flags; TYPE_2__ min_addr; TYPE_1__ max_addr; } ;
struct tcf_ct_params {int ct_action; int ipv4_range; struct nf_nat_range2 range; } ;
struct tc_ct {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NF_NAT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_NAT_RANGE_MAP_IPS ; 
 int /*<<< orphan*/  NF_NAT_RANGE_PROTO_SPECIFIED ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int TCA_CT_ACT_NAT ; 
 int TCA_CT_ACT_NAT_DST ; 
 int TCA_CT_ACT_NAT_SRC ; 
 size_t TCA_CT_NAT_IPV4_MAX ; 
 size_t TCA_CT_NAT_IPV4_MIN ; 
 size_t TCA_CT_NAT_IPV6_MAX ; 
 size_t TCA_CT_NAT_IPV6_MIN ; 
 size_t TCA_CT_NAT_PORT_MAX ; 
 size_t TCA_CT_NAT_PORT_MIN ; 
 void* nla_get_be16 (struct nlattr*) ; 
 void* nla_get_in6_addr (struct nlattr*) ; 
 void* nla_get_in_addr (struct nlattr*) ; 

__attribute__((used)) static int tcf_ct_fill_params_nat(struct tcf_ct_params *p,
				  struct tc_ct *parm,
				  struct nlattr **tb,
				  struct netlink_ext_ack *extack)
{
	struct nf_nat_range2 *range;

	if (!(p->ct_action & TCA_CT_ACT_NAT))
		return 0;

	if (!IS_ENABLED(CONFIG_NF_NAT)) {
		NL_SET_ERR_MSG_MOD(extack, "Netfilter nat isn't enabled in kernel");
		return -EOPNOTSUPP;
	}

	if (!(p->ct_action & (TCA_CT_ACT_NAT_SRC | TCA_CT_ACT_NAT_DST)))
		return 0;

	if ((p->ct_action & TCA_CT_ACT_NAT_SRC) &&
	    (p->ct_action & TCA_CT_ACT_NAT_DST)) {
		NL_SET_ERR_MSG_MOD(extack, "dnat and snat can't be enabled at the same time");
		return -EOPNOTSUPP;
	}

	range = &p->range;
	if (tb[TCA_CT_NAT_IPV4_MIN]) {
		struct nlattr *max_attr = tb[TCA_CT_NAT_IPV4_MAX];

		p->ipv4_range = true;
		range->flags |= NF_NAT_RANGE_MAP_IPS;
		range->min_addr.ip =
			nla_get_in_addr(tb[TCA_CT_NAT_IPV4_MIN]);

		range->max_addr.ip = max_attr ?
				     nla_get_in_addr(max_attr) :
				     range->min_addr.ip;
	} else if (tb[TCA_CT_NAT_IPV6_MIN]) {
		struct nlattr *max_attr = tb[TCA_CT_NAT_IPV6_MAX];

		p->ipv4_range = false;
		range->flags |= NF_NAT_RANGE_MAP_IPS;
		range->min_addr.in6 =
			nla_get_in6_addr(tb[TCA_CT_NAT_IPV6_MIN]);

		range->max_addr.in6 = max_attr ?
				      nla_get_in6_addr(max_attr) :
				      range->min_addr.in6;
	}

	if (tb[TCA_CT_NAT_PORT_MIN]) {
		range->flags |= NF_NAT_RANGE_PROTO_SPECIFIED;
		range->min_proto.all = nla_get_be16(tb[TCA_CT_NAT_PORT_MIN]);

		range->max_proto.all = tb[TCA_CT_NAT_PORT_MAX] ?
				       nla_get_be16(tb[TCA_CT_NAT_PORT_MAX]) :
				       range->min_proto.all;
	}

	return 0;
}
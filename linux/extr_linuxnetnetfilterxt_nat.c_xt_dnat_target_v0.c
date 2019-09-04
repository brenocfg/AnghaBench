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
struct xt_action_param {struct nf_nat_ipv4_multi_range_compat* targinfo; } ;
struct sk_buff {int dummy; } ;
struct nf_nat_range2 {int dummy; } ;
struct nf_nat_ipv4_multi_range_compat {int /*<<< orphan*/ * range; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int IP_CT_NEW ; 
 int IP_CT_RELATED ; 
 int /*<<< orphan*/  NF_NAT_MANIP_DST ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 unsigned int nf_nat_setup_info (struct nf_conn*,struct nf_nat_range2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xt_nat_convert_range (struct nf_nat_range2*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
xt_dnat_target_v0(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct nf_nat_ipv4_multi_range_compat *mr = par->targinfo;
	struct nf_nat_range2 range;
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	WARN_ON(!(ct != NULL &&
		 (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED)));

	xt_nat_convert_range(&range, &mr->range[0]);
	return nf_nat_setup_info(ct, &range, NF_NAT_MANIP_DST);
}
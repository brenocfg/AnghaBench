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
struct tcf_result {int dummy; } ;
struct tcf_mpls_params {int tcfm_action; int /*<<< orphan*/  tcfm_proto; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_qstats; int /*<<< orphan*/  cpu_bstats; } ;
struct tcf_mpls {TYPE_1__ common; int /*<<< orphan*/  mpls_p; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_tm; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int mac_len; int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
#define  TCA_MPLS_ACT_DEC_TTL 131 
#define  TCA_MPLS_ACT_MODIFY 130 
#define  TCA_MPLS_ACT_POP 129 
#define  TCA_MPLS_ACT_PUSH 128 
 int TC_ACT_SHOT ; 
 int /*<<< orphan*/  bstats_cpu_update (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  eth_p_mpls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpls_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  qstats_drop_inc (int /*<<< orphan*/ ) ; 
 struct tcf_mpls_params* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_at_tc_ingress (struct sk_buff*) ; 
 int skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mpls_dec_ttl (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mpls_pop (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_mpls_push (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_mpls_update_lse (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push_rcsum (struct sk_buff*,int) ; 
 int /*<<< orphan*/  tcf_lastuse_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_mpls_get_lse (int /*<<< orphan*/ *,struct tcf_mpls_params*,int) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct tcf_mpls* to_mpls (struct tc_action const*) ; 

__attribute__((used)) static int tcf_mpls_act(struct sk_buff *skb, const struct tc_action *a,
			struct tcf_result *res)
{
	struct tcf_mpls *m = to_mpls(a);
	struct tcf_mpls_params *p;
	__be32 new_lse;
	int ret, mac_len;

	tcf_lastuse_update(&m->tcf_tm);
	bstats_cpu_update(this_cpu_ptr(m->common.cpu_bstats), skb);

	/* Ensure 'data' points at mac_header prior calling mpls manipulating
	 * functions.
	 */
	if (skb_at_tc_ingress(skb)) {
		skb_push_rcsum(skb, skb->mac_len);
		mac_len = skb->mac_len;
	} else {
		mac_len = skb_network_header(skb) - skb_mac_header(skb);
	}

	ret = READ_ONCE(m->tcf_action);

	p = rcu_dereference_bh(m->mpls_p);

	switch (p->tcfm_action) {
	case TCA_MPLS_ACT_POP:
		if (skb_mpls_pop(skb, p->tcfm_proto, mac_len))
			goto drop;
		break;
	case TCA_MPLS_ACT_PUSH:
		new_lse = tcf_mpls_get_lse(NULL, p, !eth_p_mpls(skb->protocol));
		if (skb_mpls_push(skb, new_lse, p->tcfm_proto, mac_len))
			goto drop;
		break;
	case TCA_MPLS_ACT_MODIFY:
		new_lse = tcf_mpls_get_lse(mpls_hdr(skb), p, false);
		if (skb_mpls_update_lse(skb, new_lse))
			goto drop;
		break;
	case TCA_MPLS_ACT_DEC_TTL:
		if (skb_mpls_dec_ttl(skb))
			goto drop;
		break;
	}

	if (skb_at_tc_ingress(skb))
		skb_pull_rcsum(skb, skb->mac_len);

	return ret;

drop:
	qstats_drop_inc(this_cpu_ptr(m->common.cpu_qstats));
	return TC_ACT_SHOT;
}
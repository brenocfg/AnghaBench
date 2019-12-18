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
typedef  int u16 ;
struct tcf_vlan_params {int tcfv_action; int tcfv_push_vid; int tcfv_push_prio; int /*<<< orphan*/  tcfv_push_proto; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_qstats; int /*<<< orphan*/  cpu_bstats; } ;
struct tcf_vlan {TYPE_1__ common; int /*<<< orphan*/  vlan_p; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_tm; } ;
struct tcf_result {int dummy; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  mac_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
#define  TCA_VLAN_ACT_MODIFY 130 
#define  TCA_VLAN_ACT_POP 129 
#define  TCA_VLAN_ACT_PUSH 128 
 int TC_ACT_SHOT ; 
 int VLAN_PRIO_MASK ; 
 int VLAN_PRIO_SHIFT ; 
 int VLAN_VID_MASK ; 
 int __skb_vlan_pop (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  __vlan_hwaccel_clear_tag (struct sk_buff*) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bstats_cpu_update (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  qstats_drop_inc (int /*<<< orphan*/ ) ; 
 struct tcf_vlan_params* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_at_tc_ingress (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push_rcsum (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_vlan_pop (struct sk_buff*) ; 
 int skb_vlan_push (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tagged (struct sk_buff*) ; 
 int /*<<< orphan*/  tcf_lastuse_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct tcf_vlan* to_vlan (struct tc_action const*) ; 

__attribute__((used)) static int tcf_vlan_act(struct sk_buff *skb, const struct tc_action *a,
			struct tcf_result *res)
{
	struct tcf_vlan *v = to_vlan(a);
	struct tcf_vlan_params *p;
	int action;
	int err;
	u16 tci;

	tcf_lastuse_update(&v->tcf_tm);
	bstats_cpu_update(this_cpu_ptr(v->common.cpu_bstats), skb);

	/* Ensure 'data' points at mac_header prior calling vlan manipulating
	 * functions.
	 */
	if (skb_at_tc_ingress(skb))
		skb_push_rcsum(skb, skb->mac_len);

	action = READ_ONCE(v->tcf_action);

	p = rcu_dereference_bh(v->vlan_p);

	switch (p->tcfv_action) {
	case TCA_VLAN_ACT_POP:
		err = skb_vlan_pop(skb);
		if (err)
			goto drop;
		break;
	case TCA_VLAN_ACT_PUSH:
		err = skb_vlan_push(skb, p->tcfv_push_proto, p->tcfv_push_vid |
				    (p->tcfv_push_prio << VLAN_PRIO_SHIFT));
		if (err)
			goto drop;
		break;
	case TCA_VLAN_ACT_MODIFY:
		/* No-op if no vlan tag (either hw-accel or in-payload) */
		if (!skb_vlan_tagged(skb))
			goto out;
		/* extract existing tag (and guarantee no hw-accel tag) */
		if (skb_vlan_tag_present(skb)) {
			tci = skb_vlan_tag_get(skb);
			__vlan_hwaccel_clear_tag(skb);
		} else {
			/* in-payload vlan tag, pop it */
			err = __skb_vlan_pop(skb, &tci);
			if (err)
				goto drop;
		}
		/* replace the vid */
		tci = (tci & ~VLAN_VID_MASK) | p->tcfv_push_vid;
		/* replace prio bits, if tcfv_push_prio specified */
		if (p->tcfv_push_prio) {
			tci &= ~VLAN_PRIO_MASK;
			tci |= p->tcfv_push_prio << VLAN_PRIO_SHIFT;
		}
		/* put updated tci as hwaccel tag */
		__vlan_hwaccel_put_tag(skb, p->tcfv_push_proto, tci);
		break;
	default:
		BUG();
	}

out:
	if (skb_at_tc_ingress(skb))
		skb_pull_rcsum(skb, skb->mac_len);

	return action;

drop:
	qstats_drop_inc(this_cpu_ptr(v->common.cpu_qstats));
	return TC_ACT_SHOT;
}
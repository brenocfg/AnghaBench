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
typedef  int /*<<< orphan*/  t ;
struct tcf_vlan_params {scalar_t__ tcfv_action; int /*<<< orphan*/  tcfv_push_prio; int /*<<< orphan*/  tcfv_push_proto; int /*<<< orphan*/  tcfv_push_vid; } ;
struct tcf_vlan {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  vlan_p; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tcf_t {int dummy; } ;
struct tc_vlan {scalar_t__ v_action; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 scalar_t__ TCA_VLAN_ACT_MODIFY ; 
 scalar_t__ TCA_VLAN_ACT_PUSH ; 
 int /*<<< orphan*/  TCA_VLAN_PAD ; 
 int /*<<< orphan*/  TCA_VLAN_PARMS ; 
 int /*<<< orphan*/  TCA_VLAN_PUSH_VLAN_ID ; 
 int /*<<< orphan*/  TCA_VLAN_PUSH_VLAN_PRIORITY ; 
 int /*<<< orphan*/  TCA_VLAN_PUSH_VLAN_PROTOCOL ; 
 int /*<<< orphan*/  TCA_VLAN_TM ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_vlan*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 struct tcf_vlan_params* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_vlan* to_vlan (struct tc_action*) ; 

__attribute__((used)) static int tcf_vlan_dump(struct sk_buff *skb, struct tc_action *a,
			 int bind, int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_vlan *v = to_vlan(a);
	struct tcf_vlan_params *p;
	struct tc_vlan opt = {
		.index    = v->tcf_index,
		.refcnt   = refcount_read(&v->tcf_refcnt) - ref,
		.bindcnt  = atomic_read(&v->tcf_bindcnt) - bind,
	};
	struct tcf_t t;

	spin_lock_bh(&v->tcf_lock);
	opt.action = v->tcf_action;
	p = rcu_dereference_protected(v->vlan_p, lockdep_is_held(&v->tcf_lock));
	opt.v_action = p->tcfv_action;
	if (nla_put(skb, TCA_VLAN_PARMS, sizeof(opt), &opt))
		goto nla_put_failure;

	if ((p->tcfv_action == TCA_VLAN_ACT_PUSH ||
	     p->tcfv_action == TCA_VLAN_ACT_MODIFY) &&
	    (nla_put_u16(skb, TCA_VLAN_PUSH_VLAN_ID, p->tcfv_push_vid) ||
	     nla_put_be16(skb, TCA_VLAN_PUSH_VLAN_PROTOCOL,
			  p->tcfv_push_proto) ||
	     (nla_put_u8(skb, TCA_VLAN_PUSH_VLAN_PRIORITY,
					      p->tcfv_push_prio))))
		goto nla_put_failure;

	tcf_tm_dump(&t, &v->tcf_tm);
	if (nla_put_64bit(skb, TCA_VLAN_TM, sizeof(t), &t, TCA_VLAN_PAD))
		goto nla_put_failure;
	spin_unlock_bh(&v->tcf_lock);

	return skb->len;

nla_put_failure:
	spin_unlock_bh(&v->tcf_lock);
	nlmsg_trim(skb, b);
	return -1;
}
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
struct tcf_t {int dummy; } ;
struct tcf_ct_params {int ct_action; int mark; int* labels; int zone; int /*<<< orphan*/ * labels_mask; int /*<<< orphan*/  mark_mask; } ;
struct tcf_ct {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  params; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tc_ct {int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NF_CONNTRACK_LABELS ; 
 int /*<<< orphan*/  CONFIG_NF_CONNTRACK_MARK ; 
 int /*<<< orphan*/  CONFIG_NF_CONNTRACK_ZONES ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCA_CT_ACTION ; 
 int TCA_CT_ACT_CLEAR ; 
 int /*<<< orphan*/  TCA_CT_LABELS ; 
 int /*<<< orphan*/  TCA_CT_LABELS_MASK ; 
 int /*<<< orphan*/  TCA_CT_MARK ; 
 int /*<<< orphan*/  TCA_CT_MARK_MASK ; 
 int /*<<< orphan*/  TCA_CT_PAD ; 
 int /*<<< orphan*/  TCA_CT_PARMS ; 
 int /*<<< orphan*/  TCA_CT_TM ; 
 int /*<<< orphan*/  TCA_CT_UNSPEC ; 
 int /*<<< orphan*/  TCA_CT_ZONE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_ct*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 struct tcf_ct_params* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ tcf_ct_dump_key_val (struct sk_buff*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tcf_ct_dump_nat (struct sk_buff*,struct tcf_ct_params*) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_ct* to_ct (struct tc_action*) ; 

__attribute__((used)) static inline int tcf_ct_dump(struct sk_buff *skb, struct tc_action *a,
			      int bind, int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_ct *c = to_ct(a);
	struct tcf_ct_params *p;

	struct tc_ct opt = {
		.index   = c->tcf_index,
		.refcnt  = refcount_read(&c->tcf_refcnt) - ref,
		.bindcnt = atomic_read(&c->tcf_bindcnt) - bind,
	};
	struct tcf_t t;

	spin_lock_bh(&c->tcf_lock);
	p = rcu_dereference_protected(c->params,
				      lockdep_is_held(&c->tcf_lock));
	opt.action = c->tcf_action;

	if (tcf_ct_dump_key_val(skb,
				&p->ct_action, TCA_CT_ACTION,
				NULL, TCA_CT_UNSPEC,
				sizeof(p->ct_action)))
		goto nla_put_failure;

	if (p->ct_action & TCA_CT_ACT_CLEAR)
		goto skip_dump;

	if (IS_ENABLED(CONFIG_NF_CONNTRACK_MARK) &&
	    tcf_ct_dump_key_val(skb,
				&p->mark, TCA_CT_MARK,
				&p->mark_mask, TCA_CT_MARK_MASK,
				sizeof(p->mark)))
		goto nla_put_failure;

	if (IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS) &&
	    tcf_ct_dump_key_val(skb,
				p->labels, TCA_CT_LABELS,
				p->labels_mask, TCA_CT_LABELS_MASK,
				sizeof(p->labels)))
		goto nla_put_failure;

	if (IS_ENABLED(CONFIG_NF_CONNTRACK_ZONES) &&
	    tcf_ct_dump_key_val(skb,
				&p->zone, TCA_CT_ZONE,
				NULL, TCA_CT_UNSPEC,
				sizeof(p->zone)))
		goto nla_put_failure;

	if (tcf_ct_dump_nat(skb, p))
		goto nla_put_failure;

skip_dump:
	if (nla_put(skb, TCA_CT_PARMS, sizeof(opt), &opt))
		goto nla_put_failure;

	tcf_tm_dump(&t, &c->tcf_tm);
	if (nla_put_64bit(skb, TCA_CT_TM, sizeof(t), &t, TCA_CT_PAD))
		goto nla_put_failure;
	spin_unlock_bh(&c->tcf_lock);

	return skb->len;
nla_put_failure:
	spin_unlock_bh(&c->tcf_lock);
	nlmsg_trim(skb, b);
	return -1;
}
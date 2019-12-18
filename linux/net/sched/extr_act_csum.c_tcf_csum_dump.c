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
struct tcf_csum_params {int /*<<< orphan*/  update_flags; } ;
struct tcf_csum {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  params; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tc_csum {int /*<<< orphan*/  update_flags; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_CSUM_PAD ; 
 int /*<<< orphan*/  TCA_CSUM_PARMS ; 
 int /*<<< orphan*/  TCA_CSUM_TM ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_csum*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 struct tcf_csum_params* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_csum* to_tcf_csum (struct tc_action*) ; 

__attribute__((used)) static int tcf_csum_dump(struct sk_buff *skb, struct tc_action *a, int bind,
			 int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_csum *p = to_tcf_csum(a);
	struct tcf_csum_params *params;
	struct tc_csum opt = {
		.index   = p->tcf_index,
		.refcnt  = refcount_read(&p->tcf_refcnt) - ref,
		.bindcnt = atomic_read(&p->tcf_bindcnt) - bind,
	};
	struct tcf_t t;

	spin_lock_bh(&p->tcf_lock);
	params = rcu_dereference_protected(p->params,
					   lockdep_is_held(&p->tcf_lock));
	opt.action = p->tcf_action;
	opt.update_flags = params->update_flags;

	if (nla_put(skb, TCA_CSUM_PARMS, sizeof(opt), &opt))
		goto nla_put_failure;

	tcf_tm_dump(&t, &p->tcf_tm);
	if (nla_put_64bit(skb, TCA_CSUM_TM, sizeof(t), &t, TCA_CSUM_PAD))
		goto nla_put_failure;
	spin_unlock_bh(&p->tcf_lock);

	return skb->len;

nla_put_failure:
	spin_unlock_bh(&p->tcf_lock);
	nlmsg_trim(skb, b);
	return -1;
}
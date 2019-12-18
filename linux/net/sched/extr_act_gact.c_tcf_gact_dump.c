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
struct tcf_gact {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_tm; scalar_t__ tcfg_ptype; int /*<<< orphan*/  tcfg_pval; int /*<<< orphan*/  tcfg_paction; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tc_gact_p {scalar_t__ ptype; int /*<<< orphan*/  pval; int /*<<< orphan*/  paction; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_gact {scalar_t__ ptype; int /*<<< orphan*/  pval; int /*<<< orphan*/  paction; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  p_opt ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_GACT_PAD ; 
 int /*<<< orphan*/  TCA_GACT_PARMS ; 
 int /*<<< orphan*/  TCA_GACT_PROB ; 
 int /*<<< orphan*/  TCA_GACT_TM ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_gact_p*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_gact* to_gact (struct tc_action*) ; 

__attribute__((used)) static int tcf_gact_dump(struct sk_buff *skb, struct tc_action *a,
			 int bind, int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_gact *gact = to_gact(a);
	struct tc_gact opt = {
		.index   = gact->tcf_index,
		.refcnt  = refcount_read(&gact->tcf_refcnt) - ref,
		.bindcnt = atomic_read(&gact->tcf_bindcnt) - bind,
	};
	struct tcf_t t;

	spin_lock_bh(&gact->tcf_lock);
	opt.action = gact->tcf_action;
	if (nla_put(skb, TCA_GACT_PARMS, sizeof(opt), &opt))
		goto nla_put_failure;
#ifdef CONFIG_GACT_PROB
	if (gact->tcfg_ptype) {
		struct tc_gact_p p_opt = {
			.paction = gact->tcfg_paction,
			.pval    = gact->tcfg_pval,
			.ptype   = gact->tcfg_ptype,
		};

		if (nla_put(skb, TCA_GACT_PROB, sizeof(p_opt), &p_opt))
			goto nla_put_failure;
	}
#endif
	tcf_tm_dump(&t, &gact->tcf_tm);
	if (nla_put_64bit(skb, TCA_GACT_TM, sizeof(t), &t, TCA_GACT_PAD))
		goto nla_put_failure;
	spin_unlock_bh(&gact->tcf_lock);

	return skb->len;

nla_put_failure:
	spin_unlock_bh(&gact->tcf_lock);
	nlmsg_trim(skb, b);
	return -1;
}
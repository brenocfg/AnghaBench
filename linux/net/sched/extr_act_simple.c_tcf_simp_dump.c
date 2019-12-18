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
struct tcf_defact {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  tcfd_defdata; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tc_defact {int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_DEF_DATA ; 
 int /*<<< orphan*/  TCA_DEF_PAD ; 
 int /*<<< orphan*/  TCA_DEF_PARMS ; 
 int /*<<< orphan*/  TCA_DEF_TM ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_defact*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_defact* to_defact (struct tc_action*) ; 

__attribute__((used)) static int tcf_simp_dump(struct sk_buff *skb, struct tc_action *a,
			 int bind, int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_defact *d = to_defact(a);
	struct tc_defact opt = {
		.index   = d->tcf_index,
		.refcnt  = refcount_read(&d->tcf_refcnt) - ref,
		.bindcnt = atomic_read(&d->tcf_bindcnt) - bind,
	};
	struct tcf_t t;

	spin_lock_bh(&d->tcf_lock);
	opt.action = d->tcf_action;
	if (nla_put(skb, TCA_DEF_PARMS, sizeof(opt), &opt) ||
	    nla_put_string(skb, TCA_DEF_DATA, d->tcfd_defdata))
		goto nla_put_failure;

	tcf_tm_dump(&t, &d->tcf_tm);
	if (nla_put_64bit(skb, TCA_DEF_TM, sizeof(t), &t, TCA_DEF_PAD))
		goto nla_put_failure;
	spin_unlock_bh(&d->tcf_lock);

	return skb->len;

nla_put_failure:
	spin_unlock_bh(&d->tcf_lock);
	nlmsg_trim(skb, b);
	return -1;
}
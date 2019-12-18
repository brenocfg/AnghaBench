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
struct tcf_pedit {int tcfp_nkeys; int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_tm; scalar_t__ tcfp_keys_ex; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcfp_flags; int /*<<< orphan*/  tcf_index; int /*<<< orphan*/  tcfp_keys; } ;
struct tc_pedit_key {int dummy; } ;
struct tc_pedit {int nkeys; scalar_t__ bindcnt; scalar_t__ refcnt; int /*<<< orphan*/  action; int /*<<< orphan*/  flags; int /*<<< orphan*/  index; int /*<<< orphan*/  keys; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TCA_PEDIT_PAD ; 
 int /*<<< orphan*/  TCA_PEDIT_PARMS ; 
 int /*<<< orphan*/  TCA_PEDIT_PARMS_EX ; 
 int /*<<< orphan*/  TCA_PEDIT_TM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keys ; 
 int /*<<< orphan*/  kfree (struct tc_pedit*) ; 
 struct tc_pedit* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_pedit*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int struct_size (struct tc_pedit*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tcf_pedit_key_ex_dump (struct sk_buff*,scalar_t__,int) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_pedit* to_pedit (struct tc_action*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_pedit_dump(struct sk_buff *skb, struct tc_action *a,
			  int bind, int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_pedit *p = to_pedit(a);
	struct tc_pedit *opt;
	struct tcf_t t;
	int s;

	s = struct_size(opt, keys, p->tcfp_nkeys);

	/* netlink spinlocks held above us - must use ATOMIC */
	opt = kzalloc(s, GFP_ATOMIC);
	if (unlikely(!opt))
		return -ENOBUFS;

	spin_lock_bh(&p->tcf_lock);
	memcpy(opt->keys, p->tcfp_keys,
	       p->tcfp_nkeys * sizeof(struct tc_pedit_key));
	opt->index = p->tcf_index;
	opt->nkeys = p->tcfp_nkeys;
	opt->flags = p->tcfp_flags;
	opt->action = p->tcf_action;
	opt->refcnt = refcount_read(&p->tcf_refcnt) - ref;
	opt->bindcnt = atomic_read(&p->tcf_bindcnt) - bind;

	if (p->tcfp_keys_ex) {
		if (tcf_pedit_key_ex_dump(skb,
					  p->tcfp_keys_ex,
					  p->tcfp_nkeys))
			goto nla_put_failure;

		if (nla_put(skb, TCA_PEDIT_PARMS_EX, s, opt))
			goto nla_put_failure;
	} else {
		if (nla_put(skb, TCA_PEDIT_PARMS, s, opt))
			goto nla_put_failure;
	}

	tcf_tm_dump(&t, &p->tcf_tm);
	if (nla_put_64bit(skb, TCA_PEDIT_TM, sizeof(t), &t, TCA_PEDIT_PAD))
		goto nla_put_failure;
	spin_unlock_bh(&p->tcf_lock);

	kfree(opt);
	return skb->len;

nla_put_failure:
	spin_unlock_bh(&p->tcf_lock);
	nlmsg_trim(skb, b);
	kfree(opt);
	return -1;
}
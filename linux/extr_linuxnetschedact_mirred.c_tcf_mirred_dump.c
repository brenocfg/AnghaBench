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
struct tcf_mirred {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  tcfm_eaction; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tc_mirred {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  eaction; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_MIRRED_PAD ; 
 int /*<<< orphan*/  TCA_MIRRED_PARMS ; 
 int /*<<< orphan*/  TCA_MIRRED_TM ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_mirred*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct net_device* tcf_mirred_dev_dereference (struct tcf_mirred*) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_mirred* to_mirred (struct tc_action*) ; 

__attribute__((used)) static int tcf_mirred_dump(struct sk_buff *skb, struct tc_action *a, int bind,
			   int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_mirred *m = to_mirred(a);
	struct tc_mirred opt = {
		.index   = m->tcf_index,
		.refcnt  = refcount_read(&m->tcf_refcnt) - ref,
		.bindcnt = atomic_read(&m->tcf_bindcnt) - bind,
	};
	struct net_device *dev;
	struct tcf_t t;

	spin_lock_bh(&m->tcf_lock);
	opt.action = m->tcf_action;
	opt.eaction = m->tcfm_eaction;
	dev = tcf_mirred_dev_dereference(m);
	if (dev)
		opt.ifindex = dev->ifindex;

	if (nla_put(skb, TCA_MIRRED_PARMS, sizeof(opt), &opt))
		goto nla_put_failure;

	tcf_tm_dump(&t, &m->tcf_tm);
	if (nla_put_64bit(skb, TCA_MIRRED_TM, sizeof(t), &t, TCA_MIRRED_PAD))
		goto nla_put_failure;
	spin_unlock_bh(&m->tcf_lock);

	return skb->len;

nla_put_failure:
	spin_unlock_bh(&m->tcf_lock);
	nlmsg_trim(skb, b);
	return -1;
}
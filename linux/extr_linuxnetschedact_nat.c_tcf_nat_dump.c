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
struct tcf_nat {int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_index; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  new_addr; int /*<<< orphan*/  old_addr; } ;
struct tc_nat {int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  action; int /*<<< orphan*/  index; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  new_addr; int /*<<< orphan*/  old_addr; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_NAT_PAD ; 
 int /*<<< orphan*/  TCA_NAT_PARMS ; 
 int /*<<< orphan*/  TCA_NAT_TM ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_nat*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_nat* to_tcf_nat (struct tc_action*) ; 

__attribute__((used)) static int tcf_nat_dump(struct sk_buff *skb, struct tc_action *a,
			int bind, int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_nat *p = to_tcf_nat(a);
	struct tc_nat opt = {
		.old_addr = p->old_addr,
		.new_addr = p->new_addr,
		.mask     = p->mask,
		.flags    = p->flags,

		.index    = p->tcf_index,
		.action   = p->tcf_action,
		.refcnt   = refcount_read(&p->tcf_refcnt) - ref,
		.bindcnt  = atomic_read(&p->tcf_bindcnt) - bind,
	};
	struct tcf_t t;

	if (nla_put(skb, TCA_NAT_PARMS, sizeof(opt), &opt))
		goto nla_put_failure;

	tcf_tm_dump(&t, &p->tcf_tm);
	if (nla_put_64bit(skb, TCA_NAT_TM, sizeof(t), &t, TCA_NAT_PAD))
		goto nla_put_failure;

	return skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}
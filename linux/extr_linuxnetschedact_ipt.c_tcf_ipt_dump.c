#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tm ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_1__ user; } ;
struct xt_entry_target {TYPE_2__ u; scalar_t__ refcnt; scalar_t__ bindcnt; } ;
struct tcf_t {int dummy; } ;
struct tcf_ipt {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  tcfi_tname; int /*<<< orphan*/  tcfi_hook; int /*<<< orphan*/  tcf_index; TYPE_7__* tcfi_t; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_bindcnt; } ;
struct tc_cnt {TYPE_2__ u; scalar_t__ refcnt; scalar_t__ bindcnt; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
struct TYPE_12__ {int target_size; } ;
struct TYPE_11__ {TYPE_3__* target; } ;
struct TYPE_13__ {TYPE_5__ user; TYPE_4__ kernel; } ;
struct TYPE_14__ {TYPE_6__ u; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TCA_IPT_CNT ; 
 int /*<<< orphan*/  TCA_IPT_HOOK ; 
 int /*<<< orphan*/  TCA_IPT_INDEX ; 
 int /*<<< orphan*/  TCA_IPT_PAD ; 
 int /*<<< orphan*/  TCA_IPT_TABLE ; 
 int /*<<< orphan*/  TCA_IPT_TARG ; 
 int /*<<< orphan*/  TCA_IPT_TM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct xt_entry_target*) ; 
 struct xt_entry_target* kmemdup (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct xt_entry_target*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_ipt* to_ipt (struct tc_action*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_ipt_dump(struct sk_buff *skb, struct tc_action *a, int bind,
			int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_ipt *ipt = to_ipt(a);
	struct xt_entry_target *t;
	struct tcf_t tm;
	struct tc_cnt c;

	/* for simple targets kernel size == user size
	 * user name = target name
	 * for foolproof you need to not assume this
	 */

	spin_lock_bh(&ipt->tcf_lock);
	t = kmemdup(ipt->tcfi_t, ipt->tcfi_t->u.user.target_size, GFP_ATOMIC);
	if (unlikely(!t))
		goto nla_put_failure;

	c.bindcnt = atomic_read(&ipt->tcf_bindcnt) - bind;
	c.refcnt = refcount_read(&ipt->tcf_refcnt) - ref;
	strcpy(t->u.user.name, ipt->tcfi_t->u.kernel.target->name);

	if (nla_put(skb, TCA_IPT_TARG, ipt->tcfi_t->u.user.target_size, t) ||
	    nla_put_u32(skb, TCA_IPT_INDEX, ipt->tcf_index) ||
	    nla_put_u32(skb, TCA_IPT_HOOK, ipt->tcfi_hook) ||
	    nla_put(skb, TCA_IPT_CNT, sizeof(struct tc_cnt), &c) ||
	    nla_put_string(skb, TCA_IPT_TABLE, ipt->tcfi_tname))
		goto nla_put_failure;

	tcf_tm_dump(&tm, &ipt->tcf_tm);
	if (nla_put_64bit(skb, TCA_IPT_TM, sizeof(tm), &tm, TCA_IPT_PAD))
		goto nla_put_failure;

	spin_unlock_bh(&ipt->tcf_lock);
	kfree(t);
	return skb->len;

nla_put_failure:
	spin_unlock_bh(&ipt->tcf_lock);
	nlmsg_trim(skb, b);
	kfree(t);
	return -1;
}
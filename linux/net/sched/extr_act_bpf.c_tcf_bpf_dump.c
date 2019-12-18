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
typedef  int /*<<< orphan*/  tm ;
struct tcf_t {int dummy; } ;
struct tcf_bpf {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tc_action {int dummy; } ;
struct tc_act_bpf {int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_ACT_BPF_PAD ; 
 int /*<<< orphan*/  TCA_ACT_BPF_PARMS ; 
 int /*<<< orphan*/  TCA_ACT_BPF_TM ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_act_bpf*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tcf_bpf_dump_bpf_info (struct tcf_bpf*,struct sk_buff*) ; 
 int tcf_bpf_dump_ebpf_info (struct tcf_bpf*,struct sk_buff*) ; 
 scalar_t__ tcf_bpf_is_ebpf (struct tcf_bpf*) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_bpf* to_bpf (struct tc_action*) ; 

__attribute__((used)) static int tcf_bpf_dump(struct sk_buff *skb, struct tc_action *act,
			int bind, int ref)
{
	unsigned char *tp = skb_tail_pointer(skb);
	struct tcf_bpf *prog = to_bpf(act);
	struct tc_act_bpf opt = {
		.index   = prog->tcf_index,
		.refcnt  = refcount_read(&prog->tcf_refcnt) - ref,
		.bindcnt = atomic_read(&prog->tcf_bindcnt) - bind,
	};
	struct tcf_t tm;
	int ret;

	spin_lock_bh(&prog->tcf_lock);
	opt.action = prog->tcf_action;
	if (nla_put(skb, TCA_ACT_BPF_PARMS, sizeof(opt), &opt))
		goto nla_put_failure;

	if (tcf_bpf_is_ebpf(prog))
		ret = tcf_bpf_dump_ebpf_info(prog, skb);
	else
		ret = tcf_bpf_dump_bpf_info(prog, skb);
	if (ret)
		goto nla_put_failure;

	tcf_tm_dump(&tm, &prog->tcf_tm);
	if (nla_put_64bit(skb, TCA_ACT_BPF_TM, sizeof(tm), &tm,
			  TCA_ACT_BPF_PAD))
		goto nla_put_failure;

	spin_unlock_bh(&prog->tcf_lock);
	return skb->len;

nla_put_failure:
	spin_unlock_bh(&prog->tcf_lock);
	nlmsg_trim(skb, tp);
	return -1;
}
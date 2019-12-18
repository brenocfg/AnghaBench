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
struct tc_ife {int /*<<< orphan*/  flags; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tcf_ife_params {struct tc_ife eth_type; struct tc_ife* eth_src; struct tc_ife* eth_dst; int /*<<< orphan*/  flags; } ;
struct tcf_ife_info {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  params; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  TCA_IFE_DMAC ; 
 int /*<<< orphan*/  TCA_IFE_PAD ; 
 int /*<<< orphan*/  TCA_IFE_PARMS ; 
 int /*<<< orphan*/  TCA_IFE_SMAC ; 
 int /*<<< orphan*/  TCA_IFE_TM ; 
 int /*<<< orphan*/  TCA_IFE_TYPE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ dump_metalist (struct sk_buff*,struct tcf_ife_info*) ; 
 int /*<<< orphan*/  is_zero_ether_addr (struct tc_ife*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_ife*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct tcf_ife_params* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_ife_info* to_ife (struct tc_action*) ; 

__attribute__((used)) static int tcf_ife_dump(struct sk_buff *skb, struct tc_action *a, int bind,
			int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_ife_info *ife = to_ife(a);
	struct tcf_ife_params *p;
	struct tc_ife opt = {
		.index = ife->tcf_index,
		.refcnt = refcount_read(&ife->tcf_refcnt) - ref,
		.bindcnt = atomic_read(&ife->tcf_bindcnt) - bind,
	};
	struct tcf_t t;

	spin_lock_bh(&ife->tcf_lock);
	opt.action = ife->tcf_action;
	p = rcu_dereference_protected(ife->params,
				      lockdep_is_held(&ife->tcf_lock));
	opt.flags = p->flags;

	if (nla_put(skb, TCA_IFE_PARMS, sizeof(opt), &opt))
		goto nla_put_failure;

	tcf_tm_dump(&t, &ife->tcf_tm);
	if (nla_put_64bit(skb, TCA_IFE_TM, sizeof(t), &t, TCA_IFE_PAD))
		goto nla_put_failure;

	if (!is_zero_ether_addr(p->eth_dst)) {
		if (nla_put(skb, TCA_IFE_DMAC, ETH_ALEN, p->eth_dst))
			goto nla_put_failure;
	}

	if (!is_zero_ether_addr(p->eth_src)) {
		if (nla_put(skb, TCA_IFE_SMAC, ETH_ALEN, p->eth_src))
			goto nla_put_failure;
	}

	if (nla_put(skb, TCA_IFE_TYPE, 2, &p->eth_type))
		goto nla_put_failure;

	if (dump_metalist(skb, ife)) {
		/*ignore failure to dump metalist */
		pr_info("Failed to dump metalist\n");
	}

	spin_unlock_bh(&ife->tcf_lock);
	return skb->len;

nla_put_failure:
	spin_unlock_bh(&ife->tcf_lock);
	nlmsg_trim(skb, b);
	return -1;
}
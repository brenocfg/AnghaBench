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
struct tcf_ctinfo_params {int mode; int /*<<< orphan*/  cpmarkmask; int /*<<< orphan*/  dscpstatemask; int /*<<< orphan*/  dscpmask; int /*<<< orphan*/  zone; } ;
struct tcf_ctinfo {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  stats_cpmark_set; int /*<<< orphan*/  stats_dscp_error; int /*<<< orphan*/  stats_dscp_set; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_tm; int /*<<< orphan*/  params; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tc_ctinfo {int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int CTINFO_MODE_CPMARK ; 
 int CTINFO_MODE_DSCP ; 
 int /*<<< orphan*/  TCA_CTINFO_ACT ; 
 int /*<<< orphan*/  TCA_CTINFO_PAD ; 
 int /*<<< orphan*/  TCA_CTINFO_PARMS_CPMARK_MASK ; 
 int /*<<< orphan*/  TCA_CTINFO_PARMS_DSCP_MASK ; 
 int /*<<< orphan*/  TCA_CTINFO_PARMS_DSCP_STATEMASK ; 
 int /*<<< orphan*/  TCA_CTINFO_STATS_CPMARK_SET ; 
 int /*<<< orphan*/  TCA_CTINFO_STATS_DSCP_ERROR ; 
 int /*<<< orphan*/  TCA_CTINFO_STATS_DSCP_SET ; 
 int /*<<< orphan*/  TCA_CTINFO_TM ; 
 int /*<<< orphan*/  TCA_CTINFO_ZONE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_ctinfo*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 struct tcf_ctinfo_params* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_tm_dump (struct tcf_t*,int /*<<< orphan*/ *) ; 
 struct tcf_ctinfo* to_ctinfo (struct tc_action*) ; 

__attribute__((used)) static int tcf_ctinfo_dump(struct sk_buff *skb, struct tc_action *a,
			   int bind, int ref)
{
	struct tcf_ctinfo *ci = to_ctinfo(a);
	struct tc_ctinfo opt = {
		.index   = ci->tcf_index,
		.refcnt  = refcount_read(&ci->tcf_refcnt) - ref,
		.bindcnt = atomic_read(&ci->tcf_bindcnt) - bind,
	};
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_ctinfo_params *cp;
	struct tcf_t t;

	spin_lock_bh(&ci->tcf_lock);
	cp = rcu_dereference_protected(ci->params,
				       lockdep_is_held(&ci->tcf_lock));

	tcf_tm_dump(&t, &ci->tcf_tm);
	if (nla_put_64bit(skb, TCA_CTINFO_TM, sizeof(t), &t, TCA_CTINFO_PAD))
		goto nla_put_failure;

	opt.action = ci->tcf_action;
	if (nla_put(skb, TCA_CTINFO_ACT, sizeof(opt), &opt))
		goto nla_put_failure;

	if (nla_put_u16(skb, TCA_CTINFO_ZONE, cp->zone))
		goto nla_put_failure;

	if (cp->mode & CTINFO_MODE_DSCP) {
		if (nla_put_u32(skb, TCA_CTINFO_PARMS_DSCP_MASK,
				cp->dscpmask))
			goto nla_put_failure;
		if (nla_put_u32(skb, TCA_CTINFO_PARMS_DSCP_STATEMASK,
				cp->dscpstatemask))
			goto nla_put_failure;
	}

	if (cp->mode & CTINFO_MODE_CPMARK) {
		if (nla_put_u32(skb, TCA_CTINFO_PARMS_CPMARK_MASK,
				cp->cpmarkmask))
			goto nla_put_failure;
	}

	if (nla_put_u64_64bit(skb, TCA_CTINFO_STATS_DSCP_SET,
			      ci->stats_dscp_set, TCA_CTINFO_PAD))
		goto nla_put_failure;

	if (nla_put_u64_64bit(skb, TCA_CTINFO_STATS_DSCP_ERROR,
			      ci->stats_dscp_error, TCA_CTINFO_PAD))
		goto nla_put_failure;

	if (nla_put_u64_64bit(skb, TCA_CTINFO_STATS_CPMARK_SET,
			      ci->stats_cpmark_set, TCA_CTINFO_PAD))
		goto nla_put_failure;

	spin_unlock_bh(&ci->tcf_lock);
	return skb->len;

nla_put_failure:
	spin_unlock_bh(&ci->tcf_lock);
	nlmsg_trim(skb, b);
	return -1;
}
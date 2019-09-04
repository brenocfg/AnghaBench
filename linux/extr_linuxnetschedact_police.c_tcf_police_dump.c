#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
struct tcf_t {void* expires; void* firstuse; void* lastuse; void* install; } ;
struct TYPE_2__ {scalar_t__ expires; scalar_t__ firstuse; scalar_t__ lastuse; scalar_t__ install; } ;
struct tcf_police {int /*<<< orphan*/  tcf_lock; TYPE_1__ tcf_tm; scalar_t__ tcfp_ewma_rate; scalar_t__ tcfp_result; int /*<<< orphan*/  peak; scalar_t__ peak_present; int /*<<< orphan*/  rate; scalar_t__ rate_present; int /*<<< orphan*/  tcfp_burst; int /*<<< orphan*/  tcfp_mtu; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tc_police {int /*<<< orphan*/  peakrate; int /*<<< orphan*/  rate; int /*<<< orphan*/  burst; int /*<<< orphan*/  mtu; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  PSCHED_NS2TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCA_POLICE_AVRATE ; 
 int /*<<< orphan*/  TCA_POLICE_PAD ; 
 int /*<<< orphan*/  TCA_POLICE_RESULT ; 
 int /*<<< orphan*/  TCA_POLICE_TBF ; 
 int /*<<< orphan*/  TCA_POLICE_TM ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 void* jiffies_to_clock_t (scalar_t__) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_police*) ; 
 scalar_t__ nla_put_64bit (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 int /*<<< orphan*/  psched_ratecfg_getrate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct tcf_police* to_police (struct tc_action*) ; 

__attribute__((used)) static int tcf_police_dump(struct sk_buff *skb, struct tc_action *a,
			       int bind, int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_police *police = to_police(a);
	struct tc_police opt = {
		.index = police->tcf_index,
		.refcnt = refcount_read(&police->tcf_refcnt) - ref,
		.bindcnt = atomic_read(&police->tcf_bindcnt) - bind,
	};
	struct tcf_t t;

	spin_lock_bh(&police->tcf_lock);
	opt.action = police->tcf_action;
	opt.mtu = police->tcfp_mtu;
	opt.burst = PSCHED_NS2TICKS(police->tcfp_burst);
	if (police->rate_present)
		psched_ratecfg_getrate(&opt.rate, &police->rate);
	if (police->peak_present)
		psched_ratecfg_getrate(&opt.peakrate, &police->peak);
	if (nla_put(skb, TCA_POLICE_TBF, sizeof(opt), &opt))
		goto nla_put_failure;
	if (police->tcfp_result &&
	    nla_put_u32(skb, TCA_POLICE_RESULT, police->tcfp_result))
		goto nla_put_failure;
	if (police->tcfp_ewma_rate &&
	    nla_put_u32(skb, TCA_POLICE_AVRATE, police->tcfp_ewma_rate))
		goto nla_put_failure;

	t.install = jiffies_to_clock_t(jiffies - police->tcf_tm.install);
	t.lastuse = jiffies_to_clock_t(jiffies - police->tcf_tm.lastuse);
	t.firstuse = jiffies_to_clock_t(jiffies - police->tcf_tm.firstuse);
	t.expires = jiffies_to_clock_t(police->tcf_tm.expires);
	if (nla_put_64bit(skb, TCA_POLICE_TM, sizeof(t), &t, TCA_POLICE_PAD))
		goto nla_put_failure;
	spin_unlock_bh(&police->tcf_lock);

	return skb->len;

nla_put_failure:
	spin_unlock_bh(&police->tcf_lock);
	nlmsg_trim(skb, b);
	return -1;
}
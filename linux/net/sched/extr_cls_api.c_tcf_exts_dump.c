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
struct tcf_exts {scalar_t__ type; scalar_t__ police; int /*<<< orphan*/  actions; scalar_t__ action; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 scalar_t__ TCA_OLD_COMPAT ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,scalar_t__) ; 
 scalar_t__ tcf_action_dump (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_action_dump_old (struct sk_buff*,struct tc_action*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tc_action* tcf_exts_first_act (struct tcf_exts*) ; 
 scalar_t__ tcf_exts_has_actions (struct tcf_exts*) ; 

int tcf_exts_dump(struct sk_buff *skb, struct tcf_exts *exts)
{
#ifdef CONFIG_NET_CLS_ACT
	struct nlattr *nest;

	if (exts->action && tcf_exts_has_actions(exts)) {
		/*
		 * again for backward compatible mode - we want
		 * to work with both old and new modes of entering
		 * tc data even if iproute2  was newer - jhs
		 */
		if (exts->type != TCA_OLD_COMPAT) {
			nest = nla_nest_start_noflag(skb, exts->action);
			if (nest == NULL)
				goto nla_put_failure;

			if (tcf_action_dump(skb, exts->actions, 0, 0) < 0)
				goto nla_put_failure;
			nla_nest_end(skb, nest);
		} else if (exts->police) {
			struct tc_action *act = tcf_exts_first_act(exts);
			nest = nla_nest_start_noflag(skb, exts->police);
			if (nest == NULL || !act)
				goto nla_put_failure;
			if (tcf_action_dump_old(skb, act, 0, 0) < 0)
				goto nla_put_failure;
			nla_nest_end(skb, nest);
		}
	}
	return 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
#else
	return 0;
#endif
}
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
typedef  int u32 ;
struct tcf_result {int dummy; } ;
struct tc_action {int /*<<< orphan*/  goto_chain; TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int (* act ) (struct sk_buff*,struct tc_action const*,struct tcf_result*) ;} ;

/* Variables and functions */
 int TCA_ACT_MAX_PRIO ; 
 int TCA_ACT_MAX_PRIO_MASK ; 
 scalar_t__ TC_ACT_EXT_CMP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_ACT_GOTO_CHAIN ; 
 int /*<<< orphan*/  TC_ACT_JUMP ; 
 int TC_ACT_OK ; 
 int TC_ACT_PIPE ; 
 int TC_ACT_REPEAT ; 
 int TC_ACT_SHOT ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_skip_tc_classify (struct sk_buff*) ; 
 int stub1 (struct sk_buff*,struct tc_action const*,struct tcf_result*) ; 
 int /*<<< orphan*/  tcf_action_goto_chain_exec (struct tc_action const*,struct tcf_result*) ; 
 scalar_t__ unlikely (int) ; 

int tcf_action_exec(struct sk_buff *skb, struct tc_action **actions,
		    int nr_actions, struct tcf_result *res)
{
	u32 jmp_prgcnt = 0;
	u32 jmp_ttl = TCA_ACT_MAX_PRIO; /*matches actions per filter */
	int i;
	int ret = TC_ACT_OK;

	if (skb_skip_tc_classify(skb))
		return TC_ACT_OK;

restart_act_graph:
	for (i = 0; i < nr_actions; i++) {
		const struct tc_action *a = actions[i];

		if (jmp_prgcnt > 0) {
			jmp_prgcnt -= 1;
			continue;
		}
repeat:
		ret = a->ops->act(skb, a, res);
		if (ret == TC_ACT_REPEAT)
			goto repeat;	/* we need a ttl - JHS */

		if (TC_ACT_EXT_CMP(ret, TC_ACT_JUMP)) {
			jmp_prgcnt = ret & TCA_ACT_MAX_PRIO_MASK;
			if (!jmp_prgcnt || (jmp_prgcnt > nr_actions)) {
				/* faulty opcode, stop pipeline */
				return TC_ACT_OK;
			} else {
				jmp_ttl -= 1;
				if (jmp_ttl > 0)
					goto restart_act_graph;
				else /* faulty graph, stop pipeline */
					return TC_ACT_OK;
			}
		} else if (TC_ACT_EXT_CMP(ret, TC_ACT_GOTO_CHAIN)) {
			if (unlikely(!rcu_access_pointer(a->goto_chain))) {
				net_warn_ratelimited("can't go to NULL chain!\n");
				return TC_ACT_SHOT;
			}
			tcf_action_goto_chain_exec(a, res);
		}

		if (ret != TC_ACT_PIPE)
			break;
	}

	return ret;
}
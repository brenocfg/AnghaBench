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
struct tcf_proto {int /*<<< orphan*/  next; } ;
struct tcf_chain_info {scalar_t__* pprev; } ;
struct tcf_chain {scalar_t__ filter_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (scalar_t__,struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_chain0_head_change (struct tcf_chain*,struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_chain_hold (struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_tp_prev (struct tcf_chain_info*) ; 

__attribute__((used)) static void tcf_chain_tp_insert(struct tcf_chain *chain,
				struct tcf_chain_info *chain_info,
				struct tcf_proto *tp)
{
	if (*chain_info->pprev == chain->filter_chain)
		tcf_chain0_head_change(chain, tp);
	RCU_INIT_POINTER(tp->next, tcf_chain_tp_prev(chain_info));
	rcu_assign_pointer(*chain_info->pprev, tp);
	tcf_chain_hold(chain);
}
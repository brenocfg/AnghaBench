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
struct tcf_proto {int dummy; } ;
struct tcf_chain_info {int /*<<< orphan*/ * pprev; int /*<<< orphan*/  next; } ;
struct tcf_chain {struct tcf_proto* filter_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_chain0_head_change (struct tcf_chain*,struct tcf_proto*) ; 
 struct tcf_proto* tcf_chain_dereference (int /*<<< orphan*/ ,struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_proto_mark_delete (struct tcf_proto*) ; 

__attribute__((used)) static void tcf_chain_tp_remove(struct tcf_chain *chain,
				struct tcf_chain_info *chain_info,
				struct tcf_proto *tp)
{
	struct tcf_proto *next = tcf_chain_dereference(chain_info->next, chain);

	tcf_proto_mark_delete(tp);
	if (tp == chain->filter_chain)
		tcf_chain0_head_change(chain, next);
	RCU_INIT_POINTER(*chain_info->pprev, next);
}
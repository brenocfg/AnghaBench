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
struct tcf_proto {TYPE_1__* chain; } ;
struct tc_action {int tcfa_action; int /*<<< orphan*/  goto_chain; } ;
struct TYPE_2__ {int /*<<< orphan*/  block; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int TC_ACT_EXT_VAL_MASK ; 
 int /*<<< orphan*/  tcf_chain_get_by_act (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tcf_action_goto_chain_init(struct tc_action *a, struct tcf_proto *tp)
{
	u32 chain_index = a->tcfa_action & TC_ACT_EXT_VAL_MASK;

	if (!tp)
		return -EINVAL;
	a->goto_chain = tcf_chain_get_by_act(tp->chain->block, chain_index);
	if (!a->goto_chain)
		return -ENOMEM;
	return 0;
}
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
struct tcf_chain {int dummy; } ;
struct tc_action {int tcfa_action; int /*<<< orphan*/  goto_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_swap_protected (int /*<<< orphan*/ ,struct tcf_chain*,int) ; 

struct tcf_chain *tcf_action_set_ctrlact(struct tc_action *a, int action,
					 struct tcf_chain *goto_chain)
{
	a->tcfa_action = action;
	rcu_swap_protected(a->goto_chain, goto_chain, 1);
	return goto_chain;
}
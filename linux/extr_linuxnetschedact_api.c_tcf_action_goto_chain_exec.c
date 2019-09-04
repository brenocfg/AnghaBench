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
struct tcf_result {int /*<<< orphan*/  goto_tp; } ;
struct tcf_chain {int /*<<< orphan*/  filter_chain; } ;
struct tc_action {struct tcf_chain* goto_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_dereference_bh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcf_action_goto_chain_exec(const struct tc_action *a,
				       struct tcf_result *res)
{
	const struct tcf_chain *chain = a->goto_chain;

	res->goto_tp = rcu_dereference_bh(chain->filter_chain);
}
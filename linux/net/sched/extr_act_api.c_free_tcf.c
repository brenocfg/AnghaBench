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
struct tc_action {int /*<<< orphan*/  act_cookie; int /*<<< orphan*/  cpu_qstats; int /*<<< orphan*/  cpu_bstats_hw; int /*<<< orphan*/  cpu_bstats; int /*<<< orphan*/  goto_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tc_action*) ; 
 struct tcf_chain* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcf_chain_put_by_act (struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_set_action_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_tcf(struct tc_action *p)
{
	struct tcf_chain *chain = rcu_dereference_protected(p->goto_chain, 1);

	free_percpu(p->cpu_bstats);
	free_percpu(p->cpu_bstats_hw);
	free_percpu(p->cpu_qstats);

	tcf_set_action_cookie(&p->act_cookie, NULL);
	if (chain)
		tcf_chain_put_by_act(chain);

	kfree(p);
}
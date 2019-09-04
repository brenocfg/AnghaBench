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
struct tc_action {scalar_t__ goto_chain; int /*<<< orphan*/  act_cookie; int /*<<< orphan*/  cpu_qstats; int /*<<< orphan*/  cpu_bstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tc_action*) ; 
 int /*<<< orphan*/  tcf_action_goto_chain_fini (struct tc_action*) ; 
 int /*<<< orphan*/  tcf_set_action_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_tcf(struct tc_action *p)
{
	free_percpu(p->cpu_bstats);
	free_percpu(p->cpu_qstats);

	tcf_set_action_cookie(&p->act_cookie, NULL);
	if (p->goto_chain)
		tcf_action_goto_chain_fini(p);

	kfree(p);
}
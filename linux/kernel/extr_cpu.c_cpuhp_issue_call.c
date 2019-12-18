#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hlist_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  single; } ;
struct TYPE_3__ {int /*<<< orphan*/  single; } ;
struct cpuhp_step {TYPE_2__ teardown; TYPE_1__ startup; } ;
typedef  enum cpuhp_state { ____Placeholder_cpuhp_state } cpuhp_state ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct cpuhp_step* cpuhp_get_step (int) ; 
 int cpuhp_invoke_ap_callback (int,int,int,struct hlist_node*) ; 
 int cpuhp_invoke_callback (int,int,int,struct hlist_node*,int /*<<< orphan*/ *) ; 
 scalar_t__ cpuhp_is_ap_state (int) ; 

__attribute__((used)) static int cpuhp_issue_call(int cpu, enum cpuhp_state state, bool bringup,
			    struct hlist_node *node)
{
	struct cpuhp_step *sp = cpuhp_get_step(state);
	int ret;

	/*
	 * If there's nothing to do, we done.
	 * Relies on the union for multi_instance.
	 */
	if ((bringup && !sp->startup.single) ||
	    (!bringup && !sp->teardown.single))
		return 0;
	/*
	 * The non AP bound callbacks can fail on bringup. On teardown
	 * e.g. module removal we crash for now.
	 */
#ifdef CONFIG_SMP
	if (cpuhp_is_ap_state(state))
		ret = cpuhp_invoke_ap_callback(cpu, state, bringup, node);
	else
		ret = cpuhp_invoke_callback(cpu, state, bringup, node, NULL);
#else
	ret = cpuhp_invoke_callback(cpu, state, bringup, node, NULL);
#endif
	BUG_ON(ret && !bringup);
	return ret;
}
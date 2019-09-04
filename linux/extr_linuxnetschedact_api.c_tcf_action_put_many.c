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
struct tc_action_ops {int /*<<< orphan*/  owner; } ;
struct tc_action {struct tc_action_ops* ops; } ;

/* Variables and functions */
 int TCA_ACT_MAX_PRIO ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_action_put (struct tc_action*) ; 

__attribute__((used)) static void tcf_action_put_many(struct tc_action *actions[])
{
	int i;

	for (i = 0; i < TCA_ACT_MAX_PRIO; i++) {
		struct tc_action *a = actions[i];
		const struct tc_action_ops *ops;

		if (!a)
			continue;
		ops = a->ops;
		if (tcf_action_put(a))
			module_put(ops->owner);
	}
}
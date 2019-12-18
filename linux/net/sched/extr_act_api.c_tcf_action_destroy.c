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
 int ACT_P_DELETED ; 
 int TCA_ACT_MAX_PRIO ; 
 int __tcf_idr_release (struct tc_action*,int,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

int tcf_action_destroy(struct tc_action *actions[], int bind)
{
	const struct tc_action_ops *ops;
	struct tc_action *a;
	int ret = 0, i;

	for (i = 0; i < TCA_ACT_MAX_PRIO && actions[i]; i++) {
		a = actions[i];
		actions[i] = NULL;
		ops = a->ops;
		ret = __tcf_idr_release(a, bind, true);
		if (ret == ACT_P_DELETED)
			module_put(ops->owner);
		else if (ret < 0)
			return ret;
	}
	return ret;
}
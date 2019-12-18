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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_idrinfo {int dummy; } ;
struct tc_action_ops {int /*<<< orphan*/  owner; } ;
struct tc_action {int /*<<< orphan*/  tcfa_index; struct tcf_idrinfo* idrinfo; struct tc_action_ops* ops; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int TCA_ACT_MAX_PRIO ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_action_put (struct tc_action*) ; 
 int tcf_idr_delete_index (struct tcf_idrinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcf_action_delete(struct net *net, struct tc_action *actions[])
{
	int i;

	for (i = 0; i < TCA_ACT_MAX_PRIO && actions[i]; i++) {
		struct tc_action *a = actions[i];
		const struct tc_action_ops *ops = a->ops;
		/* Actions can be deleted concurrently so we must save their
		 * type and id to search again after reference is released.
		 */
		struct tcf_idrinfo *idrinfo = a->idrinfo;
		u32 act_index = a->tcfa_index;

		actions[i] = NULL;
		if (tcf_action_put(a)) {
			/* last reference, action was deleted concurrently */
			module_put(ops->owner);
		} else  {
			int ret;

			/* now do the delete */
			ret = tcf_idr_delete_index(idrinfo, act_index);
			if (ret < 0)
				return ret;
		}
	}
	return 0;
}
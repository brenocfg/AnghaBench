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
struct tc_action {int /*<<< orphan*/  tcfa_bindcnt; } ;

/* Variables and functions */
 int ACT_P_DELETED ; 
 int EPERM ; 
 scalar_t__ __tcf_action_put (struct tc_action*,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

int __tcf_idr_release(struct tc_action *p, bool bind, bool strict)
{
	int ret = 0;

	/* Release with strict==1 and bind==0 is only called through act API
	 * interface (classifiers always bind). Only case when action with
	 * positive reference count and zero bind count can exist is when it was
	 * also created with act API (unbinding last classifier will destroy the
	 * action if it was created by classifier). So only case when bind count
	 * can be changed after initial check is when unbound action is
	 * destroyed by act API while classifier binds to action with same id
	 * concurrently. This result either creation of new action(same behavior
	 * as before), or reusing existing action if concurrent process
	 * increments reference count before action is deleted. Both scenarios
	 * are acceptable.
	 */
	if (p) {
		if (!bind && strict && atomic_read(&p->tcfa_bindcnt) > 0)
			return -EPERM;

		if (__tcf_action_put(p, bind))
			ret = ACT_P_DELETED;
	}

	return ret;
}
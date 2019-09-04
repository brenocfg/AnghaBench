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
struct blocking_notifier_head {int /*<<< orphan*/  rwsem; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int notifier_call_chain (int /*<<< orphan*/ *,unsigned long,void*,int,int*) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int __blocking_notifier_call_chain(struct blocking_notifier_head *nh,
				   unsigned long val, void *v,
				   int nr_to_call, int *nr_calls)
{
	int ret = NOTIFY_DONE;

	/*
	 * We check the head outside the lock, but if this access is
	 * racy then it does not matter what the result of the test
	 * is, we re-check the list after having taken the lock anyway:
	 */
	if (rcu_access_pointer(nh->head)) {
		down_read(&nh->rwsem);
		ret = notifier_call_chain(&nh->head, val, v, nr_to_call,
					nr_calls);
		up_read(&nh->rwsem);
	}
	return ret;
}
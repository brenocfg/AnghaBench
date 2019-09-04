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
struct atomic_notifier_head {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int notifier_call_chain (int /*<<< orphan*/ *,unsigned long,void*,int,int*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int __atomic_notifier_call_chain(struct atomic_notifier_head *nh,
				 unsigned long val, void *v,
				 int nr_to_call, int *nr_calls)
{
	int ret;

	rcu_read_lock();
	ret = notifier_call_chain(&nh->head, val, v, nr_to_call, nr_calls);
	rcu_read_unlock();
	return ret;
}
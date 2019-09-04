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
struct kern_ipc_perm {int /*<<< orphan*/  rcu; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,void (*) (struct rcu_head*)) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void ipc_rcu_putref(struct kern_ipc_perm *ptr,
			void (*func)(struct rcu_head *head))
{
	if (!refcount_dec_and_test(&ptr->refcount))
		return;

	call_rcu(&ptr->rcu, func);
}
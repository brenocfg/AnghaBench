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
struct dlm_lock_resource {int state; int /*<<< orphan*/  asts_reserved; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_LOCK_RES_MIGRATING ; 
 int /*<<< orphan*/  __dlm_print_one_lock_resource (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

void __dlm_lockres_reserve_ast(struct dlm_lock_resource *res)
{
	assert_spin_locked(&res->spinlock);
	if (res->state & DLM_LOCK_RES_MIGRATING) {
		__dlm_print_one_lock_resource(res);
	}
	BUG_ON(res->state & DLM_LOCK_RES_MIGRATING);

	atomic_inc(&res->asts_reserved);
}
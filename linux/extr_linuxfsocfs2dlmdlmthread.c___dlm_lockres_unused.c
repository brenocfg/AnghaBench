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
struct dlm_lock_resource {int state; int /*<<< orphan*/  refmap; int /*<<< orphan*/  dirty; scalar_t__ inflight_locks; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int DLM_LOCK_RES_DIRTY ; 
 int DLM_LOCK_RES_RECOVERING ; 
 int DLM_LOCK_RES_RECOVERY_WAITING ; 
 int O2NM_MAX_NODES ; 
 scalar_t__ __dlm_lockres_has_locks (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

int __dlm_lockres_unused(struct dlm_lock_resource *res)
{
	int bit;

	assert_spin_locked(&res->spinlock);

	if (__dlm_lockres_has_locks(res))
		return 0;

	/* Locks are in the process of being created */
	if (res->inflight_locks)
		return 0;

	if (!list_empty(&res->dirty) || res->state & DLM_LOCK_RES_DIRTY)
		return 0;

	if (res->state & (DLM_LOCK_RES_RECOVERING|
			DLM_LOCK_RES_RECOVERY_WAITING))
		return 0;

	/* Another node has this resource with this node as the master */
	bit = find_next_bit(res->refmap, O2NM_MAX_NODES, 0);
	if (bit < O2NM_MAX_NODES)
		return 0;

	return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  wakeup; } ;
struct TYPE_5__ {int /*<<< orphan*/  procLatch; } ;
typedef  TYPE_1__ PGPROC ;
typedef  TYPE_2__ ConditionVariable ;

/* Variables and functions */
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvWaitLink ; 
 int /*<<< orphan*/  proclist_is_empty (int /*<<< orphan*/ *) ; 
 TYPE_1__* proclist_pop_head_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ConditionVariableSignal(ConditionVariable *cv)
{
	PGPROC	   *proc = NULL;

	/* Remove the first process from the wakeup queue (if any). */
	SpinLockAcquire(&cv->mutex);
	if (!proclist_is_empty(&cv->wakeup))
		proc = proclist_pop_head_node(&cv->wakeup, cvWaitLink);
	SpinLockRelease(&cv->mutex);

	/* If we found someone sleeping, set their latch to wake them up. */
	if (proc != NULL)
		SetLatch(&proc->procLatch);
}
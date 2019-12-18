#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WaitEventSet ;
struct TYPE_6__ {int pgprocno; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  wakeup; } ;
typedef  TYPE_1__ ConditionVariable ;

/* Variables and functions */
 int /*<<< orphan*/  AddWaitEventToSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 int /*<<< orphan*/ * CreateWaitEventSet (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * MyLatch ; 
 TYPE_3__* MyProc ; 
 int /*<<< orphan*/  PGINVALID_SOCKET ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  WL_EXIT_ON_PM_DEATH ; 
 int /*<<< orphan*/  WL_LATCH_SET ; 
 int /*<<< orphan*/  cvWaitLink ; 
 TYPE_1__* cv_sleep_target ; 
 int /*<<< orphan*/ * cv_wait_event_set ; 
 int /*<<< orphan*/  proclist_push_tail (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
ConditionVariablePrepareToSleep(ConditionVariable *cv)
{
	int			pgprocno = MyProc->pgprocno;

	/*
	 * If first time through in this process, create a WaitEventSet, which
	 * we'll reuse for all condition variable sleeps.
	 */
	if (cv_wait_event_set == NULL)
	{
		WaitEventSet *new_event_set;

		new_event_set = CreateWaitEventSet(TopMemoryContext, 2);
		AddWaitEventToSet(new_event_set, WL_LATCH_SET, PGINVALID_SOCKET,
						  MyLatch, NULL);
		AddWaitEventToSet(new_event_set, WL_EXIT_ON_PM_DEATH, PGINVALID_SOCKET,
						  NULL, NULL);
		/* Don't set cv_wait_event_set until we have a correct WES. */
		cv_wait_event_set = new_event_set;
	}

	/*
	 * If some other sleep is already prepared, cancel it; this is necessary
	 * because we have just one static variable tracking the prepared sleep,
	 * and also only one cvWaitLink in our PGPROC.  It's okay to do this
	 * because whenever control does return to the other test-and-sleep loop,
	 * its ConditionVariableSleep call will just re-establish that sleep as
	 * the prepared one.
	 */
	if (cv_sleep_target != NULL)
		ConditionVariableCancelSleep();

	/* Record the condition variable on which we will sleep. */
	cv_sleep_target = cv;

	/*
	 * Reset my latch before adding myself to the queue, to ensure that we
	 * don't miss a wakeup that occurs immediately.
	 */
	ResetLatch(MyLatch);

	/* Add myself to the wait queue. */
	SpinLockAcquire(&cv->mutex);
	proclist_push_tail(&cv->wakeup, pgprocno, cvWaitLink);
	SpinLockRelease(&cv->mutex);
}
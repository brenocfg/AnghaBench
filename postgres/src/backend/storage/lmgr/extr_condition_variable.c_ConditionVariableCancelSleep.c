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
struct TYPE_6__ {int /*<<< orphan*/  pgprocno; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  wakeup; } ;
typedef  TYPE_1__ ConditionVariable ;

/* Variables and functions */
 int /*<<< orphan*/  ConditionVariableSignal (TYPE_1__*) ; 
 TYPE_3__* MyProc ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvWaitLink ; 
 TYPE_1__* cv_sleep_target ; 
 scalar_t__ proclist_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proclist_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ConditionVariableCancelSleep(void)
{
	ConditionVariable *cv = cv_sleep_target;
	bool		signaled = false;

	if (cv == NULL)
		return;

	SpinLockAcquire(&cv->mutex);
	if (proclist_contains(&cv->wakeup, MyProc->pgprocno, cvWaitLink))
		proclist_delete(&cv->wakeup, MyProc->pgprocno, cvWaitLink);
	else
		signaled = true;
	SpinLockRelease(&cv->mutex);

	/*
	 * If we've received a signal, pass it on to another waiting process, if
	 * there is one.  Otherwise a call to ConditionVariableSignal() might get
	 * lost, despite there being another process ready to handle it.
	 */
	if (signaled)
		ConditionVariableSignal(cv);

	cv_sleep_target = NULL;
}
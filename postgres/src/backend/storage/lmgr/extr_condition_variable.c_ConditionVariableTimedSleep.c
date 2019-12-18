#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  instr_time ;
typedef  int /*<<< orphan*/  WaitEvent ;
struct TYPE_7__ {int /*<<< orphan*/  pgprocno; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  wakeup; } ;
typedef  TYPE_1__ ConditionVariable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ConditionVariablePrepareToSleep (TYPE_1__*) ; 
 scalar_t__ INSTR_TIME_GET_MILLISEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SUBTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long INT_MAX ; 
 int /*<<< orphan*/  MyLatch ; 
 TYPE_3__* MyProc ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitEventSetWait (int /*<<< orphan*/ ,long,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvWaitLink ; 
 TYPE_1__* cv_sleep_target ; 
 int /*<<< orphan*/  cv_wait_event_set ; 
 int /*<<< orphan*/  proclist_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proclist_push_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
ConditionVariableTimedSleep(ConditionVariable *cv, long timeout,
							uint32 wait_event_info)
{
	long		cur_timeout = -1;
	instr_time	start_time;
	instr_time	cur_time;

	/*
	 * If the caller didn't prepare to sleep explicitly, then do so now and
	 * return immediately.  The caller's predicate loop should immediately
	 * call again if its exit condition is not yet met.  This will result in
	 * the exit condition being tested twice before we first sleep.  The extra
	 * test can be prevented by calling ConditionVariablePrepareToSleep(cv)
	 * first.  Whether it's worth doing that depends on whether you expect the
	 * exit condition to be met initially, in which case skipping the prepare
	 * is recommended because it avoids manipulations of the wait list, or not
	 * met initially, in which case preparing first is better because it
	 * avoids one extra test of the exit condition.
	 *
	 * If we are currently prepared to sleep on some other CV, we just cancel
	 * that and prepare this one; see ConditionVariablePrepareToSleep.
	 */
	if (cv_sleep_target != cv)
	{
		ConditionVariablePrepareToSleep(cv);
		return false;
	}

	/*
	 * Record the current time so that we can calculate the remaining timeout
	 * if we are woken up spuriously.
	 */
	if (timeout >= 0)
	{
		INSTR_TIME_SET_CURRENT(start_time);
		Assert(timeout >= 0 && timeout <= INT_MAX);
		cur_timeout = timeout;
	}

	while (true)
	{
		WaitEvent	event;
		bool		done = false;

		/*
		 * Wait for latch to be set.  (If we're awakened for some other
		 * reason, the code below will cope anyway.)
		 */
		(void) WaitEventSetWait(cv_wait_event_set, cur_timeout, &event, 1,
								wait_event_info);

		/* Reset latch before examining the state of the wait list. */
		ResetLatch(MyLatch);

		CHECK_FOR_INTERRUPTS();

		/*
		 * If this process has been taken out of the wait list, then we know
		 * that it has been signaled by ConditionVariableSignal (or
		 * ConditionVariableBroadcast), so we should return to the caller. But
		 * that doesn't guarantee that the exit condition is met, only that we
		 * ought to check it.  So we must put the process back into the wait
		 * list, to ensure we don't miss any additional wakeup occurring while
		 * the caller checks its exit condition.  We can take ourselves out of
		 * the wait list only when the caller calls
		 * ConditionVariableCancelSleep.
		 *
		 * If we're still in the wait list, then the latch must have been set
		 * by something other than ConditionVariableSignal; though we don't
		 * guarantee not to return spuriously, we'll avoid this obvious case.
		 */
		SpinLockAcquire(&cv->mutex);
		if (!proclist_contains(&cv->wakeup, MyProc->pgprocno, cvWaitLink))
		{
			done = true;
			proclist_push_tail(&cv->wakeup, MyProc->pgprocno, cvWaitLink);
		}
		SpinLockRelease(&cv->mutex);

		/* We were signaled, so return */
		if (done)
			return false;

		/* If we're not done, update cur_timeout for next iteration */
		if (timeout >= 0)
		{
			INSTR_TIME_SET_CURRENT(cur_time);
			INSTR_TIME_SUBTRACT(cur_time, start_time);
			cur_timeout = timeout - (long) INSTR_TIME_GET_MILLISEC(cur_time);

			/* Have we crossed the timeout threshold? */
			if (cur_timeout <= 0)
				return true;
		}
	}
}
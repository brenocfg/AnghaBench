#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  wakeup; } ;
struct TYPE_6__ {int pgprocno; int /*<<< orphan*/  procLatch; } ;
typedef  TYPE_1__ PGPROC ;
typedef  TYPE_2__ ConditionVariable ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 TYPE_1__* MyProc ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvWaitLink ; 
 int /*<<< orphan*/ * cv_sleep_target ; 
 int proclist_contains (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proclist_is_empty (int /*<<< orphan*/ *) ; 
 TYPE_1__* proclist_pop_head_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proclist_push_tail (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
ConditionVariableBroadcast(ConditionVariable *cv)
{
	int			pgprocno = MyProc->pgprocno;
	PGPROC	   *proc = NULL;
	bool		have_sentinel = false;

	/*
	 * In some use-cases, it is common for awakened processes to immediately
	 * re-queue themselves.  If we just naively try to reduce the wakeup list
	 * to empty, we'll get into a potentially-indefinite loop against such a
	 * process.  The semantics we really want are just to be sure that we have
	 * wakened all processes that were in the list at entry.  We can use our
	 * own cvWaitLink as a sentinel to detect when we've finished.
	 *
	 * A seeming flaw in this approach is that someone else might signal the
	 * CV and in doing so remove our sentinel entry.  But that's fine: since
	 * CV waiters are always added and removed in order, that must mean that
	 * every previous waiter has been wakened, so we're done.  We'll get an
	 * extra "set" on our latch from the someone else's signal, which is
	 * slightly inefficient but harmless.
	 *
	 * We can't insert our cvWaitLink as a sentinel if it's already in use in
	 * some other proclist.  While that's not expected to be true for typical
	 * uses of this function, we can deal with it by simply canceling any
	 * prepared CV sleep.  The next call to ConditionVariableSleep will take
	 * care of re-establishing the lost state.
	 */
	if (cv_sleep_target != NULL)
		ConditionVariableCancelSleep();

	/*
	 * Inspect the state of the queue.  If it's empty, we have nothing to do.
	 * If there's exactly one entry, we need only remove and signal that
	 * entry.  Otherwise, remove the first entry and insert our sentinel.
	 */
	SpinLockAcquire(&cv->mutex);
	/* While we're here, let's assert we're not in the list. */
	Assert(!proclist_contains(&cv->wakeup, pgprocno, cvWaitLink));

	if (!proclist_is_empty(&cv->wakeup))
	{
		proc = proclist_pop_head_node(&cv->wakeup, cvWaitLink);
		if (!proclist_is_empty(&cv->wakeup))
		{
			proclist_push_tail(&cv->wakeup, pgprocno, cvWaitLink);
			have_sentinel = true;
		}
	}
	SpinLockRelease(&cv->mutex);

	/* Awaken first waiter, if there was one. */
	if (proc != NULL)
		SetLatch(&proc->procLatch);

	while (have_sentinel)
	{
		/*
		 * Each time through the loop, remove the first wakeup list entry, and
		 * signal it unless it's our sentinel.  Repeat as long as the sentinel
		 * remains in the list.
		 *
		 * Notice that if someone else removes our sentinel, we will waken one
		 * additional process before exiting.  That's intentional, because if
		 * someone else signals the CV, they may be intending to waken some
		 * third process that added itself to the list after we added the
		 * sentinel.  Better to give a spurious wakeup (which should be
		 * harmless beyond wasting some cycles) than to lose a wakeup.
		 */
		proc = NULL;
		SpinLockAcquire(&cv->mutex);
		if (!proclist_is_empty(&cv->wakeup))
			proc = proclist_pop_head_node(&cv->wakeup, cvWaitLink);
		have_sentinel = proclist_contains(&cv->wakeup, pgprocno, cvWaitLink);
		SpinLockRelease(&cv->mutex);

		if (proc != NULL && proc != MyProc)
			SetLatch(&proc->procLatch);
	}
}
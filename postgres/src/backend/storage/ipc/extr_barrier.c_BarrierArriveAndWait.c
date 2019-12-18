#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_3__ {int phase; scalar_t__ arrived; scalar_t__ participants; int elected; int /*<<< orphan*/  condition_variable; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ Barrier ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ConditionVariableBroadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 int /*<<< orphan*/  ConditionVariablePrepareToSleep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConditionVariableSleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 

bool
BarrierArriveAndWait(Barrier *barrier, uint32 wait_event_info)
{
	bool		release = false;
	bool		elected;
	int			start_phase;
	int			next_phase;

	SpinLockAcquire(&barrier->mutex);
	start_phase = barrier->phase;
	next_phase = start_phase + 1;
	++barrier->arrived;
	if (barrier->arrived == barrier->participants)
	{
		release = true;
		barrier->arrived = 0;
		barrier->phase = next_phase;
		barrier->elected = next_phase;
	}
	SpinLockRelease(&barrier->mutex);

	/*
	 * If we were the last expected participant to arrive, we can release our
	 * peers and return true to indicate that this backend has been elected to
	 * perform any serial work.
	 */
	if (release)
	{
		ConditionVariableBroadcast(&barrier->condition_variable);

		return true;
	}

	/*
	 * Otherwise we have to wait for the last participant to arrive and
	 * advance the phase.
	 */
	elected = false;
	ConditionVariablePrepareToSleep(&barrier->condition_variable);
	for (;;)
	{
		/*
		 * We know that phase must either be start_phase, indicating that we
		 * need to keep waiting, or next_phase, indicating that the last
		 * participant that we were waiting for has either arrived or detached
		 * so that the next phase has begun.  The phase cannot advance any
		 * further than that without this backend's participation, because
		 * this backend is attached.
		 */
		SpinLockAcquire(&barrier->mutex);
		Assert(barrier->phase == start_phase || barrier->phase == next_phase);
		release = barrier->phase == next_phase;
		if (release && barrier->elected != next_phase)
		{
			/*
			 * Usually the backend that arrives last and releases the other
			 * backends is elected to return true (see above), so that it can
			 * begin processing serial work while it has a CPU timeslice.
			 * However, if the barrier advanced because someone detached, then
			 * one of the backends that is awoken will need to be elected.
			 */
			barrier->elected = barrier->phase;
			elected = true;
		}
		SpinLockRelease(&barrier->mutex);
		if (release)
			break;
		ConditionVariableSleep(&barrier->condition_variable, wait_event_info);
	}
	ConditionVariableCancelSleep();

	return elected;
}
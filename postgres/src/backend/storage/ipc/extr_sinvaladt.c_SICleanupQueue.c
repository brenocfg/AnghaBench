#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_5__ {int nextMsgNum; scalar_t__ procPid; int resetState; int signaled; scalar_t__ sendOnly; } ;
struct TYPE_4__ {int maxMsgNum; int lastBackend; int minMsgNum; int nextThreshold; TYPE_2__* procState; } ;
typedef  TYPE_1__ SISeg ;
typedef  TYPE_2__ ProcState ;
typedef  int BackendId ;

/* Variables and functions */
 int CLEANUP_MIN ; 
 int CLEANUP_QUANTUM ; 
 int /*<<< orphan*/  DEBUG4 ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MAXNUMMESSAGES ; 
 int MSGNUMWRAPAROUND ; 
 int /*<<< orphan*/  PROCSIG_CATCHUP_INTERRUPT ; 
 int SIG_THRESHOLD ; 
 int /*<<< orphan*/  SInvalReadLock ; 
 int /*<<< orphan*/  SInvalWriteLock ; 
 int /*<<< orphan*/  SendProcSignal (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* shmInvalBuffer ; 

void
SICleanupQueue(bool callerHasWriteLock, int minFree)
{
	SISeg	   *segP = shmInvalBuffer;
	int			min,
				minsig,
				lowbound,
				numMsgs,
				i;
	ProcState  *needSig = NULL;

	/* Lock out all writers and readers */
	if (!callerHasWriteLock)
		LWLockAcquire(SInvalWriteLock, LW_EXCLUSIVE);
	LWLockAcquire(SInvalReadLock, LW_EXCLUSIVE);

	/*
	 * Recompute minMsgNum = minimum of all backends' nextMsgNum, identify the
	 * furthest-back backend that needs signaling (if any), and reset any
	 * backends that are too far back.  Note that because we ignore sendOnly
	 * backends here it is possible for them to keep sending messages without
	 * a problem even when they are the only active backend.
	 */
	min = segP->maxMsgNum;
	minsig = min - SIG_THRESHOLD;
	lowbound = min - MAXNUMMESSAGES + minFree;

	for (i = 0; i < segP->lastBackend; i++)
	{
		ProcState  *stateP = &segP->procState[i];
		int			n = stateP->nextMsgNum;

		/* Ignore if inactive or already in reset state */
		if (stateP->procPid == 0 || stateP->resetState || stateP->sendOnly)
			continue;

		/*
		 * If we must free some space and this backend is preventing it, force
		 * him into reset state and then ignore until he catches up.
		 */
		if (n < lowbound)
		{
			stateP->resetState = true;
			/* no point in signaling him ... */
			continue;
		}

		/* Track the global minimum nextMsgNum */
		if (n < min)
			min = n;

		/* Also see who's furthest back of the unsignaled backends */
		if (n < minsig && !stateP->signaled)
		{
			minsig = n;
			needSig = stateP;
		}
	}
	segP->minMsgNum = min;

	/*
	 * When minMsgNum gets really large, decrement all message counters so as
	 * to forestall overflow of the counters.  This happens seldom enough that
	 * folding it into the previous loop would be a loser.
	 */
	if (min >= MSGNUMWRAPAROUND)
	{
		segP->minMsgNum -= MSGNUMWRAPAROUND;
		segP->maxMsgNum -= MSGNUMWRAPAROUND;
		for (i = 0; i < segP->lastBackend; i++)
		{
			/* we don't bother skipping inactive entries here */
			segP->procState[i].nextMsgNum -= MSGNUMWRAPAROUND;
		}
	}

	/*
	 * Determine how many messages are still in the queue, and set the
	 * threshold at which we should repeat SICleanupQueue().
	 */
	numMsgs = segP->maxMsgNum - segP->minMsgNum;
	if (numMsgs < CLEANUP_MIN)
		segP->nextThreshold = CLEANUP_MIN;
	else
		segP->nextThreshold = (numMsgs / CLEANUP_QUANTUM + 1) * CLEANUP_QUANTUM;

	/*
	 * Lastly, signal anyone who needs a catchup interrupt.  Since
	 * SendProcSignal() might not be fast, we don't want to hold locks while
	 * executing it.
	 */
	if (needSig)
	{
		pid_t		his_pid = needSig->procPid;
		BackendId	his_backendId = (needSig - &segP->procState[0]) + 1;

		needSig->signaled = true;
		LWLockRelease(SInvalReadLock);
		LWLockRelease(SInvalWriteLock);
		elog(DEBUG4, "sending sinval catchup signal to PID %d", (int) his_pid);
		SendProcSignal(his_pid, PROCSIG_CATCHUP_INTERRUPT, his_backendId);
		if (callerHasWriteLock)
			LWLockAcquire(SInvalWriteLock, LW_EXCLUSIVE);
	}
	else
	{
		LWLockRelease(SInvalReadLock);
		if (!callerHasWriteLock)
			LWLockRelease(SInvalWriteLock);
	}
}
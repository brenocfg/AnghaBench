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
struct TYPE_5__ {int hasMessages; } ;
struct TYPE_4__ {int maxMsgNum; int minMsgNum; int nextThreshold; int lastBackend; TYPE_2__* procState; int /*<<< orphan*/  msgnumLock; int /*<<< orphan*/ * buffer; } ;
typedef  int /*<<< orphan*/  SharedInvalidationMessage ;
typedef  TYPE_1__ SISeg ;
typedef  TYPE_2__ ProcState ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MAXNUMMESSAGES ; 
 int Min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SICleanupQueue (int,int) ; 
 int /*<<< orphan*/  SInvalWriteLock ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WRITE_QUANTUM ; 
 TYPE_1__* shmInvalBuffer ; 

void
SIInsertDataEntries(const SharedInvalidationMessage *data, int n)
{
	SISeg	   *segP = shmInvalBuffer;

	/*
	 * N can be arbitrarily large.  We divide the work into groups of no more
	 * than WRITE_QUANTUM messages, to be sure that we don't hold the lock for
	 * an unreasonably long time.  (This is not so much because we care about
	 * letting in other writers, as that some just-caught-up backend might be
	 * trying to do SICleanupQueue to pass on its signal, and we don't want it
	 * to have to wait a long time.)  Also, we need to consider calling
	 * SICleanupQueue every so often.
	 */
	while (n > 0)
	{
		int			nthistime = Min(n, WRITE_QUANTUM);
		int			numMsgs;
		int			max;
		int			i;

		n -= nthistime;

		LWLockAcquire(SInvalWriteLock, LW_EXCLUSIVE);

		/*
		 * If the buffer is full, we *must* acquire some space.  Clean the
		 * queue and reset anyone who is preventing space from being freed.
		 * Otherwise, clean the queue only when it's exceeded the next
		 * fullness threshold.  We have to loop and recheck the buffer state
		 * after any call of SICleanupQueue.
		 */
		for (;;)
		{
			numMsgs = segP->maxMsgNum - segP->minMsgNum;
			if (numMsgs + nthistime > MAXNUMMESSAGES ||
				numMsgs >= segP->nextThreshold)
				SICleanupQueue(true, nthistime);
			else
				break;
		}

		/*
		 * Insert new message(s) into proper slot of circular buffer
		 */
		max = segP->maxMsgNum;
		while (nthistime-- > 0)
		{
			segP->buffer[max % MAXNUMMESSAGES] = *data++;
			max++;
		}

		/* Update current value of maxMsgNum using spinlock */
		SpinLockAcquire(&segP->msgnumLock);
		segP->maxMsgNum = max;
		SpinLockRelease(&segP->msgnumLock);

		/*
		 * Now that the maxMsgNum change is globally visible, we give everyone
		 * a swift kick to make sure they read the newly added messages.
		 * Releasing SInvalWriteLock will enforce a full memory barrier, so
		 * these (unlocked) changes will be committed to memory before we exit
		 * the function.
		 */
		for (i = 0; i < segP->lastBackend; i++)
		{
			ProcState  *stateP = &segP->procState[i];

			stateP->hasMessages = true;
		}

		LWLockRelease(SInvalWriteLock);
	}
}
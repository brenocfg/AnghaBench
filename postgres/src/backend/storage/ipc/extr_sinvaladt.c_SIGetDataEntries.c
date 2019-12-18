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
struct TYPE_5__ {int hasMessages; int resetState; int nextMsgNum; int signaled; } ;
struct TYPE_4__ {int maxMsgNum; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  msgnumLock; TYPE_2__* procState; } ;
typedef  int /*<<< orphan*/  SharedInvalidationMessage ;
typedef  TYPE_1__ SISeg ;
typedef  TYPE_2__ ProcState ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 size_t MAXNUMMESSAGES ; 
 int MyBackendId ; 
 int /*<<< orphan*/  SInvalReadLock ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_1__* shmInvalBuffer ; 

int
SIGetDataEntries(SharedInvalidationMessage *data, int datasize)
{
	SISeg	   *segP;
	ProcState  *stateP;
	int			max;
	int			n;

	segP = shmInvalBuffer;
	stateP = &segP->procState[MyBackendId - 1];

	/*
	 * Before starting to take locks, do a quick, unlocked test to see whether
	 * there can possibly be anything to read.  On a multiprocessor system,
	 * it's possible that this load could migrate backwards and occur before
	 * we actually enter this function, so we might miss a sinval message that
	 * was just added by some other processor.  But they can't migrate
	 * backwards over a preceding lock acquisition, so it should be OK.  If we
	 * haven't acquired a lock preventing against further relevant
	 * invalidations, any such occurrence is not much different than if the
	 * invalidation had arrived slightly later in the first place.
	 */
	if (!stateP->hasMessages)
		return 0;

	LWLockAcquire(SInvalReadLock, LW_SHARED);

	/*
	 * We must reset hasMessages before determining how many messages we're
	 * going to read.  That way, if new messages arrive after we have
	 * determined how many we're reading, the flag will get reset and we'll
	 * notice those messages part-way through.
	 *
	 * Note that, if we don't end up reading all of the messages, we had
	 * better be certain to reset this flag before exiting!
	 */
	stateP->hasMessages = false;

	/* Fetch current value of maxMsgNum using spinlock */
	SpinLockAcquire(&segP->msgnumLock);
	max = segP->maxMsgNum;
	SpinLockRelease(&segP->msgnumLock);

	if (stateP->resetState)
	{
		/*
		 * Force reset.  We can say we have dealt with any messages added
		 * since the reset, as well; and that means we should clear the
		 * signaled flag, too.
		 */
		stateP->nextMsgNum = max;
		stateP->resetState = false;
		stateP->signaled = false;
		LWLockRelease(SInvalReadLock);
		return -1;
	}

	/*
	 * Retrieve messages and advance backend's counter, until data array is
	 * full or there are no more messages.
	 *
	 * There may be other backends that haven't read the message(s), so we
	 * cannot delete them here.  SICleanupQueue() will eventually remove them
	 * from the queue.
	 */
	n = 0;
	while (n < datasize && stateP->nextMsgNum < max)
	{
		data[n++] = segP->buffer[stateP->nextMsgNum % MAXNUMMESSAGES];
		stateP->nextMsgNum++;
	}

	/*
	 * If we have caught up completely, reset our "signaled" flag so that
	 * we'll get another signal if we fall behind again.
	 *
	 * If we haven't caught up completely, reset the hasMessages flag so that
	 * we see the remaining messages next time.
	 */
	if (stateP->nextMsgNum >= max)
		stateP->signaled = false;
	else
		stateP->hasMessages = true;

	LWLockRelease(SInvalReadLock);
	return n;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int backendId; } ;
struct TYPE_7__ {scalar_t__ procPid; int resetState; int signaled; int hasMessages; int sendOnly; int /*<<< orphan*/  nextMsgNum; TYPE_5__* proc; int /*<<< orphan*/  nextLXID; } ;
struct TYPE_6__ {int lastBackend; int maxBackends; int /*<<< orphan*/  maxMsgNum; TYPE_2__* procState; } ;
typedef  TYPE_1__ SISeg ;
typedef  TYPE_2__ ProcState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CleanupInvalidationState ; 
 int /*<<< orphan*/  DEBUG4 ; 
 int /*<<< orphan*/  ERRCODE_TOO_MANY_CONNECTIONS ; 
 int /*<<< orphan*/  FATAL ; 
 int InvalidBackendId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MyBackendId ; 
 TYPE_5__* MyProc ; 
 scalar_t__ MyProcPid ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_1__*) ; 
 int /*<<< orphan*/  SInvalWriteLock ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  nextLocalTransactionId ; 
 int /*<<< orphan*/  on_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* shmInvalBuffer ; 

void
SharedInvalBackendInit(bool sendOnly)
{
	int			index;
	ProcState  *stateP = NULL;
	SISeg	   *segP = shmInvalBuffer;

	/*
	 * This can run in parallel with read operations, but not with write
	 * operations, since SIInsertDataEntries relies on lastBackend to set
	 * hasMessages appropriately.
	 */
	LWLockAcquire(SInvalWriteLock, LW_EXCLUSIVE);

	/* Look for a free entry in the procState array */
	for (index = 0; index < segP->lastBackend; index++)
	{
		if (segP->procState[index].procPid == 0)	/* inactive slot? */
		{
			stateP = &segP->procState[index];
			break;
		}
	}

	if (stateP == NULL)
	{
		if (segP->lastBackend < segP->maxBackends)
		{
			stateP = &segP->procState[segP->lastBackend];
			Assert(stateP->procPid == 0);
			segP->lastBackend++;
		}
		else
		{
			/*
			 * out of procState slots: MaxBackends exceeded -- report normally
			 */
			MyBackendId = InvalidBackendId;
			LWLockRelease(SInvalWriteLock);
			ereport(FATAL,
					(errcode(ERRCODE_TOO_MANY_CONNECTIONS),
					 errmsg("sorry, too many clients already")));
		}
	}

	MyBackendId = (stateP - &segP->procState[0]) + 1;

	/* Advertise assigned backend ID in MyProc */
	MyProc->backendId = MyBackendId;

	/* Fetch next local transaction ID into local memory */
	nextLocalTransactionId = stateP->nextLXID;

	/* mark myself active, with all extant messages already read */
	stateP->procPid = MyProcPid;
	stateP->proc = MyProc;
	stateP->nextMsgNum = segP->maxMsgNum;
	stateP->resetState = false;
	stateP->signaled = false;
	stateP->hasMessages = false;
	stateP->sendOnly = sendOnly;

	LWLockRelease(SInvalWriteLock);

	/* register exit routine to mark my entry inactive at exit */
	on_shmem_exit(CleanupInvalidationState, PointerGetDatum(segP));

	elog(DEBUG4, "my backend ID is %d", MyBackendId);
}
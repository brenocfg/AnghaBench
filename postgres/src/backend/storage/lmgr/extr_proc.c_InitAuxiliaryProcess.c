#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int delayChkpt; scalar_t__ vacuumFlags; void* xmin; void* xid; } ;
struct TYPE_7__ {TYPE_4__* allPgXact; int /*<<< orphan*/  spins_per_delay; } ;
struct TYPE_6__ {scalar_t__ pid; size_t pgprocno; int fpVXIDLock; int lwWaiting; int /*<<< orphan*/  sem; int /*<<< orphan*/  lockGroupMembers; int /*<<< orphan*/ * lockGroupLeader; int /*<<< orphan*/  procLatch; int /*<<< orphan*/ * myProcLocks; int /*<<< orphan*/ * waitProcLock; int /*<<< orphan*/ * waitLock; scalar_t__ lwWaitMode; int /*<<< orphan*/  isBackgroundWorker; void* tempNamespaceId; void* roleId; void* databaseId; int /*<<< orphan*/  backendId; void* fpLocalTransactionId; void* lxid; int /*<<< orphan*/  waitStatus; int /*<<< orphan*/  links; } ;
typedef  TYPE_1__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AuxiliaryProcKill ; 
 TYPE_1__* AuxiliaryProcs ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  InvalidBackendId ; 
 void* InvalidLocalTransactionId ; 
 void* InvalidOid ; 
 void* InvalidTransactionId ; 
 int /*<<< orphan*/  IsBackgroundWorker ; 
 TYPE_4__* MyPgXact ; 
 TYPE_1__* MyProc ; 
 scalar_t__ MyProcPid ; 
 int NUM_AUXILIARY_PROCS ; 
 int NUM_LOCK_PARTITIONS ; 
 int /*<<< orphan*/  OwnLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  PGSemaphoreReset (int /*<<< orphan*/ ) ; 
 TYPE_2__* ProcGlobal ; 
 int /*<<< orphan*/  ProcStructLock ; 
 int /*<<< orphan*/  SHMQueueElemInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHMQueueEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_OK ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SwitchToSharedLatch () ; 
 int /*<<< orphan*/  dlist_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  on_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_spins_per_delay (int /*<<< orphan*/ ) ; 

void
InitAuxiliaryProcess(void)
{
	PGPROC	   *auxproc;
	int			proctype;

	/*
	 * ProcGlobal should be set up already (if we are a backend, we inherit
	 * this by fork() or EXEC_BACKEND mechanism from the postmaster).
	 */
	if (ProcGlobal == NULL || AuxiliaryProcs == NULL)
		elog(PANIC, "proc header uninitialized");

	if (MyProc != NULL)
		elog(ERROR, "you already exist");

	/*
	 * We use the ProcStructLock to protect assignment and releasing of
	 * AuxiliaryProcs entries.
	 *
	 * While we are holding the ProcStructLock, also copy the current shared
	 * estimate of spins_per_delay to local storage.
	 */
	SpinLockAcquire(ProcStructLock);

	set_spins_per_delay(ProcGlobal->spins_per_delay);

	/*
	 * Find a free auxproc ... *big* trouble if there isn't one ...
	 */
	for (proctype = 0; proctype < NUM_AUXILIARY_PROCS; proctype++)
	{
		auxproc = &AuxiliaryProcs[proctype];
		if (auxproc->pid == 0)
			break;
	}
	if (proctype >= NUM_AUXILIARY_PROCS)
	{
		SpinLockRelease(ProcStructLock);
		elog(FATAL, "all AuxiliaryProcs are in use");
	}

	/* Mark auxiliary proc as in use by me */
	/* use volatile pointer to prevent code rearrangement */
	((volatile PGPROC *) auxproc)->pid = MyProcPid;

	MyProc = auxproc;
	MyPgXact = &ProcGlobal->allPgXact[auxproc->pgprocno];

	SpinLockRelease(ProcStructLock);

	/*
	 * Initialize all fields of MyProc, except for those previously
	 * initialized by InitProcGlobal.
	 */
	SHMQueueElemInit(&(MyProc->links));
	MyProc->waitStatus = STATUS_OK;
	MyProc->lxid = InvalidLocalTransactionId;
	MyProc->fpVXIDLock = false;
	MyProc->fpLocalTransactionId = InvalidLocalTransactionId;
	MyPgXact->xid = InvalidTransactionId;
	MyPgXact->xmin = InvalidTransactionId;
	MyProc->backendId = InvalidBackendId;
	MyProc->databaseId = InvalidOid;
	MyProc->roleId = InvalidOid;
	MyProc->tempNamespaceId = InvalidOid;
	MyProc->isBackgroundWorker = IsBackgroundWorker;
	MyPgXact->delayChkpt = false;
	MyPgXact->vacuumFlags = 0;
	MyProc->lwWaiting = false;
	MyProc->lwWaitMode = 0;
	MyProc->waitLock = NULL;
	MyProc->waitProcLock = NULL;
#ifdef USE_ASSERT_CHECKING
	{
		int			i;

		/* Last process should have released all locks. */
		for (i = 0; i < NUM_LOCK_PARTITIONS; i++)
			Assert(SHMQueueEmpty(&(MyProc->myProcLocks[i])));
	}
#endif

	/*
	 * Acquire ownership of the PGPROC's latch, so that we can use WaitLatch
	 * on it.  That allows us to repoint the process latch, which so far
	 * points to process local one, to the shared one.
	 */
	OwnLatch(&MyProc->procLatch);
	SwitchToSharedLatch();

	/* Check that group locking fields are in a proper initial state. */
	Assert(MyProc->lockGroupLeader == NULL);
	Assert(dlist_is_empty(&MyProc->lockGroupMembers));

	/*
	 * We might be reusing a semaphore that belonged to a failed process. So
	 * be careful and reinitialize its value here.  (This is not strictly
	 * necessary anymore, but seems like a good idea for cleanliness.)
	 */
	PGSemaphoreReset(MyProc->sem);

	/*
	 * Arrange to clean up at process exit.
	 */
	on_shmem_exit(AuxiliaryProcKill, Int32GetDatum(proctype));
}
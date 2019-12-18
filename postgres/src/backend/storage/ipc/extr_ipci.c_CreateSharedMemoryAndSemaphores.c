#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int Size ;
typedef  int /*<<< orphan*/  ShmemIndexEnt ;
typedef  int /*<<< orphan*/  PGShmemHeader ;

/* Variables and functions */
 int /*<<< orphan*/  ApplyLauncherShmemInit () ; 
 int ApplyLauncherShmemSize () ; 
 int /*<<< orphan*/  AsyncShmemInit () ; 
 int AsyncShmemSize () ; 
 int /*<<< orphan*/  AutoVacuumShmemInit () ; 
 int AutoVacuumShmemSize () ; 
 int /*<<< orphan*/  BTreeShmemInit () ; 
 int BTreeShmemSize () ; 
 int BackendStatusShmemSize () ; 
 int /*<<< orphan*/  BackgroundWorkerShmemInit () ; 
 int BackgroundWorkerShmemSize () ; 
 int BufferShmemSize () ; 
 int /*<<< orphan*/  CLOGShmemInit () ; 
 int CLOGShmemSize () ; 
 int /*<<< orphan*/  CheckpointerShmemInit () ; 
 int CheckpointerShmemSize () ; 
 int /*<<< orphan*/  CommitTsShmemInit () ; 
 int CommitTsShmemSize () ; 
 int /*<<< orphan*/  CreateLWLocks () ; 
 int /*<<< orphan*/  CreateSharedBackendStatus () ; 
 int /*<<< orphan*/  CreateSharedInvalidationState () ; 
 int /*<<< orphan*/  CreateSharedProcArray () ; 
 int /*<<< orphan*/  DEBUG3 ; 
 int /*<<< orphan*/  InitBufferPool () ; 
 int /*<<< orphan*/  InitLocks () ; 
 int /*<<< orphan*/  InitPredicateLocks () ; 
 int /*<<< orphan*/  InitProcGlobal () ; 
 int /*<<< orphan*/  InitShmemAccess (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitShmemAllocation () ; 
 int /*<<< orphan*/  InitShmemIndex () ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int LWLockShmemSize () ; 
 int LockShmemSize () ; 
 int /*<<< orphan*/  MultiXactShmemInit () ; 
 int MultiXactShmemSize () ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  PGReserveSemaphores (int) ; 
 int PGSemaphoreShmemSize (int) ; 
 int /*<<< orphan*/ * PGSharedMemoryCreate (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PMSignalShmemInit () ; 
 int PMSignalShmemSize () ; 
 int PredicateLockShmemSize () ; 
 int ProcArrayShmemSize () ; 
 int ProcGlobalSemas () ; 
 int ProcGlobalShmemSize () ; 
 int /*<<< orphan*/  ProcSignalShmemInit () ; 
 int ProcSignalShmemSize () ; 
 int /*<<< orphan*/  ReplicationOriginShmemInit () ; 
 int ReplicationOriginShmemSize () ; 
 int /*<<< orphan*/  ReplicationSlotsShmemInit () ; 
 int ReplicationSlotsShmemSize () ; 
 int /*<<< orphan*/  SHMEM_INDEX_SIZE ; 
 int SInvalShmemSize () ; 
 int /*<<< orphan*/  SUBTRANSShmemInit () ; 
 int SUBTRANSShmemSize () ; 
 int /*<<< orphan*/  ShmemBackendArrayAllocation () ; 
 int ShmemBackendArraySize () ; 
 int /*<<< orphan*/  SnapMgrInit () ; 
 int SnapMgrShmemSize () ; 
 int /*<<< orphan*/  SpinlockSemaInit () ; 
 int SpinlockSemaSize () ; 
 scalar_t__ SpinlockSemas () ; 
 int /*<<< orphan*/  SyncScanShmemInit () ; 
 int SyncScanShmemSize () ; 
 int /*<<< orphan*/  TwoPhaseShmemInit () ; 
 int TwoPhaseShmemSize () ; 
 int /*<<< orphan*/  WalRcvShmemInit () ; 
 int WalRcvShmemSize () ; 
 int /*<<< orphan*/  WalSndShmemInit () ; 
 int WalSndShmemSize () ; 
 int /*<<< orphan*/  XLOGShmemInit () ; 
 int XLOGShmemSize () ; 
 int add_size (int,int) ; 
 int addin_request_allowed ; 
 int /*<<< orphan*/  dsm_postmaster_startup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int hash_estimate_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shmem_startup_hook () ; 
 int total_addin_request ; 

void
CreateSharedMemoryAndSemaphores(void)
{
	PGShmemHeader *shim = NULL;

	if (!IsUnderPostmaster)
	{
		PGShmemHeader *seghdr;
		Size		size;
		int			numSemas;

		/* Compute number of semaphores we'll need */
		numSemas = ProcGlobalSemas();
		numSemas += SpinlockSemas();

		/*
		 * Size of the Postgres shared-memory block is estimated via
		 * moderately-accurate estimates for the big hogs, plus 100K for the
		 * stuff that's too small to bother with estimating.
		 *
		 * We take some care during this phase to ensure that the total size
		 * request doesn't overflow size_t.  If this gets through, we don't
		 * need to be so careful during the actual allocation phase.
		 */
		size = 100000;
		size = add_size(size, PGSemaphoreShmemSize(numSemas));
		size = add_size(size, SpinlockSemaSize());
		size = add_size(size, hash_estimate_size(SHMEM_INDEX_SIZE,
												 sizeof(ShmemIndexEnt)));
		size = add_size(size, BufferShmemSize());
		size = add_size(size, LockShmemSize());
		size = add_size(size, PredicateLockShmemSize());
		size = add_size(size, ProcGlobalShmemSize());
		size = add_size(size, XLOGShmemSize());
		size = add_size(size, CLOGShmemSize());
		size = add_size(size, CommitTsShmemSize());
		size = add_size(size, SUBTRANSShmemSize());
		size = add_size(size, TwoPhaseShmemSize());
		size = add_size(size, BackgroundWorkerShmemSize());
		size = add_size(size, MultiXactShmemSize());
		size = add_size(size, LWLockShmemSize());
		size = add_size(size, ProcArrayShmemSize());
		size = add_size(size, BackendStatusShmemSize());
		size = add_size(size, SInvalShmemSize());
		size = add_size(size, PMSignalShmemSize());
		size = add_size(size, ProcSignalShmemSize());
		size = add_size(size, CheckpointerShmemSize());
		size = add_size(size, AutoVacuumShmemSize());
		size = add_size(size, ReplicationSlotsShmemSize());
		size = add_size(size, ReplicationOriginShmemSize());
		size = add_size(size, WalSndShmemSize());
		size = add_size(size, WalRcvShmemSize());
		size = add_size(size, ApplyLauncherShmemSize());
		size = add_size(size, SnapMgrShmemSize());
		size = add_size(size, BTreeShmemSize());
		size = add_size(size, SyncScanShmemSize());
		size = add_size(size, AsyncShmemSize());
#ifdef EXEC_BACKEND
		size = add_size(size, ShmemBackendArraySize());
#endif

		/* freeze the addin request size and include it */
		addin_request_allowed = false;
		size = add_size(size, total_addin_request);

		/* might as well round it off to a multiple of a typical page size */
		size = add_size(size, 8192 - (size % 8192));

		elog(DEBUG3, "invoking IpcMemoryCreate(size=%zu)", size);

		/*
		 * Create the shmem segment
		 */
		seghdr = PGSharedMemoryCreate(size, &shim);

		InitShmemAccess(seghdr);

		/*
		 * Create semaphores
		 */
		PGReserveSemaphores(numSemas);

		/*
		 * If spinlocks are disabled, initialize emulation layer (which
		 * depends on semaphores, so the order is important here).
		 */
#ifndef HAVE_SPINLOCKS
		SpinlockSemaInit();
#endif
	}
	else
	{
		/*
		 * We are reattaching to an existing shared memory segment. This
		 * should only be reached in the EXEC_BACKEND case.
		 */
#ifndef EXEC_BACKEND
		elog(PANIC, "should be attached to shared memory already");
#endif
	}

	/*
	 * Set up shared memory allocation mechanism
	 */
	if (!IsUnderPostmaster)
		InitShmemAllocation();

	/*
	 * Now initialize LWLocks, which do shared memory allocation and are
	 * needed for InitShmemIndex.
	 */
	CreateLWLocks();

	/*
	 * Set up shmem.c index hashtable
	 */
	InitShmemIndex();

	/*
	 * Set up xlog, clog, and buffers
	 */
	XLOGShmemInit();
	CLOGShmemInit();
	CommitTsShmemInit();
	SUBTRANSShmemInit();
	MultiXactShmemInit();
	InitBufferPool();

	/*
	 * Set up lock manager
	 */
	InitLocks();

	/*
	 * Set up predicate lock manager
	 */
	InitPredicateLocks();

	/*
	 * Set up process table
	 */
	if (!IsUnderPostmaster)
		InitProcGlobal();
	CreateSharedProcArray();
	CreateSharedBackendStatus();
	TwoPhaseShmemInit();
	BackgroundWorkerShmemInit();

	/*
	 * Set up shared-inval messaging
	 */
	CreateSharedInvalidationState();

	/*
	 * Set up interprocess signaling mechanisms
	 */
	PMSignalShmemInit();
	ProcSignalShmemInit();
	CheckpointerShmemInit();
	AutoVacuumShmemInit();
	ReplicationSlotsShmemInit();
	ReplicationOriginShmemInit();
	WalSndShmemInit();
	WalRcvShmemInit();
	ApplyLauncherShmemInit();

	/*
	 * Set up other modules that need some shared memory space
	 */
	SnapMgrInit();
	BTreeShmemInit();
	SyncScanShmemInit();
	AsyncShmemInit();

#ifdef EXEC_BACKEND

	/*
	 * Alloc the win32 shared backend array
	 */
	if (!IsUnderPostmaster)
		ShmemBackendArrayAllocation();
#endif

	/* Initialize dynamic shared memory facilities. */
	if (!IsUnderPostmaster)
		dsm_postmaster_startup(shim);

	/*
	 * Now give loadable modules a chance to set up their shmem allocations
	 */
	if (shmem_startup_hook)
		shmem_startup_hook();
}
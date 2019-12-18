#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  slock_t ;
struct TYPE_9__ {int /*<<< orphan*/ * next; } ;
struct TYPE_11__ {int pgprocno; int /*<<< orphan*/  clogGroupNext; int /*<<< orphan*/  procArrayGroupNext; int /*<<< orphan*/  lockGroupMembers; int /*<<< orphan*/ * myProcLocks; struct TYPE_11__** procgloballist; TYPE_1__ links; int /*<<< orphan*/  backendLock; int /*<<< orphan*/  procLatch; int /*<<< orphan*/  sem; } ;
struct TYPE_10__ {int startupBufferPinWaitBufId; int allProcCount; TYPE_3__* walsenderFreeProcs; TYPE_3__* bgworkerFreeProcs; TYPE_3__* autovacFreeProcs; TYPE_3__* freeProcs; TYPE_3__* allPgXact; TYPE_3__* allProcs; int /*<<< orphan*/  clogGroupFirst; int /*<<< orphan*/  procArrayGroupFirst; int /*<<< orphan*/ * checkpointerLatch; int /*<<< orphan*/ * walwriterLatch; scalar_t__ startupProcPid; int /*<<< orphan*/ * startupProc; int /*<<< orphan*/  spins_per_delay; } ;
typedef  int /*<<< orphan*/  SHM_QUEUE ;
typedef  TYPE_2__ PROC_HDR ;
typedef  TYPE_3__ PGXACT ;
typedef  TYPE_3__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_3__* AuxiliaryProcs ; 
 int /*<<< orphan*/  DEFAULT_SPINS_PER_DELAY ; 
 int /*<<< orphan*/  INVALID_PGPROCNO ; 
 int /*<<< orphan*/  InitSharedLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWLockInitialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWTRANCHE_PROC ; 
 int MaxBackends ; 
 int MaxConnections ; 
 int /*<<< orphan*/  MemSet (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int NUM_AUXILIARY_PROCS ; 
 int NUM_LOCK_PARTITIONS ; 
 int /*<<< orphan*/  PGSemaphoreCreate () ; 
 TYPE_3__* PreparedXactProcs ; 
 TYPE_2__* ProcGlobal ; 
 int /*<<< orphan*/ * ProcStructLock ; 
 int /*<<< orphan*/  SHMQueueInit (int /*<<< orphan*/ *) ; 
 scalar_t__ ShmemAlloc (int) ; 
 scalar_t__ ShmemInitStruct (char*,int,int*) ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 int autovacuum_max_workers ; 
 int /*<<< orphan*/  dlist_init (int /*<<< orphan*/ *) ; 
 int max_prepared_xacts ; 
 int max_worker_processes ; 
 int /*<<< orphan*/  pg_atomic_init_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
InitProcGlobal(void)
{
	PGPROC	   *procs;
	PGXACT	   *pgxacts;
	int			i,
				j;
	bool		found;
	uint32		TotalProcs = MaxBackends + NUM_AUXILIARY_PROCS + max_prepared_xacts;

	/* Create the ProcGlobal shared structure */
	ProcGlobal = (PROC_HDR *)
		ShmemInitStruct("Proc Header", sizeof(PROC_HDR), &found);
	Assert(!found);

	/*
	 * Initialize the data structures.
	 */
	ProcGlobal->spins_per_delay = DEFAULT_SPINS_PER_DELAY;
	ProcGlobal->freeProcs = NULL;
	ProcGlobal->autovacFreeProcs = NULL;
	ProcGlobal->bgworkerFreeProcs = NULL;
	ProcGlobal->walsenderFreeProcs = NULL;
	ProcGlobal->startupProc = NULL;
	ProcGlobal->startupProcPid = 0;
	ProcGlobal->startupBufferPinWaitBufId = -1;
	ProcGlobal->walwriterLatch = NULL;
	ProcGlobal->checkpointerLatch = NULL;
	pg_atomic_init_u32(&ProcGlobal->procArrayGroupFirst, INVALID_PGPROCNO);
	pg_atomic_init_u32(&ProcGlobal->clogGroupFirst, INVALID_PGPROCNO);

	/*
	 * Create and initialize all the PGPROC structures we'll need.  There are
	 * five separate consumers: (1) normal backends, (2) autovacuum workers
	 * and the autovacuum launcher, (3) background workers, (4) auxiliary
	 * processes, and (5) prepared transactions.  Each PGPROC structure is
	 * dedicated to exactly one of these purposes, and they do not move
	 * between groups.
	 */
	procs = (PGPROC *) ShmemAlloc(TotalProcs * sizeof(PGPROC));
	MemSet(procs, 0, TotalProcs * sizeof(PGPROC));
	ProcGlobal->allProcs = procs;
	/* XXX allProcCount isn't really all of them; it excludes prepared xacts */
	ProcGlobal->allProcCount = MaxBackends + NUM_AUXILIARY_PROCS;

	/*
	 * Also allocate a separate array of PGXACT structures.  This is separate
	 * from the main PGPROC array so that the most heavily accessed data is
	 * stored contiguously in memory in as few cache lines as possible. This
	 * provides significant performance benefits, especially on a
	 * multiprocessor system.  There is one PGXACT structure for every PGPROC
	 * structure.
	 */
	pgxacts = (PGXACT *) ShmemAlloc(TotalProcs * sizeof(PGXACT));
	MemSet(pgxacts, 0, TotalProcs * sizeof(PGXACT));
	ProcGlobal->allPgXact = pgxacts;

	for (i = 0; i < TotalProcs; i++)
	{
		/* Common initialization for all PGPROCs, regardless of type. */

		/*
		 * Set up per-PGPROC semaphore, latch, and backendLock. Prepared xact
		 * dummy PGPROCs don't need these though - they're never associated
		 * with a real process
		 */
		if (i < MaxBackends + NUM_AUXILIARY_PROCS)
		{
			procs[i].sem = PGSemaphoreCreate();
			InitSharedLatch(&(procs[i].procLatch));
			LWLockInitialize(&(procs[i].backendLock), LWTRANCHE_PROC);
		}
		procs[i].pgprocno = i;

		/*
		 * Newly created PGPROCs for normal backends, autovacuum and bgworkers
		 * must be queued up on the appropriate free list.  Because there can
		 * only ever be a small, fixed number of auxiliary processes, no free
		 * list is used in that case; InitAuxiliaryProcess() instead uses a
		 * linear search.   PGPROCs for prepared transactions are added to a
		 * free list by TwoPhaseShmemInit().
		 */
		if (i < MaxConnections)
		{
			/* PGPROC for normal backend, add to freeProcs list */
			procs[i].links.next = (SHM_QUEUE *) ProcGlobal->freeProcs;
			ProcGlobal->freeProcs = &procs[i];
			procs[i].procgloballist = &ProcGlobal->freeProcs;
		}
		else if (i < MaxConnections + autovacuum_max_workers + 1)
		{
			/* PGPROC for AV launcher/worker, add to autovacFreeProcs list */
			procs[i].links.next = (SHM_QUEUE *) ProcGlobal->autovacFreeProcs;
			ProcGlobal->autovacFreeProcs = &procs[i];
			procs[i].procgloballist = &ProcGlobal->autovacFreeProcs;
		}
		else if (i < MaxConnections + autovacuum_max_workers + 1 + max_worker_processes)
		{
			/* PGPROC for bgworker, add to bgworkerFreeProcs list */
			procs[i].links.next = (SHM_QUEUE *) ProcGlobal->bgworkerFreeProcs;
			ProcGlobal->bgworkerFreeProcs = &procs[i];
			procs[i].procgloballist = &ProcGlobal->bgworkerFreeProcs;
		}
		else if (i < MaxBackends)
		{
			/* PGPROC for walsender, add to walsenderFreeProcs list */
			procs[i].links.next = (SHM_QUEUE *) ProcGlobal->walsenderFreeProcs;
			ProcGlobal->walsenderFreeProcs = &procs[i];
			procs[i].procgloballist = &ProcGlobal->walsenderFreeProcs;
		}

		/* Initialize myProcLocks[] shared memory queues. */
		for (j = 0; j < NUM_LOCK_PARTITIONS; j++)
			SHMQueueInit(&(procs[i].myProcLocks[j]));

		/* Initialize lockGroupMembers list. */
		dlist_init(&procs[i].lockGroupMembers);

		/*
		 * Initialize the atomic variables, otherwise, it won't be safe to
		 * access them for backends that aren't currently in use.
		 */
		pg_atomic_init_u32(&(procs[i].procArrayGroupNext), INVALID_PGPROCNO);
		pg_atomic_init_u32(&(procs[i].clogGroupNext), INVALID_PGPROCNO);
	}

	/*
	 * Save pointers to the blocks of PGPROC structures reserved for auxiliary
	 * processes and prepared transactions.
	 */
	AuxiliaryProcs = &procs[MaxBackends];
	PreparedXactProcs = &procs[MaxBackends + NUM_AUXILIARY_PROCS];

	/* Create ProcStructLock spinlock, too */
	ProcStructLock = (slock_t *) ShmemAlloc(sizeof(slock_t));
	SpinLockInit(ProcStructLock);
}
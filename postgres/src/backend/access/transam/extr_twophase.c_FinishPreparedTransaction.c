#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int gidlen; int nsubxacts; int ncommitrels; int nabortrels; int ninvalmsgs; scalar_t__ initfileinval; int /*<<< orphan*/  xid; } ;
typedef  TYPE_1__ TwoPhaseFileHeader ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_10__ {TYPE_2__* allPgXact; int /*<<< orphan*/ * allProcs; } ;
struct TYPE_9__ {size_t pgprocno; int valid; scalar_t__ ondisk; int /*<<< orphan*/  prepare_start_lsn; } ;
struct TYPE_8__ {int /*<<< orphan*/  xid; } ;
typedef  int /*<<< orphan*/  SharedInvalidationMessage ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  TYPE_2__ PGXACT ;
typedef  int /*<<< orphan*/  PGPROC ;
typedef  TYPE_3__* GlobalTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AtEOXact_PgStat (int,int) ; 
 int /*<<< orphan*/  DropRelationFiles (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HOLD_INTERRUPTS () ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_3__* LockGXact (char const*,int /*<<< orphan*/ ) ; 
 int MAXALIGN (int) ; 
 int /*<<< orphan*/ * MyLockedGxact ; 
 int /*<<< orphan*/  PredicateLockTwoPhaseFinish (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ProcArrayRemove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* ProcGlobal ; 
 int /*<<< orphan*/  ProcessRecords (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESUME_INTERRUPTS () ; 
 char* ReadTwoPhaseFile (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RecordTransactionAbortPrepared (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  RecordTransactionCommitPrepared (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,char const*) ; 
 int /*<<< orphan*/  RelationCacheInitFilePostInvalidate () ; 
 int /*<<< orphan*/  RelationCacheInitFilePreInvalidate () ; 
 int /*<<< orphan*/  RemoveGXact (TYPE_3__*) ; 
 int /*<<< orphan*/  RemoveTwoPhaseFile (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SendSharedInvalidMessages (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdLatest (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 
 int /*<<< orphan*/  XlogReadTwoPhaseData (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  twophase_postabort_callbacks ; 
 int /*<<< orphan*/  twophase_postcommit_callbacks ; 

void
FinishPreparedTransaction(const char *gid, bool isCommit)
{
	GlobalTransaction gxact;
	PGPROC	   *proc;
	PGXACT	   *pgxact;
	TransactionId xid;
	char	   *buf;
	char	   *bufptr;
	TwoPhaseFileHeader *hdr;
	TransactionId latestXid;
	TransactionId *children;
	RelFileNode *commitrels;
	RelFileNode *abortrels;
	RelFileNode *delrels;
	int			ndelrels;
	SharedInvalidationMessage *invalmsgs;

	/*
	 * Validate the GID, and lock the GXACT to ensure that two backends do not
	 * try to commit the same GID at once.
	 */
	gxact = LockGXact(gid, GetUserId());
	proc = &ProcGlobal->allProcs[gxact->pgprocno];
	pgxact = &ProcGlobal->allPgXact[gxact->pgprocno];
	xid = pgxact->xid;

	/*
	 * Read and validate 2PC state data. State data will typically be stored
	 * in WAL files if the LSN is after the last checkpoint record, or moved
	 * to disk if for some reason they have lived for a long time.
	 */
	if (gxact->ondisk)
		buf = ReadTwoPhaseFile(xid, false);
	else
		XlogReadTwoPhaseData(gxact->prepare_start_lsn, &buf, NULL);


	/*
	 * Disassemble the header area
	 */
	hdr = (TwoPhaseFileHeader *) buf;
	Assert(TransactionIdEquals(hdr->xid, xid));
	bufptr = buf + MAXALIGN(sizeof(TwoPhaseFileHeader));
	bufptr += MAXALIGN(hdr->gidlen);
	children = (TransactionId *) bufptr;
	bufptr += MAXALIGN(hdr->nsubxacts * sizeof(TransactionId));
	commitrels = (RelFileNode *) bufptr;
	bufptr += MAXALIGN(hdr->ncommitrels * sizeof(RelFileNode));
	abortrels = (RelFileNode *) bufptr;
	bufptr += MAXALIGN(hdr->nabortrels * sizeof(RelFileNode));
	invalmsgs = (SharedInvalidationMessage *) bufptr;
	bufptr += MAXALIGN(hdr->ninvalmsgs * sizeof(SharedInvalidationMessage));

	/* compute latestXid among all children */
	latestXid = TransactionIdLatest(xid, hdr->nsubxacts, children);

	/* Prevent cancel/die interrupt while cleaning up */
	HOLD_INTERRUPTS();

	/*
	 * The order of operations here is critical: make the XLOG entry for
	 * commit or abort, then mark the transaction committed or aborted in
	 * pg_xact, then remove its PGPROC from the global ProcArray (which means
	 * TransactionIdIsInProgress will stop saying the prepared xact is in
	 * progress), then run the post-commit or post-abort callbacks. The
	 * callbacks will release the locks the transaction held.
	 */
	if (isCommit)
		RecordTransactionCommitPrepared(xid,
										hdr->nsubxacts, children,
										hdr->ncommitrels, commitrels,
										hdr->ninvalmsgs, invalmsgs,
										hdr->initfileinval, gid);
	else
		RecordTransactionAbortPrepared(xid,
									   hdr->nsubxacts, children,
									   hdr->nabortrels, abortrels,
									   gid);

	ProcArrayRemove(proc, latestXid);

	/*
	 * In case we fail while running the callbacks, mark the gxact invalid so
	 * no one else will try to commit/rollback, and so it will be recycled if
	 * we fail after this point.  It is still locked by our backend so it
	 * won't go away yet.
	 *
	 * (We assume it's safe to do this without taking TwoPhaseStateLock.)
	 */
	gxact->valid = false;

	/*
	 * We have to remove any files that were supposed to be dropped. For
	 * consistency with the regular xact.c code paths, must do this before
	 * releasing locks, so do it before running the callbacks.
	 *
	 * NB: this code knows that we couldn't be dropping any temp rels ...
	 */
	if (isCommit)
	{
		delrels = commitrels;
		ndelrels = hdr->ncommitrels;
	}
	else
	{
		delrels = abortrels;
		ndelrels = hdr->nabortrels;
	}

	/* Make sure files supposed to be dropped are dropped */
	DropRelationFiles(delrels, ndelrels, false);

	/*
	 * Handle cache invalidation messages.
	 *
	 * Relcache init file invalidation requires processing both before and
	 * after we send the SI messages. See AtEOXact_Inval()
	 */
	if (hdr->initfileinval)
		RelationCacheInitFilePreInvalidate();
	SendSharedInvalidMessages(invalmsgs, hdr->ninvalmsgs);
	if (hdr->initfileinval)
		RelationCacheInitFilePostInvalidate();

	/*
	 * Acquire the two-phase lock.  We want to work on the two-phase callbacks
	 * while holding it to avoid potential conflicts with other transactions
	 * attempting to use the same GID, so the lock is released once the shared
	 * memory state is cleared.
	 */
	LWLockAcquire(TwoPhaseStateLock, LW_EXCLUSIVE);

	/* And now do the callbacks */
	if (isCommit)
		ProcessRecords(bufptr, xid, twophase_postcommit_callbacks);
	else
		ProcessRecords(bufptr, xid, twophase_postabort_callbacks);

	PredicateLockTwoPhaseFinish(xid, isCommit);

	/* Clear shared memory state */
	RemoveGXact(gxact);

	/*
	 * Release the lock as all callbacks are called and shared memory cleanup
	 * is done.
	 */
	LWLockRelease(TwoPhaseStateLock);

	/* Count the prepared xact as committed or aborted */
	AtEOXact_PgStat(isCommit, false);

	/*
	 * And now we can clean up any files we may have left.
	 */
	if (gxact->ondisk)
		RemoveTwoPhaseFile(xid, true);

	MyLockedGxact = NULL;

	RESUME_INTERRUPTS();

	pfree(buf);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  lockmode; int /*<<< orphan*/  locktag; } ;
typedef  TYPE_3__ TwoPhaseLockRecord ;
struct TYPE_10__ {int /*<<< orphan*/  myLock; } ;
struct TYPE_16__ {TYPE_1__ tag; } ;
struct TYPE_15__ {scalar_t__ locktag_type; } ;
struct TYPE_11__ {int /*<<< orphan*/  mode; TYPE_6__ lock; } ;
struct TYPE_14__ {scalar_t__ nLocks; int numLockOwners; int holdsStrongLockCount; TYPE_2__ tag; TYPE_8__* proclock; int /*<<< orphan*/  lock; TYPE_4__* lockOwners; } ;
struct TYPE_13__ {int /*<<< orphan*/ * owner; } ;
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  TYPE_4__ LOCALLOCKOWNER ;
typedef  TYPE_5__ LOCALLOCK ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_8__* FastPathGetRelationLockEntry (TYPE_5__*) ; 
 scalar_t__ LOCKTAG_VIRTUALTRANSACTION ; 
 int /*<<< orphan*/  LockMethodLocalHash ; 
 int /*<<< orphan*/  RegisterTwoPhaseRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  TWOPHASE_RM_LOCK_ID ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_6__*,int) ; 

void
AtPrepare_Locks(void)
{
	HASH_SEQ_STATUS status;
	LOCALLOCK  *locallock;

	/*
	 * For the most part, we don't need to touch shared memory for this ---
	 * all the necessary state information is in the locallock table.
	 * Fast-path locks are an exception, however: we move any such locks to
	 * the main table before allowing PREPARE TRANSACTION to succeed.
	 */
	hash_seq_init(&status, LockMethodLocalHash);

	while ((locallock = (LOCALLOCK *) hash_seq_search(&status)) != NULL)
	{
		TwoPhaseLockRecord record;
		LOCALLOCKOWNER *lockOwners = locallock->lockOwners;
		bool		haveSessionLock;
		bool		haveXactLock;
		int			i;

		/*
		 * Ignore VXID locks.  We don't want those to be held by prepared
		 * transactions, since they aren't meaningful after a restart.
		 */
		if (locallock->tag.lock.locktag_type == LOCKTAG_VIRTUALTRANSACTION)
			continue;

		/* Ignore it if we don't actually hold the lock */
		if (locallock->nLocks <= 0)
			continue;

		/* Scan to see whether we hold it at session or transaction level */
		haveSessionLock = haveXactLock = false;
		for (i = locallock->numLockOwners - 1; i >= 0; i--)
		{
			if (lockOwners[i].owner == NULL)
				haveSessionLock = true;
			else
				haveXactLock = true;
		}

		/* Ignore it if we have only session lock */
		if (!haveXactLock)
			continue;

		/*
		 * If we have both session- and transaction-level locks, fail.  This
		 * should never happen with regular locks, since we only take those at
		 * session level in some special operations like VACUUM.  It's
		 * possible to hit this with advisory locks, though.
		 *
		 * It would be nice if we could keep the session hold and give away
		 * the transactional hold to the prepared xact.  However, that would
		 * require two PROCLOCK objects, and we cannot be sure that another
		 * PROCLOCK will be available when it comes time for PostPrepare_Locks
		 * to do the deed.  So for now, we error out while we can still do so
		 * safely.
		 */
		if (haveSessionLock)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cannot PREPARE while holding both session-level and transaction-level locks on the same object")));

		/*
		 * If the local lock was taken via the fast-path, we need to move it
		 * to the primary lock table, or just get a pointer to the existing
		 * primary lock table entry if by chance it's already been
		 * transferred.
		 */
		if (locallock->proclock == NULL)
		{
			locallock->proclock = FastPathGetRelationLockEntry(locallock);
			locallock->lock = locallock->proclock->tag.myLock;
		}

		/*
		 * Arrange to not release any strong lock count held by this lock
		 * entry.  We must retain the count until the prepared transaction is
		 * committed or rolled back.
		 */
		locallock->holdsStrongLockCount = false;

		/*
		 * Create a 2PC record.
		 */
		memcpy(&(record.locktag), &(locallock->tag.lock), sizeof(LOCKTAG));
		record.lockmode = locallock->tag.mode;

		RegisterTwoPhaseRecord(TWOPHASE_RM_LOCK_ID, 0,
							   &record, sizeof(TwoPhaseLockRecord));
	}
}
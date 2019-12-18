#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* newestCommitTsXid; void* oldestCommitTsXid; } ;
struct TYPE_4__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  time; } ;
struct TYPE_5__ {int commitTsActive; TYPE_1__ dataLastCommit; void* xidLastCommit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTsControlLock ; 
 int /*<<< orphan*/  CommitTsCtl ; 
 int /*<<< orphan*/  CommitTsLock ; 
 int /*<<< orphan*/  InvalidRepOriginId ; 
 void* InvalidTransactionId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_3__* ShmemVariableCache ; 
 int /*<<< orphan*/  SlruScanDirCbDeleteAll ; 
 int /*<<< orphan*/  SlruScanDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMESTAMP_NOBEGIN (int /*<<< orphan*/ ) ; 
 TYPE_2__* commitTsShared ; 

__attribute__((used)) static void
DeactivateCommitTs(void)
{
	/*
	 * Cleanup the status in the shared memory.
	 *
	 * We reset everything in the commitTsShared record to prevent user from
	 * getting confusing data about last committed transaction on the standby
	 * when the module was activated repeatedly on the primary.
	 */
	LWLockAcquire(CommitTsLock, LW_EXCLUSIVE);

	commitTsShared->commitTsActive = false;
	commitTsShared->xidLastCommit = InvalidTransactionId;
	TIMESTAMP_NOBEGIN(commitTsShared->dataLastCommit.time);
	commitTsShared->dataLastCommit.nodeid = InvalidRepOriginId;

	ShmemVariableCache->oldestCommitTsXid = InvalidTransactionId;
	ShmemVariableCache->newestCommitTsXid = InvalidTransactionId;

	LWLockRelease(CommitTsLock);

	/*
	 * Remove *all* files.  This is necessary so that there are no leftover
	 * files; in the case where this feature is later enabled after running
	 * with it disabled for some time there may be a gap in the file sequence.
	 * (We can probably tolerate out-of-sequence files, as they are going to
	 * be overwritten anyway when we wrap around, but it seems better to be
	 * tidy.)
	 */
	LWLockAcquire(CommitTsControlLock, LW_EXCLUSIVE);
	(void) SlruScanDirectory(CommitTsCtl, SlruScanDirCbDeleteAll, NULL);
	LWLockRelease(CommitTsControlLock);
}
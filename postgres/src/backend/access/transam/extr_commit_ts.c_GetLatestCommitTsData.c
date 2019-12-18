#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_3__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  time; } ;
struct TYPE_4__ {TYPE_1__ dataLastCommit; int /*<<< orphan*/  xidLastCommit; int /*<<< orphan*/  commitTsActive; } ;
typedef  int /*<<< orphan*/  RepOriginId ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTsLock ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 TYPE_2__* commitTsShared ; 
 int /*<<< orphan*/  error_commit_ts_disabled () ; 

TransactionId
GetLatestCommitTsData(TimestampTz *ts, RepOriginId *nodeid)
{
	TransactionId xid;

	LWLockAcquire(CommitTsLock, LW_SHARED);

	/* Error if module not enabled */
	if (!commitTsShared->commitTsActive)
		error_commit_ts_disabled();

	xid = commitTsShared->xidLastCommit;
	if (ts)
		*ts = commitTsShared->dataLastCommit.time;
	if (nodeid)
		*nodeid = commitTsShared->dataLastCommit.nodeid;
	LWLockRelease(CommitTsLock);

	return xid;
}
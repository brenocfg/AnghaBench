#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  PagePrecedes; } ;
struct TYPE_6__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  time; } ;
struct TYPE_7__ {int commitTsActive; TYPE_1__ dataLastCommit; int /*<<< orphan*/  xidLastCommit; } ;
typedef  int /*<<< orphan*/  CommitTimestampShared ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CommitTsControlLock ; 
 TYPE_3__* CommitTsCtl ; 
 int /*<<< orphan*/  CommitTsPagePrecedes ; 
 int /*<<< orphan*/  CommitTsShmemBuffers () ; 
 int /*<<< orphan*/  InvalidRepOriginId ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  LWTRANCHE_COMMITTS_BUFFERS ; 
 TYPE_2__* ShmemInitStruct (char*,int,int*) ; 
 int /*<<< orphan*/  SimpleLruInit (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMESTAMP_NOBEGIN (int /*<<< orphan*/ ) ; 
 TYPE_2__* commitTsShared ; 

void
CommitTsShmemInit(void)
{
	bool		found;

	CommitTsCtl->PagePrecedes = CommitTsPagePrecedes;
	SimpleLruInit(CommitTsCtl, "commit_timestamp", CommitTsShmemBuffers(), 0,
				  CommitTsControlLock, "pg_commit_ts",
				  LWTRANCHE_COMMITTS_BUFFERS);

	commitTsShared = ShmemInitStruct("CommitTs shared",
									 sizeof(CommitTimestampShared),
									 &found);

	if (!IsUnderPostmaster)
	{
		Assert(!found);

		commitTsShared->xidLastCommit = InvalidTransactionId;
		TIMESTAMP_NOBEGIN(commitTsShared->dataLastCommit.time);
		commitTsShared->dataLastCommit.nodeid = InvalidRepOriginId;
		commitTsShared->commitTsActive = false;
	}
	else
		Assert(found);
}
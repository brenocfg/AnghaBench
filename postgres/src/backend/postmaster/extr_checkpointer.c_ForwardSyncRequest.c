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
struct TYPE_6__ {scalar_t__ checkpointer_pid; int num_requests; int max_requests; TYPE_1__* requests; int /*<<< orphan*/  num_backend_fsync; int /*<<< orphan*/  num_backend_writes; } ;
struct TYPE_5__ {scalar_t__ checkpointerLatch; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  ftag; } ;
typedef  int /*<<< orphan*/  SyncRequestType ;
typedef  int /*<<< orphan*/  FileTag ;
typedef  TYPE_1__ CheckpointerRequest ;

/* Variables and functions */
 int /*<<< orphan*/  AmBackgroundWriterProcess () ; 
 scalar_t__ AmCheckpointerProcess () ; 
 int /*<<< orphan*/  CheckpointerCommLock ; 
 TYPE_3__* CheckpointerShmem ; 
 int /*<<< orphan*/  CompactCheckpointerRequestQueue () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_2__* ProcGlobal ; 
 int /*<<< orphan*/  SetLatch (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

bool
ForwardSyncRequest(const FileTag *ftag, SyncRequestType type)
{
	CheckpointerRequest *request;
	bool		too_full;

	if (!IsUnderPostmaster)
		return false;			/* probably shouldn't even get here */

	if (AmCheckpointerProcess())
		elog(ERROR, "ForwardSyncRequest must not be called in checkpointer");

	LWLockAcquire(CheckpointerCommLock, LW_EXCLUSIVE);

	/* Count all backend writes regardless of if they fit in the queue */
	if (!AmBackgroundWriterProcess())
		CheckpointerShmem->num_backend_writes++;

	/*
	 * If the checkpointer isn't running or the request queue is full, the
	 * backend will have to perform its own fsync request.  But before forcing
	 * that to happen, we can try to compact the request queue.
	 */
	if (CheckpointerShmem->checkpointer_pid == 0 ||
		(CheckpointerShmem->num_requests >= CheckpointerShmem->max_requests &&
		 !CompactCheckpointerRequestQueue()))
	{
		/*
		 * Count the subset of writes where backends have to do their own
		 * fsync
		 */
		if (!AmBackgroundWriterProcess())
			CheckpointerShmem->num_backend_fsync++;
		LWLockRelease(CheckpointerCommLock);
		return false;
	}

	/* OK, insert request */
	request = &CheckpointerShmem->requests[CheckpointerShmem->num_requests++];
	request->ftag = *ftag;
	request->type = type;

	/* If queue is more than half full, nudge the checkpointer to empty it */
	too_full = (CheckpointerShmem->num_requests >=
				CheckpointerShmem->max_requests / 2);

	LWLockRelease(CheckpointerCommLock);

	/* ... but not till after we release the lock */
	if (too_full && ProcGlobal->checkpointerLatch)
		SetLatch(ProcGlobal->checkpointerLatch);

	return true;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_7__ {TYPE_1__* slot; } ;
struct TYPE_6__ {size_t slot; scalar_t__ generation; } ;
struct TYPE_5__ {scalar_t__ generation; scalar_t__ pid; int /*<<< orphan*/  in_use; } ;
typedef  int /*<<< orphan*/  BgwHandleStatus ;
typedef  TYPE_1__ BackgroundWorkerSlot ;
typedef  TYPE_2__ BackgroundWorkerHandle ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BGWH_NOT_YET_STARTED ; 
 int /*<<< orphan*/  BGWH_STARTED ; 
 int /*<<< orphan*/  BGWH_STOPPED ; 
 TYPE_4__* BackgroundWorkerData ; 
 int /*<<< orphan*/  BackgroundWorkerLock ; 
 scalar_t__ InvalidPid ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 size_t max_worker_processes ; 

BgwHandleStatus
GetBackgroundWorkerPid(BackgroundWorkerHandle *handle, pid_t *pidp)
{
	BackgroundWorkerSlot *slot;
	pid_t		pid;

	Assert(handle->slot < max_worker_processes);
	slot = &BackgroundWorkerData->slot[handle->slot];

	/*
	 * We could probably arrange to synchronize access to data using memory
	 * barriers only, but for now, let's just keep it simple and grab the
	 * lock.  It seems unlikely that there will be enough traffic here to
	 * result in meaningful contention.
	 */
	LWLockAcquire(BackgroundWorkerLock, LW_SHARED);

	/*
	 * The generation number can't be concurrently changed while we hold the
	 * lock.  The pid, which is updated by the postmaster, can change at any
	 * time, but we assume such changes are atomic.  So the value we read
	 * won't be garbage, but it might be out of date by the time the caller
	 * examines it (but that's unavoidable anyway).
	 *
	 * The in_use flag could be in the process of changing from true to false,
	 * but if it is already false then it can't change further.
	 */
	if (handle->generation != slot->generation || !slot->in_use)
		pid = 0;
	else
		pid = slot->pid;

	/* All done. */
	LWLockRelease(BackgroundWorkerLock);

	if (pid == 0)
		return BGWH_STOPPED;
	else if (pid == InvalidPid)
		return BGWH_NOT_YET_STARTED;
	*pidp = pid;
	return BGWH_STARTED;
}
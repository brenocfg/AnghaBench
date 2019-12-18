#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_13__ {scalar_t__ parallel_register_count; scalar_t__ parallel_terminate_count; int total_slots; TYPE_1__* slot; } ;
struct TYPE_12__ {int bgw_flags; } ;
struct TYPE_11__ {int slot; scalar_t__ generation; } ;
struct TYPE_10__ {int in_use; int terminate; scalar_t__ generation; int /*<<< orphan*/  pid; int /*<<< orphan*/  worker; } ;
typedef  TYPE_1__ BackgroundWorkerSlot ;
typedef  TYPE_2__ BackgroundWorkerHandle ;
typedef  TYPE_3__ BackgroundWorker ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BGWORKER_CLASS_PARALLEL ; 
 TYPE_9__* BackgroundWorkerData ; 
 int /*<<< orphan*/  BackgroundWorkerLock ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidPid ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ MAX_PARALLEL_WORKER_LIMIT ; 
 int /*<<< orphan*/  PMSIGNAL_BACKGROUND_WORKER_CHANGE ; 
 int /*<<< orphan*/  SanityCheckBackgroundWorker (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendPostmasterSignal (int /*<<< orphan*/ ) ; 
 scalar_t__ max_parallel_workers ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 TYPE_2__* palloc (int) ; 
 int /*<<< orphan*/  pg_write_barrier () ; 

bool
RegisterDynamicBackgroundWorker(BackgroundWorker *worker,
								BackgroundWorkerHandle **handle)
{
	int			slotno;
	bool		success = false;
	bool		parallel;
	uint64		generation = 0;

	/*
	 * We can't register dynamic background workers from the postmaster. If
	 * this is a standalone backend, we're the only process and can't start
	 * any more.  In a multi-process environment, it might be theoretically
	 * possible, but we don't currently support it due to locking
	 * considerations; see comments on the BackgroundWorkerSlot data
	 * structure.
	 */
	if (!IsUnderPostmaster)
		return false;

	if (!SanityCheckBackgroundWorker(worker, ERROR))
		return false;

	parallel = (worker->bgw_flags & BGWORKER_CLASS_PARALLEL) != 0;

	LWLockAcquire(BackgroundWorkerLock, LW_EXCLUSIVE);

	/*
	 * If this is a parallel worker, check whether there are already too many
	 * parallel workers; if so, don't register another one.  Our view of
	 * parallel_terminate_count may be slightly stale, but that doesn't really
	 * matter: we would have gotten the same result if we'd arrived here
	 * slightly earlier anyway.  There's no help for it, either, since the
	 * postmaster must not take locks; a memory barrier wouldn't guarantee
	 * anything useful.
	 */
	if (parallel && (BackgroundWorkerData->parallel_register_count -
					 BackgroundWorkerData->parallel_terminate_count) >=
		max_parallel_workers)
	{
		Assert(BackgroundWorkerData->parallel_register_count -
			   BackgroundWorkerData->parallel_terminate_count <=
			   MAX_PARALLEL_WORKER_LIMIT);
		LWLockRelease(BackgroundWorkerLock);
		return false;
	}

	/*
	 * Look for an unused slot.  If we find one, grab it.
	 */
	for (slotno = 0; slotno < BackgroundWorkerData->total_slots; ++slotno)
	{
		BackgroundWorkerSlot *slot = &BackgroundWorkerData->slot[slotno];

		if (!slot->in_use)
		{
			memcpy(&slot->worker, worker, sizeof(BackgroundWorker));
			slot->pid = InvalidPid; /* indicates not started yet */
			slot->generation++;
			slot->terminate = false;
			generation = slot->generation;
			if (parallel)
				BackgroundWorkerData->parallel_register_count++;

			/*
			 * Make sure postmaster doesn't see the slot as in use before it
			 * sees the new contents.
			 */
			pg_write_barrier();

			slot->in_use = true;
			success = true;
			break;
		}
	}

	LWLockRelease(BackgroundWorkerLock);

	/* If we found a slot, tell the postmaster to notice the change. */
	if (success)
		SendPostmasterSignal(PMSIGNAL_BACKGROUND_WORKER_CHANGE);

	/*
	 * If we found a slot and the user has provided a handle, initialize it.
	 */
	if (success && handle)
	{
		*handle = palloc(sizeof(BackgroundWorkerHandle));
		(*handle)->slot = slotno;
		(*handle)->generation = generation;
	}

	return success;
}
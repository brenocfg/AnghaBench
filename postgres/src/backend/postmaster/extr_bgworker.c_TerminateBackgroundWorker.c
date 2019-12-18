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
struct TYPE_7__ {TYPE_1__* slot; } ;
struct TYPE_6__ {size_t slot; scalar_t__ generation; } ;
struct TYPE_5__ {scalar_t__ generation; int terminate; } ;
typedef  TYPE_1__ BackgroundWorkerSlot ;
typedef  TYPE_2__ BackgroundWorkerHandle ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_4__* BackgroundWorkerData ; 
 int /*<<< orphan*/  BackgroundWorkerLock ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  PMSIGNAL_BACKGROUND_WORKER_CHANGE ; 
 int /*<<< orphan*/  SendPostmasterSignal (int /*<<< orphan*/ ) ; 
 size_t max_worker_processes ; 

void
TerminateBackgroundWorker(BackgroundWorkerHandle *handle)
{
	BackgroundWorkerSlot *slot;
	bool		signal_postmaster = false;

	Assert(handle->slot < max_worker_processes);
	slot = &BackgroundWorkerData->slot[handle->slot];

	/* Set terminate flag in shared memory, unless slot has been reused. */
	LWLockAcquire(BackgroundWorkerLock, LW_EXCLUSIVE);
	if (handle->generation == slot->generation)
	{
		slot->terminate = true;
		signal_postmaster = true;
	}
	LWLockRelease(BackgroundWorkerLock);

	/* Make sure the postmaster notices the change to shared memory. */
	if (signal_postmaster)
		SendPostmasterSignal(PMSIGNAL_BACKGROUND_WORKER_CHANGE);
}
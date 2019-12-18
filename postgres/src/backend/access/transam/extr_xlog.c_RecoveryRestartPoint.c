#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {int redo; } ;
struct TYPE_5__ {int /*<<< orphan*/  info_lck; TYPE_1__ lastCheckPoint; int /*<<< orphan*/  lastCheckPointEndPtr; int /*<<< orphan*/  lastCheckPointRecPtr; } ;
typedef  TYPE_1__ CheckPoint ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  EndRecPtr ; 
 int /*<<< orphan*/  ReadRecPtr ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_2__* XLogCtl ; 
 scalar_t__ XLogHaveInvalidPages () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_recovery (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RecoveryRestartPoint(const CheckPoint *checkPoint)
{
	/*
	 * Also refrain from creating a restartpoint if we have seen any
	 * references to non-existent pages. Restarting recovery from the
	 * restartpoint would not see the references, so we would lose the
	 * cross-check that the pages belonged to a relation that was dropped
	 * later.
	 */
	if (XLogHaveInvalidPages())
	{
		elog(trace_recovery(DEBUG2),
			 "could not record restart point at %X/%X because there "
			 "are unresolved references to invalid pages",
			 (uint32) (checkPoint->redo >> 32),
			 (uint32) checkPoint->redo);
		return;
	}

	/*
	 * Copy the checkpoint record to shared memory, so that checkpointer can
	 * work out the next time it wants to perform a restartpoint.
	 */
	SpinLockAcquire(&XLogCtl->info_lck);
	XLogCtl->lastCheckPointRecPtr = ReadRecPtr;
	XLogCtl->lastCheckPointEndPtr = EndRecPtr;
	XLogCtl->lastCheckPoint = *checkPoint;
	SpinLockRelease(&XLogCtl->info_lck);
}
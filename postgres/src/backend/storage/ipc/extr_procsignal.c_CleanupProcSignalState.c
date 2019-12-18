#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pss_pid; } ;
typedef  TYPE_1__ ProcSignalSlot ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ MyProcPid ; 
 TYPE_1__ volatile* MyProcSignalSlot ; 
 TYPE_1__* ProcSignalSlots ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,int,int) ; 

__attribute__((used)) static void
CleanupProcSignalState(int status, Datum arg)
{
	int			pss_idx = DatumGetInt32(arg);
	volatile ProcSignalSlot *slot;

	slot = &ProcSignalSlots[pss_idx - 1];
	Assert(slot == MyProcSignalSlot);

	/*
	 * Clear MyProcSignalSlot, so that a SIGUSR1 received after this point
	 * won't try to access it after it's no longer ours (and perhaps even
	 * after we've unmapped the shared memory segment).
	 */
	MyProcSignalSlot = NULL;

	/* sanity check */
	if (slot->pss_pid != MyProcPid)
	{
		/*
		 * don't ERROR here. We're exiting anyway, and don't want to get into
		 * infinite loop trying to exit
		 */
		elog(LOG, "process %d releasing ProcSignal slot %d, but it contains %d",
			 MyProcPid, pss_idx, (int) slot->pss_pid);
		return;					/* XXX better to zero the slot anyway? */
	}

	slot->pss_pid = 0;
}
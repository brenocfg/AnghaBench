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
typedef  int /*<<< orphan*/  sig_atomic_t ;
struct TYPE_4__ {scalar_t__ pss_pid; int /*<<< orphan*/  pss_signalFlags; } ;
typedef  TYPE_1__ ProcSignalSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CleanupProcSignalState ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MemSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MyProcPid ; 
 TYPE_1__ volatile* MyProcSignalSlot ; 
 int NUM_PROCSIGNALS ; 
 int NumProcSignalSlots ; 
 TYPE_1__* ProcSignalSlots ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  on_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ProcSignalInit(int pss_idx)
{
	volatile ProcSignalSlot *slot;

	Assert(pss_idx >= 1 && pss_idx <= NumProcSignalSlots);

	slot = &ProcSignalSlots[pss_idx - 1];

	/* sanity check */
	if (slot->pss_pid != 0)
		elog(LOG, "process %d taking over ProcSignal slot %d, but it's not empty",
			 MyProcPid, pss_idx);

	/* Clear out any leftover signal reasons */
	MemSet(slot->pss_signalFlags, 0, NUM_PROCSIGNALS * sizeof(sig_atomic_t));

	/* Mark slot with my PID */
	slot->pss_pid = MyProcPid;

	/* Remember slot location for CheckProcSignal */
	MyProcSignalSlot = slot;

	/* Set up to release the slot on process exit */
	on_shmem_exit(CleanupProcSignalState, Int32GetDatum(pss_idx));
}
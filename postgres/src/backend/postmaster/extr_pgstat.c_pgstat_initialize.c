#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * BackendStatusArray ; 
 int InvalidBackendId ; 
 int MaxBackends ; 
 int MyAuxProcType ; 
 int /*<<< orphan*/ * MyBEEntry ; 
 int MyBackendId ; 
 int NotAnAuxProcess ; 
 int /*<<< orphan*/  on_shmem_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_beshutdown_hook ; 

void
pgstat_initialize(void)
{
	/* Initialize MyBEEntry */
	if (MyBackendId != InvalidBackendId)
	{
		Assert(MyBackendId >= 1 && MyBackendId <= MaxBackends);
		MyBEEntry = &BackendStatusArray[MyBackendId - 1];
	}
	else
	{
		/* Must be an auxiliary process */
		Assert(MyAuxProcType != NotAnAuxProcess);

		/*
		 * Assign the MyBEEntry for an auxiliary process.  Since it doesn't
		 * have a BackendId, the slot is statically allocated based on the
		 * auxiliary process type (MyAuxProcType).  Backends use slots indexed
		 * in the range from 1 to MaxBackends (inclusive), so we use
		 * MaxBackends + AuxBackendType + 1 as the index of the slot for an
		 * auxiliary process.
		 */
		MyBEEntry = &BackendStatusArray[MaxBackends + MyAuxProcType];
	}

	/* Set up a process-exit hook to clean up */
	on_shmem_exit(pgstat_beshutdown_hook, 0);
}
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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  LWLockPadded ;
typedef  int /*<<< orphan*/  LWLock ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeLWLocks () ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int LWLOCK_MINIMAL_SIZE ; 
 int LWLOCK_PADDED_SIZE ; 
 int /*<<< orphan*/  LWLockShmemSize () ; 
 int LWTRANCHE_FIRST_USER_DEFINED ; 
 scalar_t__ LW_VAL_EXCLUSIVE ; 
 scalar_t__ MAX_BACKENDS ; 
 int /*<<< orphan*/ * MainLWLockArray ; 
 int /*<<< orphan*/  RegisterLWLockTranches () ; 
 scalar_t__ ShmemAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StaticAssertStmt (int,char*) ; 

void
CreateLWLocks(void)
{
	StaticAssertStmt(LW_VAL_EXCLUSIVE > (uint32) MAX_BACKENDS,
					 "MAX_BACKENDS too big for lwlock.c");

	StaticAssertStmt(sizeof(LWLock) <= LWLOCK_MINIMAL_SIZE &&
					 sizeof(LWLock) <= LWLOCK_PADDED_SIZE,
					 "Miscalculated LWLock padding");

	if (!IsUnderPostmaster)
	{
		Size		spaceLocks = LWLockShmemSize();
		int		   *LWLockCounter;
		char	   *ptr;

		/* Allocate space */
		ptr = (char *) ShmemAlloc(spaceLocks);

		/* Leave room for dynamic allocation of tranches */
		ptr += sizeof(int);

		/* Ensure desired alignment of LWLock array */
		ptr += LWLOCK_PADDED_SIZE - ((uintptr_t) ptr) % LWLOCK_PADDED_SIZE;

		MainLWLockArray = (LWLockPadded *) ptr;

		/*
		 * Initialize the dynamic-allocation counter for tranches, which is
		 * stored just before the first LWLock.
		 */
		LWLockCounter = (int *) ((char *) MainLWLockArray - sizeof(int));
		*LWLockCounter = LWTRANCHE_FIRST_USER_DEFINED;

		/* Initialize all LWLocks */
		InitializeLWLocks();
	}

	/* Register all LWLock tranches */
	RegisterLWLockTranches();
}
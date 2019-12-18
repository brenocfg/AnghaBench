#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mode; int /*<<< orphan*/ * lock; } ;
typedef  scalar_t__ LWLockMode ;
typedef  int /*<<< orphan*/  LWLock ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HOLD_INTERRUPTS () ; 
 int /*<<< orphan*/  LOG_LWDEBUG (char*,int /*<<< orphan*/ *,char*) ; 
 int LWLockAttemptLock (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LW_EXCLUSIVE ; 
 scalar_t__ LW_SHARED ; 
 size_t MAX_SIMUL_LWLOCKS ; 
 int /*<<< orphan*/  PRINT_LWDEBUG (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RESUME_INTERRUPTS () ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_LWLOCK_CONDACQUIRE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_LWLOCK_CONDACQUIRE_FAIL (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  T_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* held_lwlocks ; 
 size_t num_held_lwlocks ; 

bool
LWLockConditionalAcquire(LWLock *lock, LWLockMode mode)
{
	bool		mustwait;

	AssertArg(mode == LW_SHARED || mode == LW_EXCLUSIVE);

	PRINT_LWDEBUG("LWLockConditionalAcquire", lock, mode);

	/* Ensure we will have room to remember the lock */
	if (num_held_lwlocks >= MAX_SIMUL_LWLOCKS)
		elog(ERROR, "too many LWLocks taken");

	/*
	 * Lock out cancel/die interrupts until we exit the code section protected
	 * by the LWLock.  This ensures that interrupts will not interfere with
	 * manipulations of data structures in shared memory.
	 */
	HOLD_INTERRUPTS();

	/* Check for the lock */
	mustwait = LWLockAttemptLock(lock, mode);

	if (mustwait)
	{
		/* Failed to get lock, so release interrupt holdoff */
		RESUME_INTERRUPTS();

		LOG_LWDEBUG("LWLockConditionalAcquire", lock, "failed");
		TRACE_POSTGRESQL_LWLOCK_CONDACQUIRE_FAIL(T_NAME(lock), mode);
	}
	else
	{
		/* Add lock to list of locks held by this backend */
		held_lwlocks[num_held_lwlocks].lock = lock;
		held_lwlocks[num_held_lwlocks++].mode = mode;
		TRACE_POSTGRESQL_LWLOCK_CONDACQUIRE(T_NAME(lock), mode);
	}
	return !mustwait;
}
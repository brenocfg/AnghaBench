#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ LWLock ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockWaitListLock (TYPE_1__*) ; 
 int /*<<< orphan*/  LWLockWaitListUnlock (TYPE_1__*) ; 
 int LW_VAL_EXCLUSIVE ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
LWLockConflictsWithVar(LWLock *lock,
					   uint64 *valptr, uint64 oldval, uint64 *newval,
					   bool *result)
{
	bool		mustwait;
	uint64		value;

	/*
	 * Test first to see if it the slot is free right now.
	 *
	 * XXX: the caller uses a spinlock before this, so we don't need a memory
	 * barrier here as far as the current usage is concerned.  But that might
	 * not be safe in general.
	 */
	mustwait = (pg_atomic_read_u32(&lock->state) & LW_VAL_EXCLUSIVE) != 0;

	if (!mustwait)
	{
		*result = true;
		return false;
	}

	*result = false;

	/*
	 * Read value using the lwlock's wait list lock, as we can't generally
	 * rely on atomic 64 bit reads/stores.  TODO: On platforms with a way to
	 * do atomic 64 bit reads/writes the spinlock should be optimized away.
	 */
	LWLockWaitListLock(lock);
	value = *valptr;
	LWLockWaitListUnlock(lock);

	if (value != oldval)
	{
		mustwait = false;
		*newval = value;
	}
	else
	{
		mustwait = true;
	}

	return mustwait;
}
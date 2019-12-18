#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_3__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  state; } ;
typedef  scalar_t__ LWLockMode ;
typedef  TYPE_1__ LWLock ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int) ; 
 scalar_t__ LW_EXCLUSIVE ; 
 int LW_LOCK_MASK ; 
 scalar_t__ LW_SHARED ; 
 int LW_VAL_EXCLUSIVE ; 
 scalar_t__ LW_VAL_SHARED ; 
 int /*<<< orphan*/  MyProc ; 
 scalar_t__ pg_atomic_compare_exchange_u32 (int /*<<< orphan*/ *,int*,int) ; 
 int pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_unreachable () ; 

__attribute__((used)) static bool
LWLockAttemptLock(LWLock *lock, LWLockMode mode)
{
	uint32		old_state;

	AssertArg(mode == LW_EXCLUSIVE || mode == LW_SHARED);

	/*
	 * Read once outside the loop, later iterations will get the newer value
	 * via compare & exchange.
	 */
	old_state = pg_atomic_read_u32(&lock->state);

	/* loop until we've determined whether we could acquire the lock or not */
	while (true)
	{
		uint32		desired_state;
		bool		lock_free;

		desired_state = old_state;

		if (mode == LW_EXCLUSIVE)
		{
			lock_free = (old_state & LW_LOCK_MASK) == 0;
			if (lock_free)
				desired_state += LW_VAL_EXCLUSIVE;
		}
		else
		{
			lock_free = (old_state & LW_VAL_EXCLUSIVE) == 0;
			if (lock_free)
				desired_state += LW_VAL_SHARED;
		}

		/*
		 * Attempt to swap in the state we are expecting. If we didn't see
		 * lock to be free, that's just the old value. If we saw it as free,
		 * we'll attempt to mark it acquired. The reason that we always swap
		 * in the value is that this doubles as a memory barrier. We could try
		 * to be smarter and only swap in values if we saw the lock as free,
		 * but benchmark haven't shown it as beneficial so far.
		 *
		 * Retry if the value changed since we last looked at it.
		 */
		if (pg_atomic_compare_exchange_u32(&lock->state,
										   &old_state, desired_state))
		{
			if (lock_free)
			{
				/* Great! Got the lock. */
#ifdef LOCK_DEBUG
				if (mode == LW_EXCLUSIVE)
					lock->owner = MyProc;
#endif
				return false;
			}
			else
				return true;	/* somebody else has the lock */
		}
	}
	pg_unreachable();
}
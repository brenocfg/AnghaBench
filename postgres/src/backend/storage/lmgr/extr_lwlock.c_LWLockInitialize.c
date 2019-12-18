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
struct TYPE_3__ {int tranche; int /*<<< orphan*/  waiters; int /*<<< orphan*/  nwaiters; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ LWLock ;

/* Variables and functions */
 int /*<<< orphan*/  LW_FLAG_RELEASE_OK ; 
 int /*<<< orphan*/  pg_atomic_init_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proclist_init (int /*<<< orphan*/ *) ; 

void
LWLockInitialize(LWLock *lock, int tranche_id)
{
	pg_atomic_init_u32(&lock->state, LW_FLAG_RELEASE_OK);
#ifdef LOCK_DEBUG
	pg_atomic_init_u32(&lock->nwaiters, 0);
#endif
	lock->tranche = tranche_id;
	proclist_init(&lock->waiters);
}
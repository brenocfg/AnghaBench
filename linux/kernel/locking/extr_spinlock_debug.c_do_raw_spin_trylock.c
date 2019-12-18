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
struct TYPE_5__ {int /*<<< orphan*/  raw_lock; } ;
typedef  TYPE_1__ raw_spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIN_BUG_ON (int,TYPE_1__*,char*) ; 
 int arch_spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_spin_lock_after (TYPE_1__*) ; 
 int /*<<< orphan*/  mmiowb_spin_lock () ; 

int do_raw_spin_trylock(raw_spinlock_t *lock)
{
	int ret = arch_spin_trylock(&lock->raw_lock);

	if (ret) {
		mmiowb_spin_lock();
		debug_spin_lock_after(lock);
	}
#ifndef CONFIG_SMP
	/*
	 * Must not happen on UP:
	 */
	SPIN_BUG_ON(!ret, lock, "trylock failure on UP");
#endif
	return ret;
}
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
struct TYPE_4__ {int /*<<< orphan*/  raw_lock; } ;
typedef  TYPE_1__ rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  RWLOCK_BUG_ON (int,TYPE_1__*,char*) ; 
 int arch_read_trylock (int /*<<< orphan*/ *) ; 

int do_raw_read_trylock(rwlock_t *lock)
{
	int ret = arch_read_trylock(&lock->raw_lock);

#ifndef CONFIG_SMP
	/*
	 * Must not happen on UP:
	 */
	RWLOCK_BUG_ON(!ret, lock, "trylock failure on UP");
#endif
	return ret;
}
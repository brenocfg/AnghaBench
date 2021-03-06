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
typedef  int slock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int NUM_SPINLOCK_SEMAPHORES ; 
 int /*<<< orphan*/  PGSemaphoreUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SpinlockSemaArray ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

void
s_unlock_sema(volatile slock_t *lock)
{
	int			lockndx = *lock;

	if (lockndx <= 0 || lockndx > NUM_SPINLOCK_SEMAPHORES)
		elog(ERROR, "invalid spinlock number: %d", lockndx);
	PGSemaphoreUnlock(SpinlockSemaArray[lockndx - 1]);
}
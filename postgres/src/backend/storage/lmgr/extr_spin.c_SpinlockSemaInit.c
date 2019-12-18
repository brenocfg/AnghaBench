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
typedef  int /*<<< orphan*/  PGSemaphore ;

/* Variables and functions */
 int /*<<< orphan*/  PGSemaphoreCreate () ; 
 scalar_t__ ShmemAllocUnlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SpinlockSemaArray ; 
 int /*<<< orphan*/  SpinlockSemaSize () ; 
 int SpinlockSemas () ; 

void
SpinlockSemaInit(void)
{
	PGSemaphore *spinsemas;
	int			nsemas = SpinlockSemas();
	int			i;

	/*
	 * We must use ShmemAllocUnlocked(), since the spinlock protecting
	 * ShmemAlloc() obviously can't be ready yet.
	 */
	spinsemas = (PGSemaphore *) ShmemAllocUnlocked(SpinlockSemaSize());
	for (i = 0; i < nsemas; ++i)
		spinsemas[i] = PGSemaphoreCreate();
	SpinlockSemaArray = spinsemas;
}
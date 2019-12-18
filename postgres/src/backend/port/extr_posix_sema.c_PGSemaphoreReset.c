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
 scalar_t__ EAGAIN ; 
 scalar_t__ EDEADLK ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  PG_SEM_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ sem_trywait (int /*<<< orphan*/ ) ; 

void
PGSemaphoreReset(PGSemaphore sema)
{
	/*
	 * There's no direct API for this in POSIX, so we have to ratchet the
	 * semaphore down to 0 with repeated trywait's.
	 */
	for (;;)
	{
		if (sem_trywait(PG_SEM_REF(sema)) < 0)
		{
			if (errno == EAGAIN || errno == EDEADLK)
				break;			/* got it down to 0 */
			if (errno == EINTR)
				continue;		/* can this happen? */
			elog(FATAL, "sem_trywait failed: %m");
		}
	}
}
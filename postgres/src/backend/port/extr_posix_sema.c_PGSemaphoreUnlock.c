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
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  PG_SEM_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int sem_post (int /*<<< orphan*/ ) ; 

void
PGSemaphoreUnlock(PGSemaphore sema)
{
	int			errStatus;

	/*
	 * Note: if errStatus is -1 and errno == EINTR then it means we returned
	 * from the operation prematurely because we were sent a signal.  So we
	 * try and unlock the semaphore again. Not clear this can really happen,
	 * but might as well cope.
	 */
	do
	{
		errStatus = sem_post(PG_SEM_REF(sema));
	} while (errStatus < 0 && errno == EINTR);

	if (errStatus < 0)
		elog(FATAL, "sem_post failed: %m");
}
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
struct sembuf {int sem_op; int /*<<< orphan*/  sem_num; int /*<<< orphan*/  sem_flg; } ;
struct TYPE_3__ {int /*<<< orphan*/  semId; int /*<<< orphan*/  semNum; } ;
typedef  TYPE_1__* PGSemaphore ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  IPC_NOWAIT ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int semop (int /*<<< orphan*/ ,struct sembuf*,int) ; 

bool
PGSemaphoreTryLock(PGSemaphore sema)
{
	int			errStatus;
	struct sembuf sops;

	sops.sem_op = -1;			/* decrement */
	sops.sem_flg = IPC_NOWAIT;	/* but don't block */
	sops.sem_num = sema->semNum;

	/*
	 * Note: if errStatus is -1 and errno == EINTR then it means we returned
	 * from the operation prematurely because we were sent a signal.  So we
	 * try and lock the semaphore again.
	 */
	do
	{
		errStatus = semop(sema->semId, &sops, 1);
	} while (errStatus < 0 && errno == EINTR);

	if (errStatus < 0)
	{
		/* Expect EAGAIN or EWOULDBLOCK (platform-dependent) */
#ifdef EAGAIN
		if (errno == EAGAIN)
			return false;		/* failed to lock it */
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || (EWOULDBLOCK != EAGAIN))
		if (errno == EWOULDBLOCK)
			return false;		/* failed to lock it */
#endif
		/* Otherwise we got trouble */
		elog(FATAL, "semop(id=%d) failed: %m", sema->semId);
	}

	return true;
}
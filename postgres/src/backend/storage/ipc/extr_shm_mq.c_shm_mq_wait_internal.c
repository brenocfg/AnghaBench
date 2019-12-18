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
struct TYPE_3__ {scalar_t__ mq_detached; int /*<<< orphan*/  mq_mutex; } ;
typedef  TYPE_1__ shm_mq ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  PGPROC ;
typedef  scalar_t__ BgwHandleStatus ;
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;

/* Variables and functions */
 scalar_t__ BGWH_NOT_YET_STARTED ; 
 scalar_t__ BGWH_STARTED ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ GetBackgroundWorkerPid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAIT_EVENT_MQ_INTERNAL ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int /*<<< orphan*/  WaitLatch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
shm_mq_wait_internal(shm_mq *mq, PGPROC **ptr, BackgroundWorkerHandle *handle)
{
	bool		result = false;

	for (;;)
	{
		BgwHandleStatus status;
		pid_t		pid;

		/* Acquire the lock just long enough to check the pointer. */
		SpinLockAcquire(&mq->mq_mutex);
		result = (*ptr != NULL);
		SpinLockRelease(&mq->mq_mutex);

		/* Fail if detached; else succeed if initialized. */
		if (mq->mq_detached)
		{
			result = false;
			break;
		}
		if (result)
			break;

		if (handle != NULL)
		{
			/* Check for unexpected worker death. */
			status = GetBackgroundWorkerPid(handle, &pid);
			if (status != BGWH_STARTED && status != BGWH_NOT_YET_STARTED)
			{
				result = false;
				break;
			}
		}

		/* Wait to be signalled. */
		(void) WaitLatch(MyLatch, WL_LATCH_SET | WL_EXIT_ON_PM_DEATH, 0,
						 WAIT_EVENT_MQ_INTERNAL);

		/* Reset the latch so we don't spin. */
		ResetLatch(MyLatch);

		/* An interrupt may have occurred while we were waiting. */
		CHECK_FOR_INTERRUPTS();
	}

	return result;
}
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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  BgwHandleStatus ;
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;

/* Variables and functions */
 int /*<<< orphan*/  BGWH_POSTMASTER_DIED ; 
 int /*<<< orphan*/  BGWH_STOPPED ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  GetBackgroundWorkerPid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_BGWORKER_SHUTDOWN ; 
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int WaitLatch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BgwHandleStatus
WaitForBackgroundWorkerShutdown(BackgroundWorkerHandle *handle)
{
	BgwHandleStatus status;
	int			rc;

	for (;;)
	{
		pid_t		pid;

		CHECK_FOR_INTERRUPTS();

		status = GetBackgroundWorkerPid(handle, &pid);
		if (status == BGWH_STOPPED)
			break;

		rc = WaitLatch(MyLatch,
					   WL_LATCH_SET | WL_POSTMASTER_DEATH, 0,
					   WAIT_EVENT_BGWORKER_SHUTDOWN);

		if (rc & WL_POSTMASTER_DEATH)
		{
			status = BGWH_POSTMASTER_DIED;
			break;
		}

		ResetLatch(MyLatch);
	}

	return status;
}
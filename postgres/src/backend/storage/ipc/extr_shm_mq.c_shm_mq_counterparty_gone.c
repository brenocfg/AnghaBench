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
struct TYPE_3__ {int mq_detached; } ;
typedef  TYPE_1__ shm_mq ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  scalar_t__ BgwHandleStatus ;
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;

/* Variables and functions */
 scalar_t__ BGWH_NOT_YET_STARTED ; 
 scalar_t__ BGWH_STARTED ; 
 scalar_t__ GetBackgroundWorkerPid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
shm_mq_counterparty_gone(shm_mq *mq, BackgroundWorkerHandle *handle)
{
	pid_t		pid;

	/* If the queue has been detached, counterparty is definitely gone. */
	if (mq->mq_detached)
		return true;

	/* If there's a handle, check worker status. */
	if (handle != NULL)
	{
		BgwHandleStatus status;

		/* Check for unexpected worker death. */
		status = GetBackgroundWorkerPid(handle, &pid);
		if (status != BGWH_STARTED && status != BGWH_NOT_YET_STARTED)
		{
			/* Mark it detached, just to make it official. */
			mq->mq_detached = true;
			return true;
		}
	}

	/* Counterparty is not definitively gone. */
	return false;
}
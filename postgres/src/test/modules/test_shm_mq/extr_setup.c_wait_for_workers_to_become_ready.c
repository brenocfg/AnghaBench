#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nworkers; } ;
typedef  TYPE_1__ worker_state ;
struct TYPE_7__ {int workers_ready; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ test_shm_mq_header ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  PG_WAIT_EXTENSION ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int /*<<< orphan*/  WaitLatch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_worker_status (TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
wait_for_workers_to_become_ready(worker_state *wstate,
								 volatile test_shm_mq_header *hdr)
{
	bool		result = false;

	for (;;)
	{
		int			workers_ready;

		/* If all the workers are ready, we have succeeded. */
		SpinLockAcquire(&hdr->mutex);
		workers_ready = hdr->workers_ready;
		SpinLockRelease(&hdr->mutex);
		if (workers_ready >= wstate->nworkers)
		{
			result = true;
			break;
		}

		/* If any workers (or the postmaster) have died, we have failed. */
		if (!check_worker_status(wstate))
		{
			result = false;
			break;
		}

		/* Wait to be signalled. */
		(void) WaitLatch(MyLatch, WL_LATCH_SET | WL_EXIT_ON_PM_DEATH, 0,
						 PG_WAIT_EXTENSION);

		/* Reset the latch so we don't spin. */
		ResetLatch(MyLatch);

		/* An interrupt may have occurred while we were waiting. */
		CHECK_FOR_INTERRUPTS();
	}

	if (!result)
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_RESOURCES),
				 errmsg("one or more background workers failed to start")));
}
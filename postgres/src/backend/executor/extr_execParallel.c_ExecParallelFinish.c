#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nworkers_launched; } ;
struct TYPE_4__ {int finished; int /*<<< orphan*/ * buffer_usage; TYPE_2__* pcxt; int /*<<< orphan*/ * reader; int /*<<< orphan*/ * tqueue; } ;
typedef  TYPE_1__ ParallelExecutorInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyTupleQueueReader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InstrAccumParallelQuery (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitForParallelWorkersToFinish (TYPE_2__*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_mq_detach (int /*<<< orphan*/ ) ; 

void
ExecParallelFinish(ParallelExecutorInfo *pei)
{
	int			nworkers = pei->pcxt->nworkers_launched;
	int			i;

	/* Make this be a no-op if called twice in a row. */
	if (pei->finished)
		return;

	/*
	 * Detach from tuple queues ASAP, so that any still-active workers will
	 * notice that no further results are wanted.
	 */
	if (pei->tqueue != NULL)
	{
		for (i = 0; i < nworkers; i++)
			shm_mq_detach(pei->tqueue[i]);
		pfree(pei->tqueue);
		pei->tqueue = NULL;
	}

	/*
	 * While we're waiting for the workers to finish, let's get rid of the
	 * tuple queue readers.  (Any other local cleanup could be done here too.)
	 */
	if (pei->reader != NULL)
	{
		for (i = 0; i < nworkers; i++)
			DestroyTupleQueueReader(pei->reader[i]);
		pfree(pei->reader);
		pei->reader = NULL;
	}

	/* Now wait for the workers to finish. */
	WaitForParallelWorkersToFinish(pei->pcxt);

	/*
	 * Next, accumulate buffer usage.  (This must wait for the workers to
	 * finish, or we might get incomplete data.)
	 */
	for (i = 0; i < nworkers; i++)
		InstrAccumParallelQuery(&pei->buffer_usage[i]);

	pei->finished = true;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nworkers_launched; struct TYPE_5__* function_name; struct TYPE_5__* library_name; struct TYPE_5__* worker; struct TYPE_5__* private_memory; int /*<<< orphan*/ * seg; int /*<<< orphan*/ * error_mqh; int /*<<< orphan*/  bgwhandle; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ ParallelContext ;

/* Variables and functions */
 int /*<<< orphan*/  HOLD_INTERRUPTS () ; 
 int /*<<< orphan*/  RESUME_INTERRUPTS () ; 
 int /*<<< orphan*/  TerminateBackgroundWorker (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForParallelWorkersToExit (TYPE_1__*) ; 
 int /*<<< orphan*/  dlist_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  shm_mq_detach (int /*<<< orphan*/ *) ; 

void
DestroyParallelContext(ParallelContext *pcxt)
{
	int			i;

	/*
	 * Be careful about order of operations here!  We remove the parallel
	 * context from the list before we do anything else; otherwise, if an
	 * error occurs during a subsequent step, we might try to nuke it again
	 * from AtEOXact_Parallel or AtEOSubXact_Parallel.
	 */
	dlist_delete(&pcxt->node);

	/* Kill each worker in turn, and forget their error queues. */
	if (pcxt->worker != NULL)
	{
		for (i = 0; i < pcxt->nworkers_launched; ++i)
		{
			if (pcxt->worker[i].error_mqh != NULL)
			{
				TerminateBackgroundWorker(pcxt->worker[i].bgwhandle);

				shm_mq_detach(pcxt->worker[i].error_mqh);
				pcxt->worker[i].error_mqh = NULL;
			}
		}
	}

	/*
	 * If we have allocated a shared memory segment, detach it.  This will
	 * implicitly detach the error queues, and any other shared memory queues,
	 * stored there.
	 */
	if (pcxt->seg != NULL)
	{
		dsm_detach(pcxt->seg);
		pcxt->seg = NULL;
	}

	/*
	 * If this parallel context is actually in backend-private memory rather
	 * than shared memory, free that memory instead.
	 */
	if (pcxt->private_memory != NULL)
	{
		pfree(pcxt->private_memory);
		pcxt->private_memory = NULL;
	}

	/*
	 * We can't finish transaction commit or abort until all of the workers
	 * have exited.  This means, in particular, that we can't respond to
	 * interrupts at this stage.
	 */
	HOLD_INTERRUPTS();
	WaitForParallelWorkersToExit(pcxt);
	RESUME_INTERRUPTS();

	/* Free the worker array itself. */
	if (pcxt->worker != NULL)
	{
		pfree(pcxt->worker);
		pcxt->worker = NULL;
	}

	/* Free memory. */
	pfree(pcxt->library_name);
	pfree(pcxt->function_name);
	pfree(pcxt);
}
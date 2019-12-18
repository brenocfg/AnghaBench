#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleQueueReader ;
struct TYPE_4__ {size_t nextreader; size_t nreaders; scalar_t__ need_to_scan_locally; int /*<<< orphan*/ ** reader; } ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_1__ GatherState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ExecShutdownGatherWorkers (TYPE_1__*) ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TupleQueueReaderNext (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  WAIT_EVENT_EXECUTE_GATHER ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int /*<<< orphan*/  WaitLatch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static HeapTuple
gather_readnext(GatherState *gatherstate)
{
	int			nvisited = 0;

	for (;;)
	{
		TupleQueueReader *reader;
		HeapTuple	tup;
		bool		readerdone;

		/* Check for async events, particularly messages from workers. */
		CHECK_FOR_INTERRUPTS();

		/*
		 * Attempt to read a tuple, but don't block if none is available.
		 *
		 * Note that TupleQueueReaderNext will just return NULL for a worker
		 * which fails to initialize.  We'll treat that worker as having
		 * produced no tuples; WaitForParallelWorkersToFinish will error out
		 * when we get there.
		 */
		Assert(gatherstate->nextreader < gatherstate->nreaders);
		reader = gatherstate->reader[gatherstate->nextreader];
		tup = TupleQueueReaderNext(reader, true, &readerdone);

		/*
		 * If this reader is done, remove it from our working array of active
		 * readers.  If all readers are done, we're outta here.
		 */
		if (readerdone)
		{
			Assert(!tup);
			--gatherstate->nreaders;
			if (gatherstate->nreaders == 0)
			{
				ExecShutdownGatherWorkers(gatherstate);
				return NULL;
			}
			memmove(&gatherstate->reader[gatherstate->nextreader],
					&gatherstate->reader[gatherstate->nextreader + 1],
					sizeof(TupleQueueReader *)
					* (gatherstate->nreaders - gatherstate->nextreader));
			if (gatherstate->nextreader >= gatherstate->nreaders)
				gatherstate->nextreader = 0;
			continue;
		}

		/* If we got a tuple, return it. */
		if (tup)
			return tup;

		/*
		 * Advance nextreader pointer in round-robin fashion.  Note that we
		 * only reach this code if we weren't able to get a tuple from the
		 * current worker.  We used to advance the nextreader pointer after
		 * every tuple, but it turns out to be much more efficient to keep
		 * reading from the same queue until that would require blocking.
		 */
		gatherstate->nextreader++;
		if (gatherstate->nextreader >= gatherstate->nreaders)
			gatherstate->nextreader = 0;

		/* Have we visited every (surviving) TupleQueueReader? */
		nvisited++;
		if (nvisited >= gatherstate->nreaders)
		{
			/*
			 * If (still) running plan locally, return NULL so caller can
			 * generate another tuple from the local copy of the plan.
			 */
			if (gatherstate->need_to_scan_locally)
				return NULL;

			/* Nothing to do except wait for developments. */
			(void) WaitLatch(MyLatch, WL_LATCH_SET | WL_EXIT_ON_PM_DEATH, 0,
							 WAIT_EVENT_EXECUTE_GATHER);
			ResetLatch(MyLatch);
			nvisited = 0;
		}
	}
}
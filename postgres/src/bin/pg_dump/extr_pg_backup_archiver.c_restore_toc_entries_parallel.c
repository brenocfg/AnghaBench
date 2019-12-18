#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int reqs; int /*<<< orphan*/  tag; int /*<<< orphan*/  desc; int /*<<< orphan*/  dumpId; } ;
typedef  TYPE_1__ TocEntry ;
struct TYPE_22__ {int /*<<< orphan*/  restorePass; int /*<<< orphan*/  tocCount; } ;
struct TYPE_21__ {scalar_t__ first_te; scalar_t__ last_te; } ;
typedef  int /*<<< orphan*/  ParallelState ;
typedef  TYPE_2__ ParallelReadyList ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ACT_RESTORE ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DispatchJobForTocEntry (TYPE_3__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ IsEveryWorkerIdle (int /*<<< orphan*/ *) ; 
 int REQ_DATA ; 
 int REQ_SCHEMA ; 
 int /*<<< orphan*/  RESTORE_PASS_LAST ; 
 int /*<<< orphan*/  RESTORE_PASS_MAIN ; 
 int /*<<< orphan*/  WFW_GOT_STATUS ; 
 int /*<<< orphan*/  WFW_ONE_IDLE ; 
 int /*<<< orphan*/  WaitForWorkers (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_restore_job_done ; 
 int /*<<< orphan*/  move_to_ready_list (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_debug (char*) ; 
 int /*<<< orphan*/  pg_log_info (char*,...) ; 
 TYPE_1__* pop_next_work_item (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ready_list_free (TYPE_2__*) ; 
 int /*<<< orphan*/  ready_list_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reduce_dependencies (TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void
restore_toc_entries_parallel(ArchiveHandle *AH, ParallelState *pstate,
							 TocEntry *pending_list)
{
	ParallelReadyList ready_list;
	TocEntry   *next_work_item;

	pg_log_debug("entering restore_toc_entries_parallel");

	/* Set up ready_list with enough room for all known TocEntrys */
	ready_list_init(&ready_list, AH->tocCount);

	/*
	 * The pending_list contains all items that we need to restore.  Move all
	 * items that are available to process immediately into the ready_list.
	 * After this setup, the pending list is everything that needs to be done
	 * but is blocked by one or more dependencies, while the ready list
	 * contains items that have no remaining dependencies and are OK to
	 * process in the current restore pass.
	 */
	AH->restorePass = RESTORE_PASS_MAIN;
	move_to_ready_list(pending_list, &ready_list, AH->restorePass);

	/*
	 * main parent loop
	 *
	 * Keep going until there is no worker still running AND there is no work
	 * left to be done.  Note invariant: at top of loop, there should always
	 * be at least one worker available to dispatch a job to.
	 */
	pg_log_info("entering main parallel loop");

	for (;;)
	{
		/* Look for an item ready to be dispatched to a worker */
		next_work_item = pop_next_work_item(AH, &ready_list, pstate);
		if (next_work_item != NULL)
		{
			/* If not to be restored, don't waste time launching a worker */
			if ((next_work_item->reqs & (REQ_SCHEMA | REQ_DATA)) == 0)
			{
				pg_log_info("skipping item %d %s %s",
							next_work_item->dumpId,
							next_work_item->desc, next_work_item->tag);
				/* Update its dependencies as though we'd completed it */
				reduce_dependencies(AH, next_work_item, &ready_list);
				/* Loop around to see if anything else can be dispatched */
				continue;
			}

			pg_log_info("launching item %d %s %s",
						next_work_item->dumpId,
						next_work_item->desc, next_work_item->tag);

			/* Dispatch to some worker */
			DispatchJobForTocEntry(AH, pstate, next_work_item, ACT_RESTORE,
								   mark_restore_job_done, &ready_list);
		}
		else if (IsEveryWorkerIdle(pstate))
		{
			/*
			 * Nothing is ready and no worker is running, so we're done with
			 * the current pass or maybe with the whole process.
			 */
			if (AH->restorePass == RESTORE_PASS_LAST)
				break;			/* No more parallel processing is possible */

			/* Advance to next restore pass */
			AH->restorePass++;
			/* That probably allows some stuff to be made ready */
			move_to_ready_list(pending_list, &ready_list, AH->restorePass);
			/* Loop around to see if anything's now ready */
			continue;
		}
		else
		{
			/*
			 * We have nothing ready, but at least one child is working, so
			 * wait for some subjob to finish.
			 */
		}

		/*
		 * Before dispatching another job, check to see if anything has
		 * finished.  We should check every time through the loop so as to
		 * reduce dependencies as soon as possible.  If we were unable to
		 * dispatch any job this time through, wait until some worker finishes
		 * (and, hopefully, unblocks some pending item).  If we did dispatch
		 * something, continue as soon as there's at least one idle worker.
		 * Note that in either case, there's guaranteed to be at least one
		 * idle worker when we return to the top of the loop.  This ensures we
		 * won't block inside DispatchJobForTocEntry, which would be
		 * undesirable: we'd rather postpone dispatching until we see what's
		 * been unblocked by finished jobs.
		 */
		WaitForWorkers(AH, pstate,
					   next_work_item ? WFW_ONE_IDLE : WFW_GOT_STATUS);
	}

	/* There should now be nothing in ready_list. */
	Assert(ready_list.first_te > ready_list.last_te);

	ready_list_free(&ready_list);

	pg_log_info("finished main parallel loop");
}
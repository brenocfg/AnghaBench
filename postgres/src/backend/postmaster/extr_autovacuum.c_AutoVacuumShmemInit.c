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
typedef  TYPE_1__* WorkerInfo ;
struct TYPE_5__ {int /*<<< orphan*/  av_freeWorkers; int /*<<< orphan*/  av_workItems; int /*<<< orphan*/ * av_startingWorker; int /*<<< orphan*/  av_runningWorkers; scalar_t__ av_launcherpid; } ;
struct TYPE_4__ {int /*<<< orphan*/  wi_links; } ;
typedef  int /*<<< orphan*/  AutoVacuumWorkItem ;
typedef  TYPE_2__ AutoVacuumShmemStruct ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_2__* AutoVacuumShmem ; 
 int /*<<< orphan*/  AutoVacuumShmemSize () ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int MAXALIGN (int) ; 
 int NUM_WORKITEMS ; 
 scalar_t__ ShmemInitStruct (char*,int /*<<< orphan*/ ,int*) ; 
 int autovacuum_max_workers ; 
 int /*<<< orphan*/  dlist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
AutoVacuumShmemInit(void)
{
	bool		found;

	AutoVacuumShmem = (AutoVacuumShmemStruct *)
		ShmemInitStruct("AutoVacuum Data",
						AutoVacuumShmemSize(),
						&found);

	if (!IsUnderPostmaster)
	{
		WorkerInfo	worker;
		int			i;

		Assert(!found);

		AutoVacuumShmem->av_launcherpid = 0;
		dlist_init(&AutoVacuumShmem->av_freeWorkers);
		dlist_init(&AutoVacuumShmem->av_runningWorkers);
		AutoVacuumShmem->av_startingWorker = NULL;
		memset(AutoVacuumShmem->av_workItems, 0,
			   sizeof(AutoVacuumWorkItem) * NUM_WORKITEMS);

		worker = (WorkerInfo) ((char *) AutoVacuumShmem +
							   MAXALIGN(sizeof(AutoVacuumShmemStruct)));

		/* initialize the WorkerInfo free list */
		for (i = 0; i < autovacuum_max_workers; i++)
			dlist_push_head(&AutoVacuumShmem->av_freeWorkers,
							&worker[i].wi_links);
	}
	else
		Assert(found);
}
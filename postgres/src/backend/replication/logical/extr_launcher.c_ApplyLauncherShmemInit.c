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
struct TYPE_5__ {int /*<<< orphan*/  relmutex; struct TYPE_5__* workers; } ;
typedef  TYPE_1__ LogicalRepWorker ;
typedef  TYPE_1__ LogicalRepCtxStruct ;

/* Variables and functions */
 int ApplyLauncherShmemSize () ; 
 TYPE_1__* LogicalRepCtx ; 
 scalar_t__ ShmemInitStruct (char*,int,int*) ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 int max_logical_replication_workers ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
ApplyLauncherShmemInit(void)
{
	bool		found;

	LogicalRepCtx = (LogicalRepCtxStruct *)
		ShmemInitStruct("Logical Replication Launcher Data",
						ApplyLauncherShmemSize(),
						&found);

	if (!found)
	{
		int			slot;

		memset(LogicalRepCtx, 0, ApplyLauncherShmemSize());

		/* Initialize memory and spin locks for each worker slot. */
		for (slot = 0; slot < max_logical_replication_workers; slot++)
		{
			LogicalRepWorker *worker = &LogicalRepCtx->workers[slot];

			memset(worker, 0, sizeof(LogicalRepWorker));
			SpinLockInit(&worker->relmutex);
		}
	}
}
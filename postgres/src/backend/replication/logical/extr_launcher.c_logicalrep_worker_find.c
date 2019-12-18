#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* workers; } ;
struct TYPE_4__ {scalar_t__ subid; scalar_t__ relid; scalar_t__ proc; scalar_t__ in_use; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ LogicalRepWorker ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 TYPE_3__* LogicalRepCtx ; 
 int /*<<< orphan*/  LogicalRepWorkerLock ; 
 int max_logical_replication_workers ; 

LogicalRepWorker *
logicalrep_worker_find(Oid subid, Oid relid, bool only_running)
{
	int			i;
	LogicalRepWorker *res = NULL;

	Assert(LWLockHeldByMe(LogicalRepWorkerLock));

	/* Search for attached worker for a given subscription id. */
	for (i = 0; i < max_logical_replication_workers; i++)
	{
		LogicalRepWorker *w = &LogicalRepCtx->workers[i];

		if (w->in_use && w->subid == subid && w->relid == relid &&
			(!only_running || w->proc))
		{
			res = w;
			break;
		}
	}

	return res;
}
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
struct TYPE_3__ {int in_use; void* relid; void* subid; void* userid; void* dbid; int /*<<< orphan*/ * proc; } ;
typedef  TYPE_1__ LogicalRepWorker ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  LWLockHeldByMeInMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LogicalRepWorkerLock ; 

__attribute__((used)) static void
logicalrep_worker_cleanup(LogicalRepWorker *worker)
{
	Assert(LWLockHeldByMeInMode(LogicalRepWorkerLock, LW_EXCLUSIVE));

	worker->in_use = false;
	worker->proc = NULL;
	worker->dbid = InvalidOid;
	worker->userid = InvalidOid;
	worker->subid = InvalidOid;
	worker->relid = InvalidOid;
}
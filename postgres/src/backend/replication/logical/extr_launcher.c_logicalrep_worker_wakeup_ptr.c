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
struct TYPE_5__ {TYPE_1__* proc; } ;
struct TYPE_4__ {int /*<<< orphan*/  procLatch; } ;
typedef  TYPE_2__ LogicalRepWorker ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogicalRepWorkerLock ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 

void
logicalrep_worker_wakeup_ptr(LogicalRepWorker *worker)
{
	Assert(LWLockHeldByMe(LogicalRepWorkerLock));

	SetLatch(&worker->proc->procLatch);
}
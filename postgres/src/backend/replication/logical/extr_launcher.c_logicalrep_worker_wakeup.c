#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LogicalRepWorker ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  LogicalRepWorkerLock ; 
 int /*<<< orphan*/ * logicalrep_worker_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  logicalrep_worker_wakeup_ptr (int /*<<< orphan*/ *) ; 

void
logicalrep_worker_wakeup(Oid subid, Oid relid)
{
	LogicalRepWorker *worker;

	LWLockAcquire(LogicalRepWorkerLock, LW_SHARED);

	worker = logicalrep_worker_find(subid, relid, true);

	if (worker)
		logicalrep_worker_wakeup_ptr(worker);

	LWLockRelease(LogicalRepWorkerLock);
}
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

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LogicalRepWorkerLock ; 
 int /*<<< orphan*/  MyLogicalRepWorker ; 
 int /*<<< orphan*/  logicalrep_worker_cleanup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
logicalrep_worker_detach(void)
{
	/* Block concurrent access. */
	LWLockAcquire(LogicalRepWorkerLock, LW_EXCLUSIVE);

	logicalrep_worker_cleanup(MyLogicalRepWorker);

	LWLockRelease(LogicalRepWorkerLock);
}
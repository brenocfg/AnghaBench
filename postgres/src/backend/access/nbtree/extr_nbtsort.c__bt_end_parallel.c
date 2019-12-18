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
struct TYPE_3__ {int /*<<< orphan*/  pcxt; int /*<<< orphan*/  snapshot; } ;
typedef  TYPE_1__ BTLeader ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyParallelContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExitParallelMode () ; 
 scalar_t__ IsMVCCSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnregisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForParallelWorkersToFinish (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_bt_end_parallel(BTLeader *btleader)
{
	/* Shutdown worker processes */
	WaitForParallelWorkersToFinish(btleader->pcxt);
	/* Free last reference to MVCC snapshot, if one was used */
	if (IsMVCCSnapshot(btleader->snapshot))
		UnregisterSnapshot(btleader->snapshot);
	DestroyParallelContext(btleader->pcxt);
	ExitParallelMode();
}
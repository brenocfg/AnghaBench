#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_3__ {int /*<<< orphan*/  insertingAt; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ l; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockUpdateVar (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t MyLockNo ; 
 int NUM_XLOGINSERT_LOCKS ; 
 TYPE_2__* WALInsertLocks ; 
 scalar_t__ holdingAllLocks ; 

__attribute__((used)) static void
WALInsertLockUpdateInsertingAt(XLogRecPtr insertingAt)
{
	if (holdingAllLocks)
	{
		/*
		 * We use the last lock to mark our actual position, see comments in
		 * WALInsertLockAcquireExclusive.
		 */
		LWLockUpdateVar(&WALInsertLocks[NUM_XLOGINSERT_LOCKS - 1].l.lock,
						&WALInsertLocks[NUM_XLOGINSERT_LOCKS - 1].l.insertingAt,
						insertingAt);
	}
	else
		LWLockUpdateVar(&WALInsertLocks[MyLockNo].l.lock,
						&WALInsertLocks[MyLockNo].l.insertingAt,
						insertingAt);
}
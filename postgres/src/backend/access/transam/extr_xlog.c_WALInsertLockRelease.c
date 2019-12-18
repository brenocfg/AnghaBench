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
struct TYPE_3__ {int /*<<< orphan*/  insertingAt; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ l; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockReleaseClearVar (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t MyLockNo ; 
 int NUM_XLOGINSERT_LOCKS ; 
 TYPE_2__* WALInsertLocks ; 
 int holdingAllLocks ; 

__attribute__((used)) static void
WALInsertLockRelease(void)
{
	if (holdingAllLocks)
	{
		int			i;

		for (i = 0; i < NUM_XLOGINSERT_LOCKS; i++)
			LWLockReleaseClearVar(&WALInsertLocks[i].l.lock,
								  &WALInsertLocks[i].l.insertingAt,
								  0);

		holdingAllLocks = false;
	}
	else
	{
		LWLockReleaseClearVar(&WALInsertLocks[MyLockNo].l.lock,
							  &WALInsertLocks[MyLockNo].l.insertingAt,
							  0);
	}
}
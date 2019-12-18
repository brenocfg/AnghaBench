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
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_3__ {scalar_t__ lastImportantAt; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ l; } ;

/* Variables and functions */
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int NUM_XLOGINSERT_LOCKS ; 
 TYPE_2__* WALInsertLocks ; 

XLogRecPtr
GetLastImportantRecPtr(void)
{
	XLogRecPtr	res = InvalidXLogRecPtr;
	int			i;

	for (i = 0; i < NUM_XLOGINSERT_LOCKS; i++)
	{
		XLogRecPtr	last_important;

		/*
		 * Need to take a lock to prevent torn reads of the LSN, which are
		 * possible on some of the supported platforms. WAL insert locks only
		 * support exclusive mode, so we have to use that.
		 */
		LWLockAcquire(&WALInsertLocks[i].l.lock, LW_EXCLUSIVE);
		last_important = WALInsertLocks[i].l.lastImportantAt;
		LWLockRelease(&WALInsertLocks[i].l.lock);

		if (res < last_important)
			res = last_important;
	}

	return res;
}
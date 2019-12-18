#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  lockmode; int /*<<< orphan*/  locktag; } ;
struct TYPE_11__ {int /*<<< orphan*/  tag; } ;
struct TYPE_10__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  waitLockMode; TYPE_1__* waitLock; } ;
struct TYPE_9__ {int /*<<< orphan*/  tag; } ;
typedef  TYPE_2__ PGPROC ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_3__ LOCK ;
typedef  TYPE_4__ DEADLOCK_INFO ;

/* Variables and functions */
 TYPE_4__* deadlockDetails ; 
 int nDeadlockDetails ; 

void
RememberSimpleDeadLock(PGPROC *proc1,
					   LOCKMODE lockmode,
					   LOCK *lock,
					   PGPROC *proc2)
{
	DEADLOCK_INFO *info = &deadlockDetails[0];

	info->locktag = lock->tag;
	info->lockmode = lockmode;
	info->pid = proc1->pid;
	info++;
	info->locktag = proc2->waitLock->tag;
	info->lockmode = proc2->waitLockMode;
	info->pid = proc2->pid;
	nDeadlockDetails = 2;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * next; int /*<<< orphan*/ * prev; } ;
struct TYPE_9__ {int waitStatus; int /*<<< orphan*/  procLatch; int /*<<< orphan*/ * waitProcLock; TYPE_2__* waitLock; TYPE_4__ links; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
struct TYPE_8__ {TYPE_1__ waitProcs; } ;
typedef  TYPE_3__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  SHMQueueDelete (TYPE_4__*) ; 
 int STATUS_WAITING ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 

PGPROC *
ProcWakeup(PGPROC *proc, int waitStatus)
{
	PGPROC	   *retProc;

	/* Proc should be sleeping ... */
	if (proc->links.prev == NULL ||
		proc->links.next == NULL)
		return NULL;
	Assert(proc->waitStatus == STATUS_WAITING);

	/* Save next process before we zap the list link */
	retProc = (PGPROC *) proc->links.next;

	/* Remove process from wait queue */
	SHMQueueDelete(&(proc->links));
	(proc->waitLock->waitProcs.size)--;

	/* Clean up process' state and pass it the ok/fail signal */
	proc->waitLock = NULL;
	proc->waitProcLock = NULL;
	proc->waitStatus = waitStatus;

	/* And awaken it */
	SetLatch(&proc->procLatch);

	return retProc;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TransactionId ;
struct TYPE_9__ {int pid; } ;
struct TYPE_8__ {scalar_t__ xid; } ;
struct TYPE_7__ {int numProcs; int* pgprocnos; } ;
typedef  TYPE_1__ ProcArrayStruct ;
typedef  TYPE_2__ PGXACT ;
typedef  TYPE_3__ PGPROC ;

/* Variables and functions */
 scalar_t__ InvalidTransactionId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 TYPE_2__* allPgXact ; 
 TYPE_3__* allProcs ; 
 TYPE_1__* procArray ; 

int
BackendXidGetPid(TransactionId xid)
{
	int			result = 0;
	ProcArrayStruct *arrayP = procArray;
	int			index;

	if (xid == InvalidTransactionId)	/* never match invalid xid */
		return 0;

	LWLockAcquire(ProcArrayLock, LW_SHARED);

	for (index = 0; index < arrayP->numProcs; index++)
	{
		int			pgprocno = arrayP->pgprocnos[index];
		PGPROC	   *proc = &allProcs[pgprocno];
		PGXACT	   *pgxact = &allPgXact[pgprocno];

		if (pgxact->xid == xid)
		{
			result = proc->pid;
			break;
		}
	}

	LWLockRelease(ProcArrayLock);

	return result;
}
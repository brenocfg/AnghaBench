#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_11__ {TYPE_3__* allPgXact; } ;
struct TYPE_10__ {size_t pgprocno; } ;
struct TYPE_9__ {int /*<<< orphan*/  xmin; int /*<<< orphan*/  xid; } ;
struct TYPE_8__ {TYPE_4__* proc; } ;
struct TYPE_7__ {int lastBackend; TYPE_2__* procState; } ;
typedef  TYPE_1__ SISeg ;
typedef  TYPE_2__ ProcState ;
typedef  TYPE_3__ PGXACT ;
typedef  TYPE_4__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 TYPE_6__* ProcGlobal ; 
 int /*<<< orphan*/  SInvalWriteLock ; 
 TYPE_1__* shmInvalBuffer ; 

void
BackendIdGetTransactionIds(int backendID, TransactionId *xid, TransactionId *xmin)
{
	SISeg	   *segP = shmInvalBuffer;

	*xid = InvalidTransactionId;
	*xmin = InvalidTransactionId;

	/* Need to lock out additions/removals of backends */
	LWLockAcquire(SInvalWriteLock, LW_SHARED);

	if (backendID > 0 && backendID <= segP->lastBackend)
	{
		ProcState  *stateP = &segP->procState[backendID - 1];
		PGPROC	   *proc = stateP->proc;

		if (proc != NULL)
		{
			PGXACT	   *xact = &ProcGlobal->allPgXact[proc->pgprocno];

			*xid = xact->xid;
			*xmin = xact->xmin;
		}
	}

	LWLockRelease(SInvalWriteLock);
}
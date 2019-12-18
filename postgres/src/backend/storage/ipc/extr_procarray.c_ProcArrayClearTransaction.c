#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t pgprocno; int recoveryConflictPending; int /*<<< orphan*/  lxid; } ;
struct TYPE_5__ {int delayChkpt; int overflowed; scalar_t__ nxids; int /*<<< orphan*/  vacuumFlags; void* xmin; void* xid; } ;
typedef  TYPE_1__ PGXACT ;
typedef  TYPE_2__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidLocalTransactionId ; 
 void* InvalidTransactionId ; 
 int /*<<< orphan*/  PROC_VACUUM_STATE_MASK ; 
 TYPE_1__* allPgXact ; 

void
ProcArrayClearTransaction(PGPROC *proc)
{
	PGXACT	   *pgxact = &allPgXact[proc->pgprocno];

	/*
	 * We can skip locking ProcArrayLock here, because this action does not
	 * actually change anyone's view of the set of running XIDs: our entry is
	 * duplicate with the gxact that has already been inserted into the
	 * ProcArray.
	 */
	pgxact->xid = InvalidTransactionId;
	proc->lxid = InvalidLocalTransactionId;
	pgxact->xmin = InvalidTransactionId;
	proc->recoveryConflictPending = false;

	/* redundant, but just in case */
	pgxact->vacuumFlags &= ~PROC_VACUUM_STATE_MASK;
	pgxact->delayChkpt = false;

	/* Clear the subtransaction-XID cache too */
	pgxact->nxids = 0;
	pgxact->overflowed = false;
}
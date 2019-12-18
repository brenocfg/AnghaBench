#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_8__ {int /*<<< orphan*/  latestCompletedXid; } ;
struct TYPE_7__ {int recoveryConflictPending; int /*<<< orphan*/  lxid; } ;
struct TYPE_6__ {int delayChkpt; int overflowed; scalar_t__ nxids; int /*<<< orphan*/  vacuumFlags; void* xmin; void* xid; } ;
typedef  TYPE_1__ PGXACT ;
typedef  TYPE_2__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidLocalTransactionId ; 
 void* InvalidTransactionId ; 
 int /*<<< orphan*/  PROC_VACUUM_STATE_MASK ; 
 TYPE_3__* ShmemVariableCache ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ProcArrayEndTransactionInternal(PGPROC *proc, PGXACT *pgxact,
								TransactionId latestXid)
{
	pgxact->xid = InvalidTransactionId;
	proc->lxid = InvalidLocalTransactionId;
	pgxact->xmin = InvalidTransactionId;
	/* must be cleared with xid/xmin: */
	pgxact->vacuumFlags &= ~PROC_VACUUM_STATE_MASK;
	pgxact->delayChkpt = false; /* be sure this is cleared in abort */
	proc->recoveryConflictPending = false;

	/* Clear the subtransaction-XID cache too while holding the lock */
	pgxact->nxids = 0;
	pgxact->overflowed = false;

	/* Also advance global latestCompletedXid while holding the lock */
	if (TransactionIdPrecedes(ShmemVariableCache->latestCompletedXid,
							  latestXid))
		ShmemVariableCache->latestCompletedXid = latestXid;
}
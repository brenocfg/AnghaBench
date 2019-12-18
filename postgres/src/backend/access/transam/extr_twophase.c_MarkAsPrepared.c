#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * allProcs; } ;
struct TYPE_4__ {int valid; size_t pgprocno; } ;
typedef  TYPE_1__* GlobalTransaction ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  ProcArrayAdd (int /*<<< orphan*/ *) ; 
 TYPE_2__* ProcGlobal ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 

__attribute__((used)) static void
MarkAsPrepared(GlobalTransaction gxact, bool lock_held)
{
	/* Lock here may be overkill, but I'm not convinced of that ... */
	if (!lock_held)
		LWLockAcquire(TwoPhaseStateLock, LW_EXCLUSIVE);
	Assert(!gxact->valid);
	gxact->valid = true;
	if (!lock_held)
		LWLockRelease(TwoPhaseStateLock);

	/*
	 * Put it into the global ProcArray so TransactionIdIsInProgress considers
	 * the XID as still running.
	 */
	ProcArrayAdd(&ProcGlobal->allProcs[gxact->pgprocno]);
}
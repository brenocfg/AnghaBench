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
struct TYPE_5__ {int /*<<< orphan*/ * proc; } ;
struct TYPE_4__ {int lastBackend; TYPE_2__* procState; } ;
typedef  TYPE_1__ SISeg ;
typedef  TYPE_2__ ProcState ;
typedef  int /*<<< orphan*/  PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  SInvalWriteLock ; 
 TYPE_1__* shmInvalBuffer ; 

PGPROC *
BackendIdGetProc(int backendID)
{
	PGPROC	   *result = NULL;
	SISeg	   *segP = shmInvalBuffer;

	/* Need to lock out additions/removals of backends */
	LWLockAcquire(SInvalWriteLock, LW_SHARED);

	if (backendID > 0 && backendID <= segP->lastBackend)
	{
		ProcState  *stateP = &segP->procState[backendID - 1];

		result = stateP->proc;
	}

	LWLockRelease(SInvalWriteLock);

	return result;
}
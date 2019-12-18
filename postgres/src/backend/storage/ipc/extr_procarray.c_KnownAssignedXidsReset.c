#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ headKnownAssignedXids; scalar_t__ tailKnownAssignedXids; scalar_t__ numKnownAssignedXids; } ;
typedef  TYPE_1__ ProcArrayStruct ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 TYPE_1__* procArray ; 

__attribute__((used)) static void
KnownAssignedXidsReset(void)
{
	ProcArrayStruct *pArray = procArray;

	LWLockAcquire(ProcArrayLock, LW_EXCLUSIVE);

	pArray->numKnownAssignedXids = 0;
	pArray->tailKnownAssignedXids = 0;
	pArray->headKnownAssignedXids = 0;

	LWLockRelease(ProcArrayLock);
}
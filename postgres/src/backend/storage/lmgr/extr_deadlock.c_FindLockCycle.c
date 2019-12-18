#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PGPROC ;
typedef  int /*<<< orphan*/  EDGE ;

/* Variables and functions */
 int FindLockCycleRecurse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ nDeadlockDetails ; 
 scalar_t__ nVisitedProcs ; 

__attribute__((used)) static bool
FindLockCycle(PGPROC *checkProc,
			  EDGE *softEdges,	/* output argument */
			  int *nSoftEdges)	/* output argument */
{
	nVisitedProcs = 0;
	nDeadlockDetails = 0;
	*nSoftEdges = 0;
	return FindLockCycleRecurse(checkProc, 0, softEdges, nSoftEdges);
}
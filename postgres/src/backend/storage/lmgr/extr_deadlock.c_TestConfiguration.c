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
struct TYPE_3__ {int /*<<< orphan*/ * blocker; int /*<<< orphan*/ * waiter; } ;
typedef  int /*<<< orphan*/  PGPROC ;
typedef  int /*<<< orphan*/  EDGE ;

/* Variables and functions */
 int /*<<< orphan*/  ExpandConstraints (TYPE_1__*,int) ; 
 scalar_t__ FindLockCycle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int MaxBackends ; 
 TYPE_1__* curConstraints ; 
 int maxPossibleConstraints ; 
 int nCurConstraints ; 
 int nPossibleConstraints ; 
 int /*<<< orphan*/ * possibleConstraints ; 

__attribute__((used)) static int
TestConfiguration(PGPROC *startProc)
{
	int			softFound = 0;
	EDGE	   *softEdges = possibleConstraints + nPossibleConstraints;
	int			nSoftEdges;
	int			i;

	/*
	 * Make sure we have room for FindLockCycle's output.
	 */
	if (nPossibleConstraints + MaxBackends > maxPossibleConstraints)
		return -1;

	/*
	 * Expand current constraint set into wait orderings.  Fail if the
	 * constraint set is not self-consistent.
	 */
	if (!ExpandConstraints(curConstraints, nCurConstraints))
		return -1;

	/*
	 * Check for cycles involving startProc or any of the procs mentioned in
	 * constraints.  We check startProc last because if it has a soft cycle
	 * still to be dealt with, we want to deal with that first.
	 */
	for (i = 0; i < nCurConstraints; i++)
	{
		if (FindLockCycle(curConstraints[i].waiter, softEdges, &nSoftEdges))
		{
			if (nSoftEdges == 0)
				return -1;		/* hard deadlock detected */
			softFound = nSoftEdges;
		}
		if (FindLockCycle(curConstraints[i].blocker, softEdges, &nSoftEdges))
		{
			if (nSoftEdges == 0)
				return -1;		/* hard deadlock detected */
			softFound = nSoftEdges;
		}
	}
	if (FindLockCycle(startProc, softEdges, &nSoftEdges))
	{
		if (nSoftEdges == 0)
			return -1;			/* hard deadlock detected */
		softFound = nSoftEdges;
	}
	return softFound;
}
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

/* Variables and functions */
 int /*<<< orphan*/  FATAL ; 
 scalar_t__ MaxBackends ; 
 int TestConfiguration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curConstraints ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 size_t maxCurConstraints ; 
 scalar_t__ maxPossibleConstraints ; 
 size_t nCurConstraints ; 
 int nPossibleConstraints ; 
 int /*<<< orphan*/ * possibleConstraints ; 

__attribute__((used)) static bool
DeadLockCheckRecurse(PGPROC *proc)
{
	int			nEdges;
	int			oldPossibleConstraints;
	bool		savedList;
	int			i;

	nEdges = TestConfiguration(proc);
	if (nEdges < 0)
		return true;			/* hard deadlock --- no solution */
	if (nEdges == 0)
		return false;			/* good configuration found */
	if (nCurConstraints >= maxCurConstraints)
		return true;			/* out of room for active constraints? */
	oldPossibleConstraints = nPossibleConstraints;
	if (nPossibleConstraints + nEdges + MaxBackends <= maxPossibleConstraints)
	{
		/* We can save the edge list in possibleConstraints[] */
		nPossibleConstraints += nEdges;
		savedList = true;
	}
	else
	{
		/* Not room; will need to regenerate the edges on-the-fly */
		savedList = false;
	}

	/*
	 * Try each available soft edge as an addition to the configuration.
	 */
	for (i = 0; i < nEdges; i++)
	{
		if (!savedList && i > 0)
		{
			/* Regenerate the list of possible added constraints */
			if (nEdges != TestConfiguration(proc))
				elog(FATAL, "inconsistent results during deadlock check");
		}
		curConstraints[nCurConstraints] =
			possibleConstraints[oldPossibleConstraints + i];
		nCurConstraints++;
		if (!DeadLockCheckRecurse(proc))
			return false;		/* found a valid solution! */
		/* give up on that added constraint, try again */
		nCurConstraints--;
	}
	nPossibleConstraints = oldPossibleConstraints;
	return true;				/* no solution found */
}
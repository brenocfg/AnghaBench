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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 char const** LWLockTrancheArray ; 
 int LWLockTranchesAllocated ; 
 scalar_t__ repalloc (char const**,int) ; 

void
LWLockRegisterTranche(int tranche_id, const char *tranche_name)
{
	Assert(LWLockTrancheArray != NULL);

	if (tranche_id >= LWLockTranchesAllocated)
	{
		int			i = LWLockTranchesAllocated;
		int			j = LWLockTranchesAllocated;

		while (i <= tranche_id)
			i *= 2;

		LWLockTrancheArray = (const char **)
			repalloc(LWLockTrancheArray, i * sizeof(char *));
		LWLockTranchesAllocated = i;
		while (j < LWLockTranchesAllocated)
			LWLockTrancheArray[j++] = NULL;
	}

	LWLockTrancheArray[tranche_id] = tranche_name;
}
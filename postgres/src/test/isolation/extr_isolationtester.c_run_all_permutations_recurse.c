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
struct TYPE_6__ {int nsessions; TYPE_1__** sessions; } ;
typedef  TYPE_2__ TestSpec ;
struct TYPE_5__ {size_t nsteps; int /*<<< orphan*/ ** steps; } ;
typedef  int /*<<< orphan*/  Step ;

/* Variables and functions */
 size_t* piles ; 
 int /*<<< orphan*/  run_permutation (TYPE_2__*,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
run_all_permutations_recurse(TestSpec *testspec, int nsteps, Step **steps)
{
	int			i;
	int			found = 0;

	for (i = 0; i < testspec->nsessions; i++)
	{
		/* If there's any more steps in this pile, pick it and recurse */
		if (piles[i] < testspec->sessions[i]->nsteps)
		{
			steps[nsteps] = testspec->sessions[i]->steps[piles[i]];
			piles[i]++;

			run_all_permutations_recurse(testspec, nsteps + 1, steps);

			piles[i]--;

			found = 1;
		}
	}

	/* If all the piles were empty, this permutation is completed. Run it */
	if (!found)
		run_permutation(testspec, nsteps, steps);
}
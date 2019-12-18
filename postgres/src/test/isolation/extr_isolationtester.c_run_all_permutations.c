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
struct TYPE_5__ {scalar_t__ nsteps; } ;
typedef  int /*<<< orphan*/  Step ;

/* Variables and functions */
 void* pg_malloc (int) ; 
 scalar_t__* piles ; 
 int /*<<< orphan*/  run_all_permutations_recurse (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
run_all_permutations(TestSpec *testspec)
{
	int			nsteps;
	int			i;
	Step	  **steps;

	/* Count the total number of steps in all sessions */
	nsteps = 0;
	for (i = 0; i < testspec->nsessions; i++)
		nsteps += testspec->sessions[i]->nsteps;

	steps = pg_malloc(sizeof(Step *) * nsteps);

	/*
	 * To generate the permutations, we conceptually put the steps of each
	 * session on a pile. To generate a permutation, we pick steps from the
	 * piles until all piles are empty. By picking steps from piles in
	 * different order, we get different permutations.
	 *
	 * A pile is actually just an integer which tells how many steps we've
	 * already picked from this pile.
	 */
	piles = pg_malloc(sizeof(int) * testspec->nsessions);
	for (i = 0; i < testspec->nsessions; i++)
		piles[i] = 0;

	run_all_permutations_recurse(testspec, 0, steps);
}
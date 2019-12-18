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
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  scalar_t__ Gene ;

/* Variables and functions */
 int geqo_randint (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
init_tour(PlannerInfo *root, Gene *tour, int num_gene)
{
	int			i,
				j;

	/*
	 * We must fill the tour[] array with a random permutation of the numbers
	 * 1 .. num_gene.  We can do that in one pass using the "inside-out"
	 * variant of the Fisher-Yates shuffle algorithm.  Notionally, we append
	 * each new value to the array and then swap it with a randomly-chosen
	 * array element (possibly including itself, else we fail to generate
	 * permutations with the last city last).  The swap step can be optimized
	 * by combining it with the insertion.
	 */
	if (num_gene > 0)
		tour[0] = (Gene) 1;

	for (i = 1; i < num_gene; i++)
	{
		j = geqo_randint(root, i, 0);
		/* i != j check avoids fetching uninitialized array element */
		if (i != j)
			tour[i] = tour[j];
		tour[j] = (Gene) (i + 1);
	}
}
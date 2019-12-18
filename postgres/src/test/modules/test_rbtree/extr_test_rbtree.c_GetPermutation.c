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
 scalar_t__ palloc (int) ; 
 int random () ; 

__attribute__((used)) static int *
GetPermutation(int size)
{
	int		   *permutation;
	int			i;

	permutation = (int *) palloc(size * sizeof(int));

	permutation[0] = 0;

	/*
	 * This is the "inside-out" variant of the Fisher-Yates shuffle algorithm.
	 * Notionally, we append each new value to the array and then swap it with
	 * a randomly-chosen array element (possibly including itself, else we
	 * fail to generate permutations with the last integer last).  The swap
	 * step can be optimized by combining it with the insertion.
	 */
	for (i = 1; i < size; i++)
	{
		int			j = random() % (i + 1);

		if (j < i)				/* avoid fetching undefined data if j=i */
			permutation[i] = permutation[j];
		permutation[j] = i;
	}

	return permutation;
}
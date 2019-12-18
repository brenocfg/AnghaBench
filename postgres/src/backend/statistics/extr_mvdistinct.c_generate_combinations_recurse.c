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
struct TYPE_3__ {int k; int n; size_t current; int /*<<< orphan*/ * combinations; } ;
typedef  TYPE_1__ CombinationGenerator ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
generate_combinations_recurse(CombinationGenerator *state,
							  int index, int start, int *current)
{
	/* If we haven't filled all the elements, simply recurse. */
	if (index < state->k)
	{
		int			i;

		/*
		 * The values have to be in ascending order, so make sure we start
		 * with the value passed by parameter.
		 */

		for (i = start; i < state->n; i++)
		{
			current[index] = i;
			generate_combinations_recurse(state, (index + 1), (i + 1), current);
		}

		return;
	}
	else
	{
		/* we got a valid combination, add it to the array */
		memcpy(&state->combinations[(state->k * state->current)],
			   current, state->k * sizeof(int));
		state->current++;
	}
}
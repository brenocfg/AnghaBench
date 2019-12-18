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
struct TYPE_3__ {int k; scalar_t__ n; scalar_t__* dependencies; int ndependencies; } ;
typedef  TYPE_1__* DependencyGenerator ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ repalloc (scalar_t__*,int) ; 

__attribute__((used)) static void
generate_dependencies_recurse(DependencyGenerator state, int index,
							  AttrNumber start, AttrNumber *current)
{
	/*
	 * The generator handles the first (k-1) elements differently from the
	 * last element.
	 */
	if (index < (state->k - 1))
	{
		AttrNumber	i;

		/*
		 * The first (k-1) values have to be in ascending order, which we
		 * generate recursively.
		 */

		for (i = start; i < state->n; i++)
		{
			current[index] = i;
			generate_dependencies_recurse(state, (index + 1), (i + 1), current);
		}
	}
	else
	{
		int			i;

		/*
		 * the last element is the implied value, which does not respect the
		 * ascending order. We just need to check that the value is not in the
		 * first (k-1) elements.
		 */

		for (i = 0; i < state->n; i++)
		{
			int			j;
			bool		match = false;

			current[index] = i;

			for (j = 0; j < index; j++)
			{
				if (current[j] == i)
				{
					match = true;
					break;
				}
			}

			/*
			 * If the value is not found in the first part of the dependency,
			 * we're done.
			 */
			if (!match)
			{
				state->dependencies = (AttrNumber *) repalloc(state->dependencies,
															  state->k * (state->ndependencies + 1) * sizeof(AttrNumber));
				memcpy(&state->dependencies[(state->k * state->ndependencies)],
					   current, state->k * sizeof(AttrNumber));
				state->ndependencies++;
			}
		}
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ncombinations; int* combinations; int current; int k; int n; } ;
typedef  TYPE_1__ CombinationGenerator ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  generate_combinations (TYPE_1__*) ; 
 int n_choose_k (int,int) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static CombinationGenerator *
generator_init(int n, int k)
{
	CombinationGenerator *state;

	Assert((n >= k) && (k > 0));

	/* allocate the generator state as a single chunk of memory */
	state = (CombinationGenerator *) palloc(sizeof(CombinationGenerator));

	state->ncombinations = n_choose_k(n, k);

	/* pre-allocate space for all combinations */
	state->combinations = (int *) palloc(sizeof(int) * k * state->ncombinations);

	state->current = 0;
	state->k = k;
	state->n = n;

	/* now actually pre-generate all the combinations of K elements */
	generate_combinations(state);

	/* make sure we got the expected number of combinations */
	Assert(state->current == state->ncombinations);

	/* reset the number, so we start with the first one */
	state->current = 0;

	return state;
}
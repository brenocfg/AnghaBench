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
struct TYPE_4__ {int k; } ;
typedef  TYPE_1__ CombinationGenerator ;

/* Variables and functions */
 int /*<<< orphan*/  generate_combinations_recurse (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pfree (int*) ; 

__attribute__((used)) static void
generate_combinations(CombinationGenerator *state)
{
	int		   *current = (int *) palloc0(sizeof(int) * state->k);

	generate_combinations_recurse(state, 0, 0, current);

	pfree(current);
}
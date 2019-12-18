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
typedef  TYPE_1__* DependencyGenerator ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  generate_dependencies_recurse (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
generate_dependencies(DependencyGenerator state)
{
	AttrNumber *current = (AttrNumber *) palloc0(sizeof(AttrNumber) * state->k);

	generate_dependencies_recurse(state, 0, 0, current);

	pfree(current);
}
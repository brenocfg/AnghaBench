#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  constisnull; int /*<<< orphan*/  constvalue; } ;
struct TYPE_7__ {size_t next_elem; size_t num_elems; int /*<<< orphan*/  opexpr; int /*<<< orphan*/ * elem_nulls; TYPE_1__ constexpr; int /*<<< orphan*/ * elem_values; } ;
struct TYPE_6__ {scalar_t__ state; } ;
typedef  TYPE_2__* PredIterInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__ ArrayConstIterState ;

/* Variables and functions */

__attribute__((used)) static Node *
arrayconst_next_fn(PredIterInfo info)
{
	ArrayConstIterState *state = (ArrayConstIterState *) info->state;

	if (state->next_elem >= state->num_elems)
		return NULL;
	state->constexpr.constvalue = state->elem_values[state->next_elem];
	state->constexpr.constisnull = state->elem_nulls[state->next_elem];
	state->next_elem++;
	return (Node *) &(state->opexpr);
}
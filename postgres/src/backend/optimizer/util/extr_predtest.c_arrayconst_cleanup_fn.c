#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  args; } ;
struct TYPE_8__ {TYPE_1__ opexpr; struct TYPE_8__* elem_nulls; struct TYPE_8__* elem_values; } ;
struct TYPE_7__ {scalar_t__ state; } ;
typedef  TYPE_2__* PredIterInfo ;
typedef  TYPE_3__ ArrayConstIterState ;

/* Variables and functions */
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_3__*) ; 

__attribute__((used)) static void
arrayconst_cleanup_fn(PredIterInfo info)
{
	ArrayConstIterState *state = (ArrayConstIterState *) info->state;

	pfree(state->elem_values);
	pfree(state->elem_nulls);
	list_free(state->opexpr.args);
	pfree(state);
}
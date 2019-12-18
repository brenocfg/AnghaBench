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
struct TYPE_3__ {int current_set; int /*<<< orphan*/ * aggcontexts; int /*<<< orphan*/  curaggcontext; int /*<<< orphan*/  hashcontext; } ;
typedef  TYPE_1__ AggState ;

/* Variables and functions */

__attribute__((used)) static void
select_current_set(AggState *aggstate, int setno, bool is_hash)
{
	/* when changing this, also adapt ExecInterpExpr() and friends */
	if (is_hash)
		aggstate->curaggcontext = aggstate->hashcontext;
	else
		aggstate->curaggcontext = aggstate->aggcontexts[setno];

	aggstate->current_set = setno;
}
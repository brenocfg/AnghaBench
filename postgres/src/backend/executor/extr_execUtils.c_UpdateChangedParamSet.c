#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  chgParam; TYPE_1__* plan; } ;
struct TYPE_4__ {int /*<<< orphan*/  allParam; } ;
typedef  TYPE_2__ PlanState ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bms_intersect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
UpdateChangedParamSet(PlanState *node, Bitmapset *newchg)
{
	Bitmapset  *parmset;

	/*
	 * The plan node only depends on params listed in its allParam set. Don't
	 * include anything else into its chgParam set.
	 */
	parmset = bms_intersect(node->plan->allParam, newchg);

	/*
	 * Keep node->chgParam == NULL if there's not actually any members; this
	 * allows the simplest possible tests in executor node files.
	 */
	if (!bms_is_empty(parmset))
		node->chgParam = bms_join(node->chgParam, parmset);
	else
		bms_free(parmset);
}
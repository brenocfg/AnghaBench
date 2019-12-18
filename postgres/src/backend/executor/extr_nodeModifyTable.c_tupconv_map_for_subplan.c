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
typedef  int /*<<< orphan*/  TupleConversionMap ;
struct TYPE_4__ {int mt_nplans; int /*<<< orphan*/ ** mt_per_subplan_tupconv_maps; } ;
typedef  TYPE_1__ ModifyTableState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ExecSetupChildParentMapForSubplan (TYPE_1__*) ; 

__attribute__((used)) static TupleConversionMap *
tupconv_map_for_subplan(ModifyTableState *mtstate, int whichplan)
{
	/* If nobody else set the per-subplan array of maps, do so ourselves. */
	if (mtstate->mt_per_subplan_tupconv_maps == NULL)
		ExecSetupChildParentMapForSubplan(mtstate);

	Assert(whichplan >= 0 && whichplan < mtstate->mt_nplans);
	return mtstate->mt_per_subplan_tupconv_maps[whichplan];
}
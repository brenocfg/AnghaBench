#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  TupleConversionMap ;
struct TYPE_7__ {int mt_nplans; int /*<<< orphan*/ ** mt_per_subplan_tupconv_maps; TYPE_1__* resultRelInfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  ri_RelationDesc; } ;
typedef  TYPE_1__ ResultRelInfo ;
typedef  TYPE_2__ ModifyTableState ;

/* Variables and functions */
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * convert_tuples_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* getTargetResultRelInfo (TYPE_2__*) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
ExecSetupChildParentMapForSubplan(ModifyTableState *mtstate)
{
	ResultRelInfo *targetRelInfo = getTargetResultRelInfo(mtstate);
	ResultRelInfo *resultRelInfos = mtstate->resultRelInfo;
	TupleDesc	outdesc;
	int			numResultRelInfos = mtstate->mt_nplans;
	int			i;

	/*
	 * Build array of conversion maps from each child's TupleDesc to the one
	 * used in the target relation.  The map pointers may be NULL when no
	 * conversion is necessary, which is hopefully a common case.
	 */

	/* Get tuple descriptor of the target rel. */
	outdesc = RelationGetDescr(targetRelInfo->ri_RelationDesc);

	mtstate->mt_per_subplan_tupconv_maps = (TupleConversionMap **)
		palloc(sizeof(TupleConversionMap *) * numResultRelInfos);

	for (i = 0; i < numResultRelInfos; ++i)
	{
		mtstate->mt_per_subplan_tupconv_maps[i] =
			convert_tuples_by_name(RelationGetDescr(resultRelInfos[i].ri_RelationDesc),
								   outdesc);
	}
}
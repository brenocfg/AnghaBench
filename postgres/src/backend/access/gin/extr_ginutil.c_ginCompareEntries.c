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
struct TYPE_3__ {int /*<<< orphan*/ * supportCollation; int /*<<< orphan*/ * compareFn; } ;
typedef  int OffsetNumber ;
typedef  TYPE_1__ GinState ;
typedef  scalar_t__ GinNullCategory ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GIN_CAT_NORM_KEY ; 

int
ginCompareEntries(GinState *ginstate, OffsetNumber attnum,
				  Datum a, GinNullCategory categorya,
				  Datum b, GinNullCategory categoryb)
{
	/* if not of same null category, sort by that first */
	if (categorya != categoryb)
		return (categorya < categoryb) ? -1 : 1;

	/* all null items in same category are equal */
	if (categorya != GIN_CAT_NORM_KEY)
		return 0;

	/* both not null, so safe to call the compareFn */
	return DatumGetInt32(FunctionCall2Coll(&ginstate->compareFn[attnum - 1],
										   ginstate->supportCollation[attnum - 1],
										   a, b));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * tupdesc; int /*<<< orphan*/  origTupdesc; scalar_t__ oneCol; } ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_1__ GinState ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  FirstOffsetNumber ; 
 int /*<<< orphan*/  GIN_CAT_NORM_KEY ; 
 int /*<<< orphan*/  GinGetNullCategory (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  OffsetNumberNext (int /*<<< orphan*/ ) ; 
 int gintuple_get_attrnum (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

Datum
gintuple_get_key(GinState *ginstate, IndexTuple tuple,
				 GinNullCategory *category)
{
	Datum		res;
	bool		isnull;

	if (ginstate->oneCol)
	{
		/*
		 * Single column index doesn't store attribute numbers in tuples
		 */
		res = index_getattr(tuple, FirstOffsetNumber, ginstate->origTupdesc,
							&isnull);
	}
	else
	{
		/*
		 * Since the datum type depends on which index column it's from, we
		 * must be careful to use the right tuple descriptor here.
		 */
		OffsetNumber colN = gintuple_get_attrnum(ginstate, tuple);

		res = index_getattr(tuple, OffsetNumberNext(FirstOffsetNumber),
							ginstate->tupdesc[colN - 1],
							&isnull);
	}

	if (isnull)
		*category = GinGetNullCategory(tuple, ginstate);
	else
		*category = GIN_CAT_NORM_KEY;

	return res;
}
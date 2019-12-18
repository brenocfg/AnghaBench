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
struct TYPE_5__ {TYPE_1__* origTupdesc; int /*<<< orphan*/ * tupdesc; scalar_t__ oneCol; } ;
struct TYPE_4__ {scalar_t__ natts; } ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_2__ GinState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetUInt16 (int /*<<< orphan*/ ) ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  index_getattr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*) ; 

OffsetNumber
gintuple_get_attrnum(GinState *ginstate, IndexTuple tuple)
{
	OffsetNumber colN;

	if (ginstate->oneCol)
	{
		/* column number is not stored explicitly */
		colN = FirstOffsetNumber;
	}
	else
	{
		Datum		res;
		bool		isnull;

		/*
		 * First attribute is always int16, so we can safely use any tuple
		 * descriptor to obtain first attribute of tuple
		 */
		res = index_getattr(tuple, FirstOffsetNumber, ginstate->tupdesc[0],
							&isnull);
		Assert(!isnull);

		colN = DatumGetUInt16(res);
		Assert(colN >= FirstOffsetNumber && colN <= ginstate->origTupdesc->natts);
	}

	return colN;
}
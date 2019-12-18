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
typedef  scalar_t__ int32 ;
struct TYPE_3__ {int ndatums; int /*<<< orphan*/ ** datums; } ;
typedef  TYPE_1__* PartitionBoundInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
partition_list_bsearch(FmgrInfo *partsupfunc, Oid *partcollation,
					   PartitionBoundInfo boundinfo,
					   Datum value, bool *is_equal)
{
	int			lo,
				hi,
				mid;

	lo = -1;
	hi = boundinfo->ndatums - 1;
	while (lo < hi)
	{
		int32		cmpval;

		mid = (lo + hi + 1) / 2;
		cmpval = DatumGetInt32(FunctionCall2Coll(&partsupfunc[0],
												 partcollation[0],
												 boundinfo->datums[mid][0],
												 value));
		if (cmpval <= 0)
		{
			lo = mid;
			*is_equal = (cmpval == 0);
			if (*is_equal)
				break;
		}
		else
			hi = mid - 1;
	}

	return lo;
}
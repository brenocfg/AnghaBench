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

/* Variables and functions */
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ partition_hbound_cmp (scalar_t__,scalar_t__,int,int) ; 

int
partition_hash_bsearch(PartitionBoundInfo boundinfo,
					   int modulus, int remainder)
{
	int			lo,
				hi,
				mid;

	lo = -1;
	hi = boundinfo->ndatums - 1;
	while (lo < hi)
	{
		int32		cmpval,
					bound_modulus,
					bound_remainder;

		mid = (lo + hi + 1) / 2;
		bound_modulus = DatumGetInt32(boundinfo->datums[mid][0]);
		bound_remainder = DatumGetInt32(boundinfo->datums[mid][1]);
		cmpval = partition_hbound_cmp(bound_modulus, bound_remainder,
									  modulus, remainder);
		if (cmpval <= 0)
		{
			lo = mid;

			if (cmpval == 0)
				break;
		}
		else
			hi = mid - 1;
	}

	return lo;
}
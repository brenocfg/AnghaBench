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
typedef  scalar_t__ int32 ;
struct TYPE_6__ {int /*<<< orphan*/  rng_collation; int /*<<< orphan*/  rng_cmp_proc_finfo; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_7__ {scalar_t__ lower; int /*<<< orphan*/  inclusive; int /*<<< orphan*/  val; scalar_t__ infinite; } ;
typedef  TYPE_2__ RangeBound ;

/* Variables and functions */
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
range_cmp_bounds(TypeCacheEntry *typcache, const RangeBound *b1, const RangeBound *b2)
{
	int32		result;

	/*
	 * First, handle cases involving infinity, which don't require invoking
	 * the comparison proc.
	 */
	if (b1->infinite && b2->infinite)
	{
		/*
		 * Both are infinity, so they are equal unless one is lower and the
		 * other not.
		 */
		if (b1->lower == b2->lower)
			return 0;
		else
			return b1->lower ? -1 : 1;
	}
	else if (b1->infinite)
		return b1->lower ? -1 : 1;
	else if (b2->infinite)
		return b2->lower ? 1 : -1;

	/*
	 * Both boundaries are finite, so compare the held values.
	 */
	result = DatumGetInt32(FunctionCall2Coll(&typcache->rng_cmp_proc_finfo,
											 typcache->rng_collation,
											 b1->val, b2->val));

	/*
	 * If the comparison is anything other than equal, we're done. If they
	 * compare equal though, we still have to consider whether the boundaries
	 * are inclusive or exclusive.
	 */
	if (result == 0)
	{
		if (!b1->inclusive && !b2->inclusive)
		{
			/* both are exclusive */
			if (b1->lower == b2->lower)
				return 0;
			else
				return b1->lower ? 1 : -1;
		}
		else if (!b1->inclusive)
			return b1->lower ? 1 : -1;
		else if (!b2->inclusive)
			return b2->lower ? -1 : 1;
		else
		{
			/*
			 * Both are inclusive and the values held are equal, so they are
			 * equal regardless of whether they are upper or lower boundaries,
			 * or a mix.
			 */
			return 0;
		}
	}

	return result;
}
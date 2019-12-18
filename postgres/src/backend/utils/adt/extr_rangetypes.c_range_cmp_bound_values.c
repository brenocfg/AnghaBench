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
struct TYPE_6__ {int /*<<< orphan*/  rng_collation; int /*<<< orphan*/  rng_cmp_proc_finfo; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_7__ {scalar_t__ lower; int /*<<< orphan*/  val; scalar_t__ infinite; } ;
typedef  TYPE_2__ RangeBound ;

/* Variables and functions */
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
range_cmp_bound_values(TypeCacheEntry *typcache, const RangeBound *b1,
					   const RangeBound *b2)
{
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
	return DatumGetInt32(FunctionCall2Coll(&typcache->rng_cmp_proc_finfo,
										   typcache->rng_collation,
										   b1->val, b2->val));
}
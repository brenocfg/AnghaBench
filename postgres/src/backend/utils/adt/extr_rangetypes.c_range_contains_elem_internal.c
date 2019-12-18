#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_7__ {int /*<<< orphan*/  rng_collation; int /*<<< orphan*/  rng_cmp_proc_finfo; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_8__ {int /*<<< orphan*/  inclusive; int /*<<< orphan*/  val; int /*<<< orphan*/  infinite; } ;
typedef  int /*<<< orphan*/  RangeType ;
typedef  TYPE_2__ RangeBound ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_deserialize (TYPE_1__*,int /*<<< orphan*/  const*,TYPE_2__*,TYPE_2__*,int*) ; 

bool
range_contains_elem_internal(TypeCacheEntry *typcache, const RangeType *r, Datum val)
{
	RangeBound	lower;
	RangeBound	upper;
	bool		empty;
	int32		cmp;

	range_deserialize(typcache, r, &lower, &upper, &empty);

	if (empty)
		return false;

	if (!lower.infinite)
	{
		cmp = DatumGetInt32(FunctionCall2Coll(&typcache->rng_cmp_proc_finfo,
											  typcache->rng_collation,
											  lower.val, val));
		if (cmp > 0)
			return false;
		if (cmp == 0 && !lower.inclusive)
			return false;
	}

	if (!upper.infinite)
	{
		cmp = DatumGetInt32(FunctionCall2Coll(&typcache->rng_cmp_proc_finfo,
											  typcache->rng_collation,
											  upper.val, val));
		if (cmp < 0)
			return false;
		if (cmp == 0 && !upper.inclusive)
			return false;
	}

	return true;
}
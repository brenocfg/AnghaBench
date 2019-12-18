#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_14__ {TYPE_1__ rng_canonical_finfo; } ;
typedef  TYPE_2__ TypeCacheEntry ;
struct TYPE_15__ {int lower; int inclusive; } ;
typedef  int /*<<< orphan*/  RangeType ;
typedef  TYPE_3__ RangeBound ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int RangeIsEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_range (TYPE_2__*,TYPE_3__*,TYPE_3__*,int) ; 
 int range_cmp_bound_values (TYPE_2__*,TYPE_3__*,TYPE_3__*) ; 

bool
bounds_adjacent(TypeCacheEntry *typcache, RangeBound boundA, RangeBound boundB)
{
	int			cmp;

	Assert(!boundA.lower && boundB.lower);

	cmp = range_cmp_bound_values(typcache, &boundA, &boundB);
	if (cmp < 0)
	{
		RangeType  *r;

		/*
		 * Bounds do not overlap; see if there are points in between.
		 */

		/* in a continuous subtype, there are assumed to be points between */
		if (!OidIsValid(typcache->rng_canonical_finfo.fn_oid))
			return false;

		/*
		 * The bounds are of a discrete range type; so make a range A..B and
		 * see if it's empty.
		 */

		/* flip the inclusion flags */
		boundA.inclusive = !boundA.inclusive;
		boundB.inclusive = !boundB.inclusive;
		/* change upper/lower labels to avoid Assert failures */
		boundA.lower = true;
		boundB.lower = false;
		r = make_range(typcache, &boundA, &boundB, false);
		return RangeIsEmpty(r);
	}
	else if (cmp == 0)
		return boundA.inclusive != boundB.inclusive;
	else
		return false;			/* bounds overlap */
}
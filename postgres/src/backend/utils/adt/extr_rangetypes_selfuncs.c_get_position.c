#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  double float8 ;
struct TYPE_10__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_8__ {int /*<<< orphan*/  rng_collation; TYPE_7__ rng_subdiff_finfo; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_9__ {scalar_t__ lower; scalar_t__ infinite; int /*<<< orphan*/  val; } ;
typedef  TYPE_2__ RangeBound ;

/* Variables and functions */
 double DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double Max (double,double) ; 
 double Min (double,double) ; 
 int OidIsValid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static float8
get_position(TypeCacheEntry *typcache, const RangeBound *value, const RangeBound *hist1,
			 const RangeBound *hist2)
{
	bool		has_subdiff = OidIsValid(typcache->rng_subdiff_finfo.fn_oid);
	float8		position;

	if (!hist1->infinite && !hist2->infinite)
	{
		float8		bin_width;

		/*
		 * Both bounds are finite. Assuming the subtype's comparison function
		 * works sanely, the value must be finite, too, because it lies
		 * somewhere between the bounds. If it doesn't, just return something.
		 */
		if (value->infinite)
			return 0.5;

		/* Can't interpolate without subdiff function */
		if (!has_subdiff)
			return 0.5;

		/* Calculate relative position using subdiff function. */
		bin_width = DatumGetFloat8(FunctionCall2Coll(
													 &typcache->rng_subdiff_finfo,
													 typcache->rng_collation,
													 hist2->val,
													 hist1->val));
		if (bin_width <= 0.0)
			return 0.5;			/* zero width bin */

		position = DatumGetFloat8(FunctionCall2Coll(
													&typcache->rng_subdiff_finfo,
													typcache->rng_collation,
													value->val,
													hist1->val))
			/ bin_width;

		/* Relative position must be in [0,1] range */
		position = Max(position, 0.0);
		position = Min(position, 1.0);
		return position;
	}
	else if (hist1->infinite && !hist2->infinite)
	{
		/*
		 * Lower bin boundary is -infinite, upper is finite. If the value is
		 * -infinite, return 0.0 to indicate it's equal to the lower bound.
		 * Otherwise return 1.0 to indicate it's infinitely far from the lower
		 * bound.
		 */
		return ((value->infinite && value->lower) ? 0.0 : 1.0);
	}
	else if (!hist1->infinite && hist2->infinite)
	{
		/* same as above, but in reverse */
		return ((value->infinite && !value->lower) ? 1.0 : 0.0);
	}
	else
	{
		/*
		 * If both bin boundaries are infinite, they should be equal to each
		 * other, and the value should also be infinite and equal to both
		 * bounds. (But don't Assert that, to avoid crashing if a user creates
		 * a datatype with a broken comparison function).
		 *
		 * Assume the value to lie in the middle of the infinite bounds.
		 */
		return 0.5;
	}
}
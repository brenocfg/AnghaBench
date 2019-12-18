#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  double float8 ;
struct TYPE_9__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_7__ {int /*<<< orphan*/  rng_collation; TYPE_6__ rng_subdiff_finfo; } ;
typedef  TYPE_1__ TypeCacheEntry ;
struct TYPE_8__ {scalar_t__ lower; scalar_t__ infinite; int /*<<< orphan*/  val; } ;
typedef  TYPE_2__ RangeBound ;

/* Variables and functions */
 double DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OidIsValid (int /*<<< orphan*/ ) ; 
 double get_float8_infinity () ; 

__attribute__((used)) static float8
get_distance(TypeCacheEntry *typcache, const RangeBound *bound1, const RangeBound *bound2)
{
	bool		has_subdiff = OidIsValid(typcache->rng_subdiff_finfo.fn_oid);

	if (!bound1->infinite && !bound2->infinite)
	{
		/*
		 * No bounds are infinite, use subdiff function or return default
		 * value of 1.0 if no subdiff is available.
		 */
		if (has_subdiff)
			return
				DatumGetFloat8(FunctionCall2Coll(&typcache->rng_subdiff_finfo,
												 typcache->rng_collation,
												 bound2->val,
												 bound1->val));
		else
			return 1.0;
	}
	else if (bound1->infinite && bound2->infinite)
	{
		/* Both bounds are infinite */
		if (bound1->lower == bound2->lower)
			return 0.0;
		else
			return get_float8_infinity();
	}
	else
	{
		/* One bound is infinite, another is not */
		return get_float8_infinity();
	}
}
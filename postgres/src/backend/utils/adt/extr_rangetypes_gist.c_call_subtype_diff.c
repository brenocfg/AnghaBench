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
typedef  double float8 ;
struct TYPE_3__ {int /*<<< orphan*/  rng_collation; int /*<<< orphan*/  rng_subdiff_finfo; } ;
typedef  TYPE_1__ TypeCacheEntry ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 double DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float8
call_subtype_diff(TypeCacheEntry *typcache, Datum val1, Datum val2)
{
	float8		value;

	value = DatumGetFloat8(FunctionCall2Coll(&typcache->rng_subdiff_finfo,
											 typcache->rng_collation,
											 val1, val2));
	/* Cope with buggy subtype_diff function by returning zero */
	if (value >= 0.0)
		return value;
	return 0.0;
}
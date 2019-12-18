#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeCacheEntry ;
struct TYPE_4__ {int infinite; int inclusive; int lower; void* val; } ;
typedef  int /*<<< orphan*/  RangeType ;
typedef  TYPE_1__ RangeBound ;
typedef  void* Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * make_range (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 

RangeType *
make_empty_range(TypeCacheEntry *typcache)
{
	RangeBound	lower;
	RangeBound	upper;

	lower.val = (Datum) 0;
	lower.infinite = false;
	lower.inclusive = false;
	lower.lower = true;

	upper.val = (Datum) 0;
	upper.infinite = false;
	upper.inclusive = false;
	upper.lower = false;

	return make_range(typcache, &lower, &upper, true);
}
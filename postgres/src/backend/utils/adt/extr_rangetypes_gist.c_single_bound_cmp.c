#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeCacheEntry ;
struct TYPE_2__ {int /*<<< orphan*/  bound; } ;
typedef  TYPE_1__ SingleBoundSortItem ;

/* Variables and functions */
 int range_cmp_bounds (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
single_bound_cmp(const void *a, const void *b, void *arg)
{
	SingleBoundSortItem *i1 = (SingleBoundSortItem *) a;
	SingleBoundSortItem *i2 = (SingleBoundSortItem *) b;
	TypeCacheEntry *typcache = (TypeCacheEntry *) arg;

	return range_cmp_bounds(typcache, &i1->bound, &i2->bound);
}
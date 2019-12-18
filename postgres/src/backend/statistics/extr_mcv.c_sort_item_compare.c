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
struct TYPE_2__ {int /*<<< orphan*/ * isnull; int /*<<< orphan*/ * values; } ;
typedef  int /*<<< orphan*/  SortSupport ;
typedef  TYPE_1__ SortItem ;

/* Variables and functions */
 int ApplySortComparator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sort_item_compare(const void *a, const void *b, void *arg)
{
	SortSupport	ssup = (SortSupport) arg;
	SortItem   *ia = (SortItem *) a;
	SortItem   *ib = (SortItem *) b;

	return ApplySortComparator(ia->values[0], ia->isnull[0],
							   ib->values[0], ib->isnull[0],
							   ssup);
}
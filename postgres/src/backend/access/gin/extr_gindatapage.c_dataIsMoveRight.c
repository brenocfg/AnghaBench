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
struct TYPE_3__ {int /*<<< orphan*/  itemptr; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  TYPE_1__* GinBtree ;

/* Variables and functions */
 int /*<<< orphan*/  GinDataPageGetRightBound (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageRightMost (int /*<<< orphan*/ ) ; 
 scalar_t__ ginCompareItemPointers (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
dataIsMoveRight(GinBtree btree, Page page)
{
	ItemPointer iptr = GinDataPageGetRightBound(page);

	if (GinPageRightMost(page))
		return false;

	return (ginCompareItemPointers(&btree->itemptr, iptr) > 0) ? true : false;
}
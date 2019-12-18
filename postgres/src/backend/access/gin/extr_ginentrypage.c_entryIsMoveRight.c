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
struct TYPE_3__ {int /*<<< orphan*/  entryCategory; int /*<<< orphan*/  entryKey; int /*<<< orphan*/  entryAttnum; int /*<<< orphan*/  ginstate; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  TYPE_1__* GinBtree ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ GinPageRightMost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getRightMostTuple (int /*<<< orphan*/ ) ; 
 scalar_t__ ginCompareAttEntries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gintuple_get_attrnum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gintuple_get_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
entryIsMoveRight(GinBtree btree, Page page)
{
	IndexTuple	itup;
	OffsetNumber attnum;
	Datum		key;
	GinNullCategory category;

	if (GinPageRightMost(page))
		return false;

	itup = getRightMostTuple(page);
	attnum = gintuple_get_attrnum(btree->ginstate, itup);
	key = gintuple_get_key(btree->ginstate, itup, &category);

	if (ginCompareAttEntries(btree->ginstate,
							 btree->entryAttnum, btree->entryKey, btree->entryCategory,
							 attnum, key, category) > 0)
		return true;

	return false;
}
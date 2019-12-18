#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Item ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  GinBtree ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GinFormInteriorTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexTupleSize (scalar_t__) ; 
 scalar_t__ InvalidOffsetNumber ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getRightMostTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 

void
ginEntryFillRoot(GinBtree btree, Page root,
				 BlockNumber lblkno, Page lpage,
				 BlockNumber rblkno, Page rpage)
{
	IndexTuple	itup;

	itup = GinFormInteriorTuple(getRightMostTuple(lpage), lpage, lblkno);
	if (PageAddItem(root, (Item) itup, IndexTupleSize(itup), InvalidOffsetNumber, false, false) == InvalidOffsetNumber)
		elog(ERROR, "failed to add item to index root page");
	pfree(itup);

	itup = GinFormInteriorTuple(getRightMostTuple(rpage), rpage, rblkno);
	if (PageAddItem(root, (Item) itup, IndexTupleSize(itup), InvalidOffsetNumber, false, false) == InvalidOffsetNumber)
		elog(ERROR, "failed to add item to index root page");
	pfree(itup);
}
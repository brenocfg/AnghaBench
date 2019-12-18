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
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  GinBtree ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GinGetDownlink (scalar_t__) ; 
 int /*<<< orphan*/  GinPageIsData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BlockNumber
entryGetLeftMostPage(GinBtree btree, Page page)
{
	IndexTuple	itup;

	Assert(!GinPageIsLeaf(page));
	Assert(!GinPageIsData(page));
	Assert(PageGetMaxOffsetNumber(page) >= FirstOffsetNumber);

	itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, FirstOffsetNumber));
	return GinGetDownlink(itup);
}
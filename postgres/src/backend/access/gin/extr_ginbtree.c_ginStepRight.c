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
struct TYPE_2__ {int /*<<< orphan*/  rightlink; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int GinPageIsData (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageIsDeleted (int /*<<< orphan*/ ) ; 
 int GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

Buffer
ginStepRight(Buffer buffer, Relation index, int lockmode)
{
	Buffer		nextbuffer;
	Page		page = BufferGetPage(buffer);
	bool		isLeaf = GinPageIsLeaf(page);
	bool		isData = GinPageIsData(page);
	BlockNumber blkno = GinPageGetOpaque(page)->rightlink;

	nextbuffer = ReadBuffer(index, blkno);
	LockBuffer(nextbuffer, lockmode);
	UnlockReleaseBuffer(buffer);

	/* Sanity check that the page we stepped to is of similar kind. */
	page = BufferGetPage(nextbuffer);
	if (isLeaf != GinPageIsLeaf(page) || isData != GinPageIsData(page))
		elog(ERROR, "right sibling of GIN page is of different type");

	/*
	 * Given the proper lock sequence above, we should never land on a deleted
	 * page.
	 */
	if (GinPageIsDeleted(page))
		elog(ERROR, "right sibling of GIN page was deleted");

	return nextbuffer;
}
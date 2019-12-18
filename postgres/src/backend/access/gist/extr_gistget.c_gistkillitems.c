#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ curBlkno; scalar_t__ curPageLSN; int numKilled; int /*<<< orphan*/ * killedItems; } ;
struct TYPE_4__ {int /*<<< orphan*/  indexRelation; int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__* GISTScanOpaque ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferGetLSNAtomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIST_SHARE ; 
 int /*<<< orphan*/  GistMarkPageHasGarbage (int /*<<< orphan*/ ) ; 
 int GistPageIsLeaf (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  ItemIdMarkDead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirtyHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRecPtrIsInvalid (scalar_t__) ; 
 int /*<<< orphan*/  gistcheckpage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gistkillitems(IndexScanDesc scan)
{
	GISTScanOpaque so = (GISTScanOpaque) scan->opaque;
	Buffer		buffer;
	Page		page;
	OffsetNumber offnum;
	ItemId		iid;
	int			i;
	bool		killedsomething = false;

	Assert(so->curBlkno != InvalidBlockNumber);
	Assert(!XLogRecPtrIsInvalid(so->curPageLSN));
	Assert(so->killedItems != NULL);

	buffer = ReadBuffer(scan->indexRelation, so->curBlkno);
	if (!BufferIsValid(buffer))
		return;

	LockBuffer(buffer, GIST_SHARE);
	gistcheckpage(scan->indexRelation, buffer);
	page = BufferGetPage(buffer);

	/*
	 * If page LSN differs it means that the page was modified since the last
	 * read. killedItems could be not valid so LP_DEAD hints applying is not
	 * safe.
	 */
	if (BufferGetLSNAtomic(buffer) != so->curPageLSN)
	{
		UnlockReleaseBuffer(buffer);
		so->numKilled = 0;		/* reset counter */
		return;
	}

	Assert(GistPageIsLeaf(page));

	/*
	 * Mark all killedItems as dead. We need no additional recheck, because,
	 * if page was modified, curPageLSN must have changed.
	 */
	for (i = 0; i < so->numKilled; i++)
	{
		offnum = so->killedItems[i];
		iid = PageGetItemId(page, offnum);
		ItemIdMarkDead(iid);
		killedsomething = true;
	}

	if (killedsomething)
	{
		GistMarkPageHasGarbage(page);
		MarkBufferDirtyHint(buffer, true);
	}

	UnlockReleaseBuffer(buffer);

	/*
	 * Always reset the scan state, so we don't look for same items on other
	 * pages.
	 */
	so->numKilled = 0;
}
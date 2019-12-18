#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  downlinkoffnum; int /*<<< orphan*/  page; int /*<<< orphan*/  blkno; } ;
struct TYPE_13__ {int /*<<< orphan*/  r; TYPE_3__* stack; } ;
struct TYPE_12__ {int /*<<< orphan*/  downlink; int /*<<< orphan*/  buf; } ;
struct TYPE_11__ {int /*<<< orphan*/  rightlink; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  int /*<<< orphan*/  GISTSTATE ;
typedef  TYPE_1__ GISTPageSplitInfo ;
typedef  TYPE_2__ GISTInsertState ;
typedef  TYPE_3__ GISTInsertStack ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIST_EXCLUSIVE ; 
 scalar_t__ GistFollowRight (int /*<<< orphan*/ ) ; 
 TYPE_10__* GistPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ OffsetNumberIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistfinishsplit (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gistformdownlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* palloc (int) ; 

__attribute__((used)) static void
gistfixsplit(GISTInsertState *state, GISTSTATE *giststate)
{
	GISTInsertStack *stack = state->stack;
	Buffer		buf;
	Page		page;
	List	   *splitinfo = NIL;

	elog(LOG, "fixing incomplete split in index \"%s\", block %u",
		 RelationGetRelationName(state->r), stack->blkno);

	Assert(GistFollowRight(stack->page));
	Assert(OffsetNumberIsValid(stack->downlinkoffnum));

	buf = stack->buffer;

	/*
	 * Read the chain of split pages, following the rightlinks. Construct a
	 * downlink tuple for each page.
	 */
	for (;;)
	{
		GISTPageSplitInfo *si = palloc(sizeof(GISTPageSplitInfo));
		IndexTuple	downlink;

		page = BufferGetPage(buf);

		/* Form the new downlink tuples to insert to parent */
		downlink = gistformdownlink(state->r, buf, giststate, stack);

		si->buf = buf;
		si->downlink = downlink;

		splitinfo = lappend(splitinfo, si);

		if (GistFollowRight(page))
		{
			/* lock next page */
			buf = ReadBuffer(state->r, GistPageGetOpaque(page)->rightlink);
			LockBuffer(buf, GIST_EXCLUSIVE);
		}
		else
			break;
	}

	/* Insert the downlinks */
	gistfinishsplit(state, stack, giststate, splitinfo, false);
}
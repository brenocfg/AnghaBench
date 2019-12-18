#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ downlinkoffnum; TYPE_1__* parent; } ;
struct TYPE_14__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_13__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  page; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_2__* IndexTuple ;
typedef  int /*<<< orphan*/  GISTSTATE ;
typedef  TYPE_3__ GISTInsertStack ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 TYPE_2__* CopyIndexTuple (TYPE_2__*) ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIST_EXCLUSIVE ; 
 int /*<<< orphan*/  GIST_UNLOCK ; 
 int /*<<< orphan*/  GistTupleSetValid (TYPE_2__*) ; 
 int /*<<< orphan*/  ItemPointerSetBlockNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistFindCorrectParent (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* gistgetadjusted (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static IndexTuple
gistformdownlink(Relation rel, Buffer buf, GISTSTATE *giststate,
				 GISTInsertStack *stack)
{
	Page		page = BufferGetPage(buf);
	OffsetNumber maxoff;
	OffsetNumber offset;
	IndexTuple	downlink = NULL;

	maxoff = PageGetMaxOffsetNumber(page);
	for (offset = FirstOffsetNumber; offset <= maxoff; offset = OffsetNumberNext(offset))
	{
		IndexTuple	ituple = (IndexTuple)
		PageGetItem(page, PageGetItemId(page, offset));

		if (downlink == NULL)
			downlink = CopyIndexTuple(ituple);
		else
		{
			IndexTuple	newdownlink;

			newdownlink = gistgetadjusted(rel, downlink, ituple,
										  giststate);
			if (newdownlink)
				downlink = newdownlink;
		}
	}

	/*
	 * If the page is completely empty, we can't form a meaningful downlink
	 * for it. But we have to insert a downlink for the page. Any key will do,
	 * as long as its consistent with the downlink of parent page, so that we
	 * can legally insert it to the parent. A minimal one that matches as few
	 * scans as possible would be best, to keep scans from doing useless work,
	 * but we don't know how to construct that. So we just use the downlink of
	 * the original page that was split - that's as far from optimal as it can
	 * get but will do..
	 */
	if (!downlink)
	{
		ItemId		iid;

		LockBuffer(stack->parent->buffer, GIST_EXCLUSIVE);
		gistFindCorrectParent(rel, stack);
		iid = PageGetItemId(stack->parent->page, stack->downlinkoffnum);
		downlink = (IndexTuple) PageGetItem(stack->parent->page, iid);
		downlink = CopyIndexTuple(downlink);
		LockBuffer(stack->parent->buffer, GIST_UNLOCK);
	}

	ItemPointerSetBlockNumber(&(downlink->t_tid), BufferGetBlockNumber(buf));
	GistTupleSetValid(downlink);

	return downlink;
}
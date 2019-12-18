#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ btpo_next; scalar_t__ btpo_prev; } ;
struct TYPE_9__ {scalar_t__ bts_blkno; scalar_t__ bts_offset; struct TYPE_9__* bts_parent; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  scalar_t__ Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_1__* BTStack ;
typedef  TYPE_2__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  BT_READ ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidBuffer ; 
 scalar_t__ P_FIRSTDATAKEY (TYPE_2__*) ; 
 scalar_t__ P_INCOMPLETE_SPLIT (TYPE_2__*) ; 
 scalar_t__ P_ISROOT (TYPE_2__*) ; 
 scalar_t__ P_NONE ; 
 scalar_t__ P_RIGHTMOST (TYPE_2__*) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ _bt_getbuf (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ _bt_getstackbuf (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
_bt_lock_branch_parent(Relation rel, BlockNumber child, BTStack stack,
					   Buffer *topparent, OffsetNumber *topoff,
					   BlockNumber *target, BlockNumber *rightsib)
{
	BlockNumber parent;
	OffsetNumber poffset,
				maxoff;
	Buffer		pbuf;
	Page		page;
	BTPageOpaque opaque;
	BlockNumber leftsib;

	/*
	 * Locate the downlink of "child" in the parent, updating the stack entry
	 * if needed.  This is how !heapkeyspace indexes deal with having
	 * non-unique high keys in leaf level pages.  Even heapkeyspace indexes
	 * can have a stale stack due to insertions into the parent.
	 */
	pbuf = _bt_getstackbuf(rel, stack, child);
	if (pbuf == InvalidBuffer)
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg_internal("failed to re-find parent key in index \"%s\" for deletion target page %u",
								 RelationGetRelationName(rel), child)));
	parent = stack->bts_blkno;
	poffset = stack->bts_offset;

	page = BufferGetPage(pbuf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	maxoff = PageGetMaxOffsetNumber(page);

	/*
	 * If the target is the rightmost child of its parent, then we can't
	 * delete, unless it's also the only child.
	 */
	if (poffset >= maxoff)
	{
		/* It's rightmost child... */
		if (poffset == P_FIRSTDATAKEY(opaque))
		{
			/*
			 * It's only child, so safe if parent would itself be removable.
			 * We have to check the parent itself, and then recurse to test
			 * the conditions at the parent's parent.
			 */
			if (P_RIGHTMOST(opaque) || P_ISROOT(opaque) ||
				P_INCOMPLETE_SPLIT(opaque))
			{
				_bt_relbuf(rel, pbuf);
				return false;
			}

			*target = parent;
			*rightsib = opaque->btpo_next;
			leftsib = opaque->btpo_prev;

			_bt_relbuf(rel, pbuf);

			/*
			 * Like in _bt_pagedel, check that the left sibling is not marked
			 * with INCOMPLETE_SPLIT flag.  That would mean that there is no
			 * downlink to the page to be deleted, and the page deletion
			 * algorithm isn't prepared to handle that.
			 */
			if (leftsib != P_NONE)
			{
				Buffer		lbuf;
				Page		lpage;
				BTPageOpaque lopaque;

				lbuf = _bt_getbuf(rel, leftsib, BT_READ);
				lpage = BufferGetPage(lbuf);
				lopaque = (BTPageOpaque) PageGetSpecialPointer(lpage);

				/*
				 * If the left sibling was concurrently split, so that its
				 * next-pointer doesn't point to the current page anymore, the
				 * split that created the current page must be completed. (We
				 * don't allow splitting an incompletely split page again
				 * until the previous split has been completed)
				 */
				if (lopaque->btpo_next == parent &&
					P_INCOMPLETE_SPLIT(lopaque))
				{
					_bt_relbuf(rel, lbuf);
					return false;
				}
				_bt_relbuf(rel, lbuf);
			}

			return _bt_lock_branch_parent(rel, parent, stack->bts_parent,
										  topparent, topoff, target, rightsib);
		}
		else
		{
			/* Unsafe to delete */
			_bt_relbuf(rel, pbuf);
			return false;
		}
	}
	else
	{
		/* Not rightmost child, so safe to delete */
		*topparent = pbuf;
		*topoff = poffset;
		return true;
	}
}
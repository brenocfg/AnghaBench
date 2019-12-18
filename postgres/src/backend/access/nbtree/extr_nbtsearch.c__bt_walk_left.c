#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ btpo_prev; scalar_t__ btpo_next; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_1__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  BT_READ ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 scalar_t__ P_ISDELETED (TYPE_1__*) ; 
 scalar_t__ P_LEFTMOST (TYPE_1__*) ; 
 scalar_t__ P_RIGHTMOST (TYPE_1__*) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_getbuf (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relandgetbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 

__attribute__((used)) static Buffer
_bt_walk_left(Relation rel, Buffer buf, Snapshot snapshot)
{
	Page		page;
	BTPageOpaque opaque;

	page = BufferGetPage(buf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);

	for (;;)
	{
		BlockNumber obknum;
		BlockNumber lblkno;
		BlockNumber blkno;
		int			tries;

		/* if we're at end of tree, release buf and return failure */
		if (P_LEFTMOST(opaque))
		{
			_bt_relbuf(rel, buf);
			break;
		}
		/* remember original page we are stepping left from */
		obknum = BufferGetBlockNumber(buf);
		/* step left */
		blkno = lblkno = opaque->btpo_prev;
		_bt_relbuf(rel, buf);
		/* check for interrupts while we're not holding any buffer lock */
		CHECK_FOR_INTERRUPTS();
		buf = _bt_getbuf(rel, blkno, BT_READ);
		page = BufferGetPage(buf);
		TestForOldSnapshot(snapshot, rel, page);
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);

		/*
		 * If this isn't the page we want, walk right till we find what we
		 * want --- but go no more than four hops (an arbitrary limit). If we
		 * don't find the correct page by then, the most likely bet is that
		 * the original page got deleted and isn't in the sibling chain at all
		 * anymore, not that its left sibling got split more than four times.
		 *
		 * Note that it is correct to test P_ISDELETED not P_IGNORE here,
		 * because half-dead pages are still in the sibling chain.  Caller
		 * must reject half-dead pages if wanted.
		 */
		tries = 0;
		for (;;)
		{
			if (!P_ISDELETED(opaque) && opaque->btpo_next == obknum)
			{
				/* Found desired page, return it */
				return buf;
			}
			if (P_RIGHTMOST(opaque) || ++tries > 4)
				break;
			blkno = opaque->btpo_next;
			buf = _bt_relandgetbuf(rel, buf, blkno, BT_READ);
			page = BufferGetPage(buf);
			TestForOldSnapshot(snapshot, rel, page);
			opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		}

		/* Return to the original page to see what's up */
		buf = _bt_relandgetbuf(rel, buf, obknum, BT_READ);
		page = BufferGetPage(buf);
		TestForOldSnapshot(snapshot, rel, page);
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		if (P_ISDELETED(opaque))
		{
			/*
			 * It was deleted.  Move right to first nondeleted page (there
			 * must be one); that is the page that has acquired the deleted
			 * one's keyspace, so stepping left from it will take us where we
			 * want to be.
			 */
			for (;;)
			{
				if (P_RIGHTMOST(opaque))
					elog(ERROR, "fell off the end of index \"%s\"",
						 RelationGetRelationName(rel));
				blkno = opaque->btpo_next;
				buf = _bt_relandgetbuf(rel, buf, blkno, BT_READ);
				page = BufferGetPage(buf);
				TestForOldSnapshot(snapshot, rel, page);
				opaque = (BTPageOpaque) PageGetSpecialPointer(page);
				if (!P_ISDELETED(opaque))
					break;
			}

			/*
			 * Now return to top of loop, resetting obknum to point to this
			 * nondeleted page, and try again.
			 */
		}
		else
		{
			/*
			 * It wasn't deleted; the explanation had better be that the page
			 * to the left got split or deleted. Without this check, we'd go
			 * into an infinite loop if there's anything wrong.
			 */
			if (opaque->btpo_prev == lblkno)
				elog(ERROR, "could not find left sibling of block %u in index \"%s\"",
					 obknum, RelationGetRelationName(rel));
			/* Okay to try again with new lblkno value */
		}
	}

	return InvalidBuffer;
}
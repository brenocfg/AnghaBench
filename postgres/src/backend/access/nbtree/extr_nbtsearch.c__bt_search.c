#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int level; } ;
struct TYPE_9__ {TYPE_1__ btpo; } ;
struct TYPE_8__ {struct TYPE_8__* bts_parent; int /*<<< orphan*/  bts_offset; int /*<<< orphan*/  bts_blkno; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  int /*<<< orphan*/  BTStackData ;
typedef  TYPE_2__* BTStack ;
typedef  int /*<<< orphan*/  BTScanInsert ;
typedef  TYPE_3__* BTPageOpaque ;

/* Variables and functions */
 int BT_READ ; 
 int BT_WRITE ; 
 int /*<<< orphan*/  BTreeInnerTupleGetDownLink (scalar_t__) ; 
 int BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int) ; 
 scalar_t__ P_ISLEAF (TYPE_3__*) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_binsrch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_getroot (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _bt_moveright (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relandgetbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 

BTStack
_bt_search(Relation rel, BTScanInsert key, Buffer *bufP, int access,
		   Snapshot snapshot)
{
	BTStack		stack_in = NULL;
	int			page_access = BT_READ;

	/* Get the root page to start with */
	*bufP = _bt_getroot(rel, access);

	/* If index is empty and access = BT_READ, no root page is created. */
	if (!BufferIsValid(*bufP))
		return (BTStack) NULL;

	/* Loop iterates once per level descended in the tree */
	for (;;)
	{
		Page		page;
		BTPageOpaque opaque;
		OffsetNumber offnum;
		ItemId		itemid;
		IndexTuple	itup;
		BlockNumber blkno;
		BlockNumber par_blkno;
		BTStack		new_stack;

		/*
		 * Race -- the page we just grabbed may have split since we read its
		 * pointer in the parent (or metapage).  If it has, we may need to
		 * move right to its new sibling.  Do that.
		 *
		 * In write-mode, allow _bt_moveright to finish any incomplete splits
		 * along the way.  Strictly speaking, we'd only need to finish an
		 * incomplete split on the leaf page we're about to insert to, not on
		 * any of the upper levels (they are taken care of in _bt_getstackbuf,
		 * if the leaf page is split and we insert to the parent page).  But
		 * this is a good opportunity to finish splits of internal pages too.
		 */
		*bufP = _bt_moveright(rel, key, *bufP, (access == BT_WRITE), stack_in,
							  page_access, snapshot);

		/* if this is a leaf page, we're done */
		page = BufferGetPage(*bufP);
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		if (P_ISLEAF(opaque))
			break;

		/*
		 * Find the appropriate item on the internal page, and get the child
		 * page that it points to.
		 */
		offnum = _bt_binsrch(rel, key, *bufP);
		itemid = PageGetItemId(page, offnum);
		itup = (IndexTuple) PageGetItem(page, itemid);
		blkno = BTreeInnerTupleGetDownLink(itup);
		par_blkno = BufferGetBlockNumber(*bufP);

		/*
		 * We need to save the location of the pivot tuple we chose in the
		 * parent page on a stack.  If we need to split a page, we'll use
		 * the stack to work back up to its parent page.  If caller ends up
		 * splitting a page one level down, it usually ends up inserting a
		 * new pivot tuple/downlink immediately after the location recorded
		 * here.
		 */
		new_stack = (BTStack) palloc(sizeof(BTStackData));
		new_stack->bts_blkno = par_blkno;
		new_stack->bts_offset = offnum;
		new_stack->bts_parent = stack_in;

		/*
		 * Page level 1 is lowest non-leaf page level prior to leaves.  So, if
		 * we're on the level 1 and asked to lock leaf page in write mode,
		 * then lock next page in write mode, because it must be a leaf.
		 */
		if (opaque->btpo.level == 1 && access == BT_WRITE)
			page_access = BT_WRITE;

		/* drop the read lock on the parent page, acquire one on the child */
		*bufP = _bt_relandgetbuf(rel, *bufP, blkno, page_access);

		/* okay, all set to move down a level */
		stack_in = new_stack;
	}

	/*
	 * If we're asked to lock leaf in write mode, but didn't manage to, then
	 * relock.  This should only happen when the root page is a leaf page (and
	 * the only page in the index other than the metapage).
	 */
	if (access == BT_WRITE && page_access == BT_READ)
	{
		/* trade in our read lock for a write lock */
		LockBuffer(*bufP, BUFFER_LOCK_UNLOCK);
		LockBuffer(*bufP, BT_WRITE);

		/*
		 * If the page was split between the time that we surrendered our read
		 * lock and acquired our write lock, then this page may no longer be
		 * the right place for the key we want to insert.  In this case, we
		 * need to move right in the tree.  See Lehman and Yao for an
		 * excruciatingly precise description.
		 */
		*bufP = _bt_moveright(rel, key, *bufP, true, stack_in, BT_WRITE,
							  snapshot);
	}

	return stack_in;
}
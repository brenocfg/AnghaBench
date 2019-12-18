#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ level; } ;
struct TYPE_9__ {TYPE_1__ btpo; } ;
struct TYPE_8__ {scalar_t__ bts_offset; int /*<<< orphan*/ * bts_parent; void* bts_blkno; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ IndexTuple ;
typedef  scalar_t__ Buffer ;
typedef  void* BlockNumber ;
typedef  TYPE_2__ BTStackData ;
typedef  TYPE_2__* BTStack ;
typedef  TYPE_4__* BTPageOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTreeInnerTupleSetDownLink (scalar_t__,void*) ; 
 void* BufferGetBlockNumber (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 scalar_t__ CopyIndexTuple (scalar_t__) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidBuffer ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  P_HIKEY ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ _bt_get_endpoint (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ _bt_getstackbuf (int /*<<< orphan*/ ,TYPE_2__*,void*) ; 
 int /*<<< orphan*/  _bt_insertonpg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 scalar_t__ _bt_newroot (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 

__attribute__((used)) static void
_bt_insert_parent(Relation rel,
				  Buffer buf,
				  Buffer rbuf,
				  BTStack stack,
				  bool is_root,
				  bool is_only)
{
	/*
	 * Here we have to do something Lehman and Yao don't talk about: deal with
	 * a root split and construction of a new root.  If our stack is empty
	 * then we have just split a node on what had been the root level when we
	 * descended the tree.  If it was still the root then we perform a
	 * new-root construction.  If it *wasn't* the root anymore, search to find
	 * the next higher level that someone constructed meanwhile, and find the
	 * right place to insert as for the normal case.
	 *
	 * If we have to search for the parent level, we do so by re-descending
	 * from the root.  This is not super-efficient, but it's rare enough not
	 * to matter.
	 */
	if (is_root)
	{
		Buffer		rootbuf;

		Assert(stack == NULL);
		Assert(is_only);
		/* create a new root node and update the metapage */
		rootbuf = _bt_newroot(rel, buf, rbuf);
		/* release the split buffers */
		_bt_relbuf(rel, rootbuf);
		_bt_relbuf(rel, rbuf);
		_bt_relbuf(rel, buf);
	}
	else
	{
		BlockNumber bknum = BufferGetBlockNumber(buf);
		BlockNumber rbknum = BufferGetBlockNumber(rbuf);
		Page		page = BufferGetPage(buf);
		IndexTuple	new_item;
		BTStackData fakestack;
		IndexTuple	ritem;
		Buffer		pbuf;

		if (stack == NULL)
		{
			BTPageOpaque lpageop;

			elog(DEBUG2, "concurrent ROOT page split");
			lpageop = (BTPageOpaque) PageGetSpecialPointer(page);
			/* Find the leftmost page at the next level up */
			pbuf = _bt_get_endpoint(rel, lpageop->btpo.level + 1, false,
									NULL);
			/* Set up a phony stack entry pointing there */
			stack = &fakestack;
			stack->bts_blkno = BufferGetBlockNumber(pbuf);
			stack->bts_offset = InvalidOffsetNumber;
			stack->bts_parent = NULL;
			_bt_relbuf(rel, pbuf);
		}

		/* get high key from left, a strict lower bound for new right page */
		ritem = (IndexTuple) PageGetItem(page,
										 PageGetItemId(page, P_HIKEY));

		/* form an index tuple that points at the new right page */
		new_item = CopyIndexTuple(ritem);
		BTreeInnerTupleSetDownLink(new_item, rbknum);

		/*
		 * Re-find and write lock the parent of buf.
		 *
		 * It's possible that the location of buf's downlink has changed since
		 * our initial _bt_search() descent.  _bt_getstackbuf() will detect
		 * and recover from this, updating the stack, which ensures that the
		 * new downlink will be inserted at the correct offset. Even buf's
		 * parent may have changed.
		 */
		pbuf = _bt_getstackbuf(rel, stack, bknum);

		/*
		 * Now we can unlock the right child. The left child will be unlocked
		 * by _bt_insertonpg().
		 */
		_bt_relbuf(rel, rbuf);

		if (pbuf == InvalidBuffer)
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg_internal("failed to re-find parent key in index \"%s\" for split pages %u/%u",
									 RelationGetRelationName(rel), bknum, rbknum)));

		/* Recursively insert into the parent */
		_bt_insertonpg(rel, NULL, pbuf, buf, stack->bts_parent,
					   new_item, stack->bts_offset + 1,
					   is_only);

		/* be tidy */
		pfree(new_item);
	}
}
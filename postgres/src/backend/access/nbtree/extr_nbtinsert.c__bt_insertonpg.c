#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ version; scalar_t__ fastlevel; int /*<<< orphan*/  last_cleanup_num_heap_tuples; int /*<<< orphan*/  oldest_btpo_xact; int /*<<< orphan*/  fastroot; int /*<<< orphan*/  level; int /*<<< orphan*/  root; } ;
typedef  TYPE_2__ xl_btree_metadata ;
struct TYPE_15__ {scalar_t__ offnum; } ;
typedef  TYPE_3__ xl_btree_insert ;
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_17__ {scalar_t__ btm_fastlevel; scalar_t__ btm_version; int /*<<< orphan*/  btm_last_cleanup_num_heap_tuples; int /*<<< orphan*/  btm_oldest_btpo_xact; int /*<<< orphan*/  btm_fastroot; int /*<<< orphan*/  btm_level; int /*<<< orphan*/  btm_root; } ;
struct TYPE_13__ {scalar_t__ level; } ;
struct TYPE_16__ {int /*<<< orphan*/  btpo_flags; TYPE_1__ btpo; } ;
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  int /*<<< orphan*/  BTStack ;
typedef  int /*<<< orphan*/  BTScanInsert ;
typedef  TYPE_4__* BTPageOpaque ;
typedef  TYPE_5__ BTMetaPageData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTP_INCOMPLETE_SPLIT ; 
 TYPE_5__* BTPageGetMeta (int /*<<< orphan*/ *) ; 
 scalar_t__ BTREE_FASTPATH_MIN_LEVEL ; 
 int /*<<< orphan*/  BTREE_METAPAGE ; 
 scalar_t__ BTREE_NOVAC_VERSION ; 
 int /*<<< orphan*/  BT_WRITE ; 
 scalar_t__ BTreeTupleGetNAtts (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ BlockNumberIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IndexRelationGetNumberOfAttributes (int /*<<< orphan*/ ) ; 
 scalar_t__ IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 int IndexTupleSize (scalar_t__) ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 scalar_t__ MAXALIGN (scalar_t__) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANIC ; 
 scalar_t__ P_FIRSTDATAKEY (TYPE_4__*) ; 
 int P_INCOMPLETE_SPLIT (TYPE_4__*) ; 
 int P_ISLEAF (TYPE_4__*) ; 
 int P_ISROOT (TYPE_4__*) ; 
 scalar_t__ P_LEFTMOST (TYPE_4__*) ; 
 scalar_t__ P_RIGHTMOST (TYPE_4__*) ; 
 scalar_t__ PageGetFreeSpace (int /*<<< orphan*/ *) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPageSplit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_BTREE_ID ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetTargetBlock (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationSetTargetBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfBtreeInsert ; 
 int /*<<< orphan*/  XLOG_BTREE_INSERT_LEAF ; 
 int /*<<< orphan*/  XLOG_BTREE_INSERT_META ; 
 int /*<<< orphan*/  XLOG_BTREE_INSERT_UPPER ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _bt_getrootheight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_insert_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _bt_pgaddtup (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_split (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _bt_upgrademetapage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
_bt_insertonpg(Relation rel,
			   BTScanInsert itup_key,
			   Buffer buf,
			   Buffer cbuf,
			   BTStack stack,
			   IndexTuple itup,
			   OffsetNumber newitemoff,
			   bool split_only_page)
{
	Page		page;
	BTPageOpaque lpageop;
	Size		itemsz;

	page = BufferGetPage(buf);
	lpageop = (BTPageOpaque) PageGetSpecialPointer(page);

	/* child buffer must be given iff inserting on an internal page */
	Assert(P_ISLEAF(lpageop) == !BufferIsValid(cbuf));
	/* tuple must have appropriate number of attributes */
	Assert(!P_ISLEAF(lpageop) ||
		   BTreeTupleGetNAtts(itup, rel) ==
		   IndexRelationGetNumberOfAttributes(rel));
	Assert(P_ISLEAF(lpageop) ||
		   BTreeTupleGetNAtts(itup, rel) <=
		   IndexRelationGetNumberOfKeyAttributes(rel));

	/* The caller should've finished any incomplete splits already. */
	if (P_INCOMPLETE_SPLIT(lpageop))
		elog(ERROR, "cannot insert to incompletely split page %u",
			 BufferGetBlockNumber(buf));

	itemsz = IndexTupleSize(itup);
	itemsz = MAXALIGN(itemsz);	/* be safe, PageAddItem will do this but we
								 * need to be consistent */

	/*
	 * Do we need to split the page to fit the item on it?
	 *
	 * Note: PageGetFreeSpace() subtracts sizeof(ItemIdData) from its result,
	 * so this comparison is correct even though we appear to be accounting
	 * only for the item and not for its line pointer.
	 */
	if (PageGetFreeSpace(page) < itemsz)
	{
		bool		is_root = P_ISROOT(lpageop);
		bool		is_only = P_LEFTMOST(lpageop) && P_RIGHTMOST(lpageop);
		Buffer		rbuf;

		/*
		 * If we're here then a pagesplit is needed. We should never reach
		 * here if we're using the fastpath since we should have checked for
		 * all the required conditions, including the fact that this page has
		 * enough freespace. Note that this routine can in theory deal with
		 * the situation where a NULL stack pointer is passed (that's what
		 * would happen if the fastpath is taken). But that path is much
		 * slower, defeating the very purpose of the optimization.  The
		 * following assertion should protect us from any future code changes
		 * that invalidate those assumptions.
		 *
		 * Note that whenever we fail to take the fastpath, we clear the
		 * cached block. Checking for a valid cached block at this point is
		 * enough to decide whether we're in a fastpath or not.
		 */
		Assert(!(P_ISLEAF(lpageop) &&
				 BlockNumberIsValid(RelationGetTargetBlock(rel))));

		/* split the buffer into left and right halves */
		rbuf = _bt_split(rel, itup_key, buf, cbuf, newitemoff, itemsz, itup);
		PredicateLockPageSplit(rel,
							   BufferGetBlockNumber(buf),
							   BufferGetBlockNumber(rbuf));

		/*----------
		 * By here,
		 *
		 *		+  our target page has been split;
		 *		+  the original tuple has been inserted;
		 *		+  we have write locks on both the old (left half)
		 *		   and new (right half) buffers, after the split; and
		 *		+  we know the key we want to insert into the parent
		 *		   (it's the "high key" on the left child page).
		 *
		 * We're ready to do the parent insertion.  We need to hold onto the
		 * locks for the child pages until we locate the parent, but we can
		 * at least release the lock on the right child before doing the
		 * actual insertion.  The lock on the left child will be released
		 * last of all by parent insertion, where it is the 'cbuf' of parent
		 * page.
		 *----------
		 */
		_bt_insert_parent(rel, buf, rbuf, stack, is_root, is_only);
	}
	else
	{
		Buffer		metabuf = InvalidBuffer;
		Page		metapg = NULL;
		BTMetaPageData *metad = NULL;
		OffsetNumber itup_off;
		BlockNumber itup_blkno;
		BlockNumber cachedBlock = InvalidBlockNumber;

		itup_off = newitemoff;
		itup_blkno = BufferGetBlockNumber(buf);

		/*
		 * If we are doing this insert because we split a page that was the
		 * only one on its tree level, but was not the root, it may have been
		 * the "fast root".  We need to ensure that the fast root link points
		 * at or above the current page.  We can safely acquire a lock on the
		 * metapage here --- see comments for _bt_newroot().
		 */
		if (split_only_page)
		{
			Assert(!P_ISLEAF(lpageop));

			metabuf = _bt_getbuf(rel, BTREE_METAPAGE, BT_WRITE);
			metapg = BufferGetPage(metabuf);
			metad = BTPageGetMeta(metapg);

			if (metad->btm_fastlevel >= lpageop->btpo.level)
			{
				/* no update wanted */
				_bt_relbuf(rel, metabuf);
				metabuf = InvalidBuffer;
			}
		}

		/*
		 * Every internal page should have exactly one negative infinity item
		 * at all times.  Only _bt_split() and _bt_newroot() should add items
		 * that become negative infinity items through truncation, since
		 * they're the only routines that allocate new internal pages.  Do not
		 * allow a retail insertion of a new item at the negative infinity
		 * offset.
		 */
		if (!P_ISLEAF(lpageop) && newitemoff == P_FIRSTDATAKEY(lpageop))
			elog(ERROR, "cannot insert second negative infinity item in block %u of index \"%s\"",
				 itup_blkno, RelationGetRelationName(rel));

		/* Do the update.  No ereport(ERROR) until changes are logged */
		START_CRIT_SECTION();

		if (!_bt_pgaddtup(page, itemsz, itup, newitemoff))
			elog(PANIC, "failed to add new item to block %u in index \"%s\"",
				 itup_blkno, RelationGetRelationName(rel));

		MarkBufferDirty(buf);

		if (BufferIsValid(metabuf))
		{
			/* upgrade meta-page if needed */
			if (metad->btm_version < BTREE_NOVAC_VERSION)
				_bt_upgrademetapage(metapg);
			metad->btm_fastroot = itup_blkno;
			metad->btm_fastlevel = lpageop->btpo.level;
			MarkBufferDirty(metabuf);
		}

		/* clear INCOMPLETE_SPLIT flag on child if inserting a downlink */
		if (BufferIsValid(cbuf))
		{
			Page		cpage = BufferGetPage(cbuf);
			BTPageOpaque cpageop = (BTPageOpaque) PageGetSpecialPointer(cpage);

			Assert(P_INCOMPLETE_SPLIT(cpageop));
			cpageop->btpo_flags &= ~BTP_INCOMPLETE_SPLIT;
			MarkBufferDirty(cbuf);
		}

		/*
		 * Cache the block information if we just inserted into the rightmost
		 * leaf page of the index and it's not the root page.  For very small
		 * index where root is also the leaf, there is no point trying for any
		 * optimization.
		 */
		if (P_RIGHTMOST(lpageop) && P_ISLEAF(lpageop) && !P_ISROOT(lpageop))
			cachedBlock = BufferGetBlockNumber(buf);

		/* XLOG stuff */
		if (RelationNeedsWAL(rel))
		{
			xl_btree_insert xlrec;
			xl_btree_metadata xlmeta;
			uint8		xlinfo;
			XLogRecPtr	recptr;

			xlrec.offnum = itup_off;

			XLogBeginInsert();
			XLogRegisterData((char *) &xlrec, SizeOfBtreeInsert);

			if (P_ISLEAF(lpageop))
				xlinfo = XLOG_BTREE_INSERT_LEAF;
			else
			{
				/*
				 * Register the left child whose INCOMPLETE_SPLIT flag was
				 * cleared.
				 */
				XLogRegisterBuffer(1, cbuf, REGBUF_STANDARD);

				xlinfo = XLOG_BTREE_INSERT_UPPER;
			}

			if (BufferIsValid(metabuf))
			{
				Assert(metad->btm_version >= BTREE_NOVAC_VERSION);
				xlmeta.version = metad->btm_version;
				xlmeta.root = metad->btm_root;
				xlmeta.level = metad->btm_level;
				xlmeta.fastroot = metad->btm_fastroot;
				xlmeta.fastlevel = metad->btm_fastlevel;
				xlmeta.oldest_btpo_xact = metad->btm_oldest_btpo_xact;
				xlmeta.last_cleanup_num_heap_tuples =
					metad->btm_last_cleanup_num_heap_tuples;

				XLogRegisterBuffer(2, metabuf, REGBUF_WILL_INIT | REGBUF_STANDARD);
				XLogRegisterBufData(2, (char *) &xlmeta, sizeof(xl_btree_metadata));

				xlinfo = XLOG_BTREE_INSERT_META;
			}

			XLogRegisterBuffer(0, buf, REGBUF_STANDARD);
			XLogRegisterBufData(0, (char *) itup, IndexTupleSize(itup));

			recptr = XLogInsert(RM_BTREE_ID, xlinfo);

			if (BufferIsValid(metabuf))
			{
				PageSetLSN(metapg, recptr);
			}
			if (BufferIsValid(cbuf))
			{
				PageSetLSN(BufferGetPage(cbuf), recptr);
			}

			PageSetLSN(page, recptr);
		}

		END_CRIT_SECTION();

		/* release buffers */
		if (BufferIsValid(metabuf))
			_bt_relbuf(rel, metabuf);
		if (BufferIsValid(cbuf))
			_bt_relbuf(rel, cbuf);
		_bt_relbuf(rel, buf);

		/*
		 * If we decided to cache the insertion target block, then set it now.
		 * But before that, check for the height of the tree and don't go for
		 * the optimization for small indexes. We defer that check to this
		 * point to ensure that we don't call _bt_getrootheight while holding
		 * lock on any other block.
		 *
		 * We do this after dropping locks on all buffers. So the information
		 * about whether the insertion block is still the rightmost block or
		 * not may have changed in between. But we will deal with that during
		 * next insert operation. No special care is required while setting
		 * it.
		 */
		if (BlockNumberIsValid(cachedBlock) &&
			_bt_getrootheight(rel) >= BTREE_FASTPATH_MIN_LEVEL)
			RelationSetTargetBlock(rel, cachedBlock);
	}
}
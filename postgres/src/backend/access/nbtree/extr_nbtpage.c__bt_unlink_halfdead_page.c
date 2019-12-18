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
struct TYPE_14__ {scalar_t__ topparent; scalar_t__ leafrightsib; scalar_t__ leafleftsib; int /*<<< orphan*/  btpo_xact; scalar_t__ rightsib; scalar_t__ leftsib; } ;
typedef  TYPE_2__ xl_btree_unlink_page ;
struct TYPE_15__ {scalar_t__ version; int fastlevel; int /*<<< orphan*/  last_cleanup_num_heap_tuples; int /*<<< orphan*/  oldest_btpo_xact; scalar_t__ fastroot; int /*<<< orphan*/  level; int /*<<< orphan*/  root; } ;
typedef  TYPE_3__ xl_btree_metadata ;
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_17__ {int btm_fastlevel; scalar_t__ btm_version; int /*<<< orphan*/  btm_last_cleanup_num_heap_tuples; int /*<<< orphan*/  btm_oldest_btpo_xact; scalar_t__ btm_fastroot; int /*<<< orphan*/  btm_level; int /*<<< orphan*/  btm_root; } ;
struct TYPE_13__ {int level; int /*<<< orphan*/  xact; } ;
struct TYPE_16__ {scalar_t__ btpo_prev; scalar_t__ btpo_next; TYPE_1__ btpo; int /*<<< orphan*/  btpo_flags; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * Page ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_4__* BTPageOpaque ;
typedef  TYPE_5__ BTMetaPageData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTP_DELETED ; 
 int /*<<< orphan*/  BTP_HALF_DEAD ; 
 TYPE_5__* BTPageGetMeta (int /*<<< orphan*/ *) ; 
 scalar_t__ BTREE_METAPAGE ; 
 scalar_t__ BTREE_NOVAC_VERSION ; 
 int /*<<< orphan*/  BT_READ ; 
 int /*<<< orphan*/  BT_WRITE ; 
 scalar_t__ BTreeInnerTupleGetDownLink (scalar_t__) ; 
 scalar_t__ BTreeTupleGetTopParent (scalar_t__) ; 
 int /*<<< orphan*/  BTreeTupleSetTopParent (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ P_FIRSTDATAKEY (TYPE_4__*) ; 
 scalar_t__ P_HIKEY ; 
 scalar_t__ P_ISDELETED (TYPE_4__*) ; 
 scalar_t__ P_ISHALFDEAD (TYPE_4__*) ; 
 scalar_t__ P_ISLEAF (TYPE_4__*) ; 
 scalar_t__ P_ISROOT (TYPE_4__*) ; 
 scalar_t__ P_NONE ; 
 int P_RIGHTMOST (TYPE_4__*) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_BTREE_ID ; 
 int /*<<< orphan*/  ReadNewTransactionId () ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfBtreeUnlinkPage ; 
 int /*<<< orphan*/  XLOG_BTREE_UNLINK_PAGE ; 
 int /*<<< orphan*/  XLOG_BTREE_UNLINK_PAGE_META ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_getbuf (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_upgrademetapage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static bool
_bt_unlink_halfdead_page(Relation rel, Buffer leafbuf, bool *rightsib_empty)
{
	BlockNumber leafblkno = BufferGetBlockNumber(leafbuf);
	BlockNumber leafleftsib;
	BlockNumber leafrightsib;
	BlockNumber target;
	BlockNumber leftsib;
	BlockNumber rightsib;
	Buffer		lbuf = InvalidBuffer;
	Buffer		buf;
	Buffer		rbuf;
	Buffer		metabuf = InvalidBuffer;
	Page		metapg = NULL;
	BTMetaPageData *metad = NULL;
	ItemId		itemid;
	Page		page;
	BTPageOpaque opaque;
	bool		rightsib_is_rightmost;
	int			targetlevel;
	IndexTuple	leafhikey;
	BlockNumber nextchild;

	page = BufferGetPage(leafbuf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);

	Assert(P_ISLEAF(opaque) && P_ISHALFDEAD(opaque));

	/*
	 * Remember some information about the leaf page.
	 */
	itemid = PageGetItemId(page, P_HIKEY);
	leafhikey = (IndexTuple) PageGetItem(page, itemid);
	leafleftsib = opaque->btpo_prev;
	leafrightsib = opaque->btpo_next;

	LockBuffer(leafbuf, BUFFER_LOCK_UNLOCK);

	/*
	 * Check here, as calling loops will have locks held, preventing
	 * interrupts from being processed.
	 */
	CHECK_FOR_INTERRUPTS();

	/*
	 * If the leaf page still has a parent pointing to it (or a chain of
	 * parents), we don't unlink the leaf page yet, but the topmost remaining
	 * parent in the branch.  Set 'target' and 'buf' to reference the page
	 * actually being unlinked.
	 */
	target = BTreeTupleGetTopParent(leafhikey);

	if (target != InvalidBlockNumber)
	{
		Assert(target != leafblkno);

		/* fetch the block number of the topmost parent's left sibling */
		buf = _bt_getbuf(rel, target, BT_READ);
		page = BufferGetPage(buf);
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		leftsib = opaque->btpo_prev;
		targetlevel = opaque->btpo.level;

		/*
		 * To avoid deadlocks, we'd better drop the target page lock before
		 * going further.
		 */
		LockBuffer(buf, BUFFER_LOCK_UNLOCK);
	}
	else
	{
		target = leafblkno;

		buf = leafbuf;
		leftsib = leafleftsib;
		targetlevel = 0;
	}

	/*
	 * We have to lock the pages we need to modify in the standard order:
	 * moving right, then up.  Else we will deadlock against other writers.
	 *
	 * So, first lock the leaf page, if it's not the target.  Then find and
	 * write-lock the current left sibling of the target page.  The sibling
	 * that was current a moment ago could have split, so we may have to move
	 * right.  This search could fail if either the sibling or the target page
	 * was deleted by someone else meanwhile; if so, give up.  (Right now,
	 * that should never happen, since page deletion is only done in VACUUM
	 * and there shouldn't be multiple VACUUMs concurrently on the same
	 * table.)
	 */
	if (target != leafblkno)
		LockBuffer(leafbuf, BT_WRITE);
	if (leftsib != P_NONE)
	{
		lbuf = _bt_getbuf(rel, leftsib, BT_WRITE);
		page = BufferGetPage(lbuf);
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		while (P_ISDELETED(opaque) || opaque->btpo_next != target)
		{
			/* step right one page */
			leftsib = opaque->btpo_next;
			_bt_relbuf(rel, lbuf);

			/*
			 * It'd be good to check for interrupts here, but it's not easy to
			 * do so because a lock is always held. This block isn't
			 * frequently reached, so hopefully the consequences of not
			 * checking interrupts aren't too bad.
			 */

			if (leftsib == P_NONE)
			{
				elog(LOG, "no left sibling (concurrent deletion?) of block %u in \"%s\"",
					 target,
					 RelationGetRelationName(rel));
				if (target != leafblkno)
				{
					/* we have only a pin on target, but pin+lock on leafbuf */
					ReleaseBuffer(buf);
					_bt_relbuf(rel, leafbuf);
				}
				else
				{
					/* we have only a pin on leafbuf */
					ReleaseBuffer(leafbuf);
				}
				return false;
			}
			lbuf = _bt_getbuf(rel, leftsib, BT_WRITE);
			page = BufferGetPage(lbuf);
			opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		}
	}
	else
		lbuf = InvalidBuffer;

	/*
	 * Next write-lock the target page itself.  It should be okay to take just
	 * a write lock not a superexclusive lock, since no scans would stop on an
	 * empty page.
	 */
	LockBuffer(buf, BT_WRITE);
	page = BufferGetPage(buf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);

	/*
	 * Check page is still empty etc, else abandon deletion.  This is just for
	 * paranoia's sake; a half-dead page cannot resurrect because there can be
	 * only one vacuum process running at a time.
	 */
	if (P_RIGHTMOST(opaque) || P_ISROOT(opaque) || P_ISDELETED(opaque))
	{
		elog(ERROR, "half-dead page changed status unexpectedly in block %u of index \"%s\"",
			 target, RelationGetRelationName(rel));
	}
	if (opaque->btpo_prev != leftsib)
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg_internal("left link changed unexpectedly in block %u of index \"%s\"",
								 target, RelationGetRelationName(rel))));

	if (target == leafblkno)
	{
		if (P_FIRSTDATAKEY(opaque) <= PageGetMaxOffsetNumber(page) ||
			!P_ISLEAF(opaque) || !P_ISHALFDEAD(opaque))
			elog(ERROR, "half-dead page changed status unexpectedly in block %u of index \"%s\"",
				 target, RelationGetRelationName(rel));
		nextchild = InvalidBlockNumber;
	}
	else
	{
		if (P_FIRSTDATAKEY(opaque) != PageGetMaxOffsetNumber(page) ||
			P_ISLEAF(opaque))
			elog(ERROR, "half-dead page changed status unexpectedly in block %u of index \"%s\"",
				 target, RelationGetRelationName(rel));

		/* remember the next non-leaf child down in the branch. */
		itemid = PageGetItemId(page, P_FIRSTDATAKEY(opaque));
		nextchild = BTreeInnerTupleGetDownLink((IndexTuple) PageGetItem(page, itemid));
		if (nextchild == leafblkno)
			nextchild = InvalidBlockNumber;
	}

	/*
	 * And next write-lock the (current) right sibling.
	 */
	rightsib = opaque->btpo_next;
	rbuf = _bt_getbuf(rel, rightsib, BT_WRITE);
	page = BufferGetPage(rbuf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	if (opaque->btpo_prev != target)
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg_internal("right sibling's left-link doesn't match: "
								 "block %u links to %u instead of expected %u in index \"%s\"",
								 rightsib, opaque->btpo_prev, target,
								 RelationGetRelationName(rel))));
	rightsib_is_rightmost = P_RIGHTMOST(opaque);
	*rightsib_empty = (P_FIRSTDATAKEY(opaque) > PageGetMaxOffsetNumber(page));

	/*
	 * If we are deleting the next-to-last page on the target's level, then
	 * the rightsib is a candidate to become the new fast root. (In theory, it
	 * might be possible to push the fast root even further down, but the odds
	 * of doing so are slim, and the locking considerations daunting.)
	 *
	 * We can safely acquire a lock on the metapage here --- see comments for
	 * _bt_newroot().
	 */
	if (leftsib == P_NONE && rightsib_is_rightmost)
	{
		page = BufferGetPage(rbuf);
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		if (P_RIGHTMOST(opaque))
		{
			/* rightsib will be the only one left on the level */
			metabuf = _bt_getbuf(rel, BTREE_METAPAGE, BT_WRITE);
			metapg = BufferGetPage(metabuf);
			metad = BTPageGetMeta(metapg);

			/*
			 * The expected case here is btm_fastlevel == targetlevel+1; if
			 * the fastlevel is <= targetlevel, something is wrong, and we
			 * choose to overwrite it to fix it.
			 */
			if (metad->btm_fastlevel > targetlevel + 1)
			{
				/* no update wanted */
				_bt_relbuf(rel, metabuf);
				metabuf = InvalidBuffer;
			}
		}
	}

	/*
	 * Here we begin doing the deletion.
	 */

	/* No ereport(ERROR) until changes are logged */
	START_CRIT_SECTION();

	/*
	 * Update siblings' side-links.  Note the target page's side-links will
	 * continue to point to the siblings.  Asserts here are just rechecking
	 * things we already verified above.
	 */
	if (BufferIsValid(lbuf))
	{
		page = BufferGetPage(lbuf);
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);
		Assert(opaque->btpo_next == target);
		opaque->btpo_next = rightsib;
	}
	page = BufferGetPage(rbuf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	Assert(opaque->btpo_prev == target);
	opaque->btpo_prev = leftsib;

	/*
	 * If we deleted a parent of the targeted leaf page, instead of the leaf
	 * itself, update the leaf to point to the next remaining child in the
	 * branch.
	 */
	if (target != leafblkno)
		BTreeTupleSetTopParent(leafhikey, nextchild);

	/*
	 * Mark the page itself deleted.  It can be recycled when all current
	 * transactions are gone.  Storing GetTopTransactionId() would work, but
	 * we're in VACUUM and would not otherwise have an XID.  Having already
	 * updated links to the target, ReadNewTransactionId() suffices as an
	 * upper bound.  Any scan having retained a now-stale link is advertising
	 * in its PGXACT an xmin less than or equal to the value we read here.  It
	 * will continue to do so, holding back RecentGlobalXmin, for the duration
	 * of that scan.
	 */
	page = BufferGetPage(buf);
	opaque = (BTPageOpaque) PageGetSpecialPointer(page);
	opaque->btpo_flags &= ~BTP_HALF_DEAD;
	opaque->btpo_flags |= BTP_DELETED;
	opaque->btpo.xact = ReadNewTransactionId();

	/* And update the metapage, if needed */
	if (BufferIsValid(metabuf))
	{
		/* upgrade metapage if needed */
		if (metad->btm_version < BTREE_NOVAC_VERSION)
			_bt_upgrademetapage(metapg);
		metad->btm_fastroot = rightsib;
		metad->btm_fastlevel = targetlevel;
		MarkBufferDirty(metabuf);
	}

	/* Must mark buffers dirty before XLogInsert */
	MarkBufferDirty(rbuf);
	MarkBufferDirty(buf);
	if (BufferIsValid(lbuf))
		MarkBufferDirty(lbuf);
	if (target != leafblkno)
		MarkBufferDirty(leafbuf);

	/* XLOG stuff */
	if (RelationNeedsWAL(rel))
	{
		xl_btree_unlink_page xlrec;
		xl_btree_metadata xlmeta;
		uint8		xlinfo;
		XLogRecPtr	recptr;

		XLogBeginInsert();

		XLogRegisterBuffer(0, buf, REGBUF_WILL_INIT);
		if (BufferIsValid(lbuf))
			XLogRegisterBuffer(1, lbuf, REGBUF_STANDARD);
		XLogRegisterBuffer(2, rbuf, REGBUF_STANDARD);
		if (target != leafblkno)
			XLogRegisterBuffer(3, leafbuf, REGBUF_WILL_INIT);

		/* information on the unlinked block */
		xlrec.leftsib = leftsib;
		xlrec.rightsib = rightsib;
		xlrec.btpo_xact = opaque->btpo.xact;

		/* information needed to recreate the leaf block (if not the target) */
		xlrec.leafleftsib = leafleftsib;
		xlrec.leafrightsib = leafrightsib;
		xlrec.topparent = nextchild;

		XLogRegisterData((char *) &xlrec, SizeOfBtreeUnlinkPage);

		if (BufferIsValid(metabuf))
		{
			XLogRegisterBuffer(4, metabuf, REGBUF_WILL_INIT | REGBUF_STANDARD);

			Assert(metad->btm_version >= BTREE_NOVAC_VERSION);
			xlmeta.version = metad->btm_version;
			xlmeta.root = metad->btm_root;
			xlmeta.level = metad->btm_level;
			xlmeta.fastroot = metad->btm_fastroot;
			xlmeta.fastlevel = metad->btm_fastlevel;
			xlmeta.oldest_btpo_xact = metad->btm_oldest_btpo_xact;
			xlmeta.last_cleanup_num_heap_tuples = metad->btm_last_cleanup_num_heap_tuples;

			XLogRegisterBufData(4, (char *) &xlmeta, sizeof(xl_btree_metadata));
			xlinfo = XLOG_BTREE_UNLINK_PAGE_META;
		}
		else
			xlinfo = XLOG_BTREE_UNLINK_PAGE;

		recptr = XLogInsert(RM_BTREE_ID, xlinfo);

		if (BufferIsValid(metabuf))
		{
			PageSetLSN(metapg, recptr);
		}
		page = BufferGetPage(rbuf);
		PageSetLSN(page, recptr);
		page = BufferGetPage(buf);
		PageSetLSN(page, recptr);
		if (BufferIsValid(lbuf))
		{
			page = BufferGetPage(lbuf);
			PageSetLSN(page, recptr);
		}
		if (target != leafblkno)
		{
			page = BufferGetPage(leafbuf);
			PageSetLSN(page, recptr);
		}
	}

	END_CRIT_SECTION();

	/* release metapage */
	if (BufferIsValid(metabuf))
		_bt_relbuf(rel, metabuf);

	/* release siblings */
	if (BufferIsValid(lbuf))
		_bt_relbuf(rel, lbuf);
	_bt_relbuf(rel, rbuf);

	/*
	 * Release the target, if it was not the leaf block.  The leaf is always
	 * kept locked.
	 */
	if (target != leafblkno)
		_bt_relbuf(rel, buf);

	return true;
}
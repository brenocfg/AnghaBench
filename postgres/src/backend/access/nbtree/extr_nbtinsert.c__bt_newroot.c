#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ level; void* rootblk; } ;
typedef  TYPE_2__ xl_btree_newroot ;
struct TYPE_18__ {scalar_t__ version; int /*<<< orphan*/  last_cleanup_num_heap_tuples; int /*<<< orphan*/  oldest_btpo_xact; scalar_t__ fastlevel; void* fastroot; scalar_t__ level; void* root; } ;
typedef  TYPE_3__ xl_btree_metadata ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_22__ {scalar_t__ btm_version; int /*<<< orphan*/  btm_last_cleanup_num_heap_tuples; int /*<<< orphan*/  btm_oldest_btpo_xact; scalar_t__ btm_level; scalar_t__ btm_fastlevel; void* btm_fastroot; void* btm_root; } ;
struct TYPE_16__ {scalar_t__ level; } ;
struct TYPE_21__ {int /*<<< orphan*/  btpo_flags; TYPE_1__ btpo; scalar_t__ btpo_cycleid; int /*<<< orphan*/  btpo_next; int /*<<< orphan*/  btpo_prev; } ;
struct TYPE_20__ {int t_info; } ;
struct TYPE_19__ {int pd_upper; int pd_special; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_4__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  IndexTupleData ;
typedef  TYPE_5__* IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  void* BlockNumber ;
typedef  TYPE_6__* BTPageOpaque ;
typedef  TYPE_7__ BTMetaPageData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTP_INCOMPLETE_SPLIT ; 
 int /*<<< orphan*/  BTP_ROOT ; 
 TYPE_7__* BTPageGetMeta (scalar_t__) ; 
 int /*<<< orphan*/  BTREE_METAPAGE ; 
 scalar_t__ BTREE_NOVAC_VERSION ; 
 int /*<<< orphan*/  BT_WRITE ; 
 int /*<<< orphan*/  BTreeInnerTupleSetDownLink (TYPE_5__*,void*) ; 
 scalar_t__ BTreeTupleGetNAtts (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTreeTupleSetNAtts (TYPE_5__*,int /*<<< orphan*/ ) ; 
 void* BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 TYPE_5__* CopyIndexTuple (TYPE_5__*) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 scalar_t__ IndexRelationGetNumberOfKeyAttributes (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOffsetNumber ; 
 int ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  P_FIRSTKEY ; 
 int /*<<< orphan*/  P_HIKEY ; 
 int P_INCOMPLETE_SPLIT (TYPE_6__*) ; 
 int /*<<< orphan*/  P_NEW ; 
 int /*<<< orphan*/  P_NONE ; 
 scalar_t__ PageAddItem (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ PageGetItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_BTREE_ID ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfBtreeNewroot ; 
 int /*<<< orphan*/  XLOG_BTREE_NEWROOT ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_upgrademetapage (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (TYPE_5__*) ; 

__attribute__((used)) static Buffer
_bt_newroot(Relation rel, Buffer lbuf, Buffer rbuf)
{
	Buffer		rootbuf;
	Page		lpage,
				rootpage;
	BlockNumber lbkno,
				rbkno;
	BlockNumber rootblknum;
	BTPageOpaque rootopaque;
	BTPageOpaque lopaque;
	ItemId		itemid;
	IndexTuple	item;
	IndexTuple	left_item;
	Size		left_item_sz;
	IndexTuple	right_item;
	Size		right_item_sz;
	Buffer		metabuf;
	Page		metapg;
	BTMetaPageData *metad;

	lbkno = BufferGetBlockNumber(lbuf);
	rbkno = BufferGetBlockNumber(rbuf);
	lpage = BufferGetPage(lbuf);
	lopaque = (BTPageOpaque) PageGetSpecialPointer(lpage);

	/* get a new root page */
	rootbuf = _bt_getbuf(rel, P_NEW, BT_WRITE);
	rootpage = BufferGetPage(rootbuf);
	rootblknum = BufferGetBlockNumber(rootbuf);

	/* acquire lock on the metapage */
	metabuf = _bt_getbuf(rel, BTREE_METAPAGE, BT_WRITE);
	metapg = BufferGetPage(metabuf);
	metad = BTPageGetMeta(metapg);

	/*
	 * Create downlink item for left page (old root).  Since this will be the
	 * first item in a non-leaf page, it implicitly has minus-infinity key
	 * value, so we need not store any actual key in it.
	 */
	left_item_sz = sizeof(IndexTupleData);
	left_item = (IndexTuple) palloc(left_item_sz);
	left_item->t_info = left_item_sz;
	BTreeInnerTupleSetDownLink(left_item, lbkno);
	BTreeTupleSetNAtts(left_item, 0);

	/*
	 * Create downlink item for right page.  The key for it is obtained from
	 * the "high key" position in the left page.
	 */
	itemid = PageGetItemId(lpage, P_HIKEY);
	right_item_sz = ItemIdGetLength(itemid);
	item = (IndexTuple) PageGetItem(lpage, itemid);
	right_item = CopyIndexTuple(item);
	BTreeInnerTupleSetDownLink(right_item, rbkno);

	/* NO EREPORT(ERROR) from here till newroot op is logged */
	START_CRIT_SECTION();

	/* upgrade metapage if needed */
	if (metad->btm_version < BTREE_NOVAC_VERSION)
		_bt_upgrademetapage(metapg);

	/* set btree special data */
	rootopaque = (BTPageOpaque) PageGetSpecialPointer(rootpage);
	rootopaque->btpo_prev = rootopaque->btpo_next = P_NONE;
	rootopaque->btpo_flags = BTP_ROOT;
	rootopaque->btpo.level =
		((BTPageOpaque) PageGetSpecialPointer(lpage))->btpo.level + 1;
	rootopaque->btpo_cycleid = 0;

	/* update metapage data */
	metad->btm_root = rootblknum;
	metad->btm_level = rootopaque->btpo.level;
	metad->btm_fastroot = rootblknum;
	metad->btm_fastlevel = rootopaque->btpo.level;

	/*
	 * Insert the left page pointer into the new root page.  The root page is
	 * the rightmost page on its level so there is no "high key" in it; the
	 * two items will go into positions P_HIKEY and P_FIRSTKEY.
	 *
	 * Note: we *must* insert the two items in item-number order, for the
	 * benefit of _bt_restore_page().
	 */
	Assert(BTreeTupleGetNAtts(left_item, rel) == 0);
	if (PageAddItem(rootpage, (Item) left_item, left_item_sz, P_HIKEY,
					false, false) == InvalidOffsetNumber)
		elog(PANIC, "failed to add leftkey to new root page"
			 " while splitting block %u of index \"%s\"",
			 BufferGetBlockNumber(lbuf), RelationGetRelationName(rel));

	/*
	 * insert the right page pointer into the new root page.
	 */
	Assert(BTreeTupleGetNAtts(right_item, rel) > 0);
	Assert(BTreeTupleGetNAtts(right_item, rel) <=
		   IndexRelationGetNumberOfKeyAttributes(rel));
	if (PageAddItem(rootpage, (Item) right_item, right_item_sz, P_FIRSTKEY,
					false, false) == InvalidOffsetNumber)
		elog(PANIC, "failed to add rightkey to new root page"
			 " while splitting block %u of index \"%s\"",
			 BufferGetBlockNumber(lbuf), RelationGetRelationName(rel));

	/* Clear the incomplete-split flag in the left child */
	Assert(P_INCOMPLETE_SPLIT(lopaque));
	lopaque->btpo_flags &= ~BTP_INCOMPLETE_SPLIT;
	MarkBufferDirty(lbuf);

	MarkBufferDirty(rootbuf);
	MarkBufferDirty(metabuf);

	/* XLOG stuff */
	if (RelationNeedsWAL(rel))
	{
		xl_btree_newroot xlrec;
		XLogRecPtr	recptr;
		xl_btree_metadata md;

		xlrec.rootblk = rootblknum;
		xlrec.level = metad->btm_level;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfBtreeNewroot);

		XLogRegisterBuffer(0, rootbuf, REGBUF_WILL_INIT);
		XLogRegisterBuffer(1, lbuf, REGBUF_STANDARD);
		XLogRegisterBuffer(2, metabuf, REGBUF_WILL_INIT | REGBUF_STANDARD);

		Assert(metad->btm_version >= BTREE_NOVAC_VERSION);
		md.version = metad->btm_version;
		md.root = rootblknum;
		md.level = metad->btm_level;
		md.fastroot = rootblknum;
		md.fastlevel = metad->btm_level;
		md.oldest_btpo_xact = metad->btm_oldest_btpo_xact;
		md.last_cleanup_num_heap_tuples = metad->btm_last_cleanup_num_heap_tuples;

		XLogRegisterBufData(2, (char *) &md, sizeof(xl_btree_metadata));

		/*
		 * Direct access to page is not good but faster - we should implement
		 * some new func in page API.
		 */
		XLogRegisterBufData(0,
							(char *) rootpage + ((PageHeader) rootpage)->pd_upper,
							((PageHeader) rootpage)->pd_special -
							((PageHeader) rootpage)->pd_upper);

		recptr = XLogInsert(RM_BTREE_ID, XLOG_BTREE_NEWROOT);

		PageSetLSN(lpage, recptr);
		PageSetLSN(rootpage, recptr);
		PageSetLSN(metapg, recptr);
	}

	END_CRIT_SECTION();

	/* done with metapage */
	_bt_relbuf(rel, metabuf);

	pfree(left_item);
	pfree(right_item);

	return rootbuf;
}
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
struct TYPE_4__ {scalar_t__ version; scalar_t__ last_cleanup_num_heap_tuples; scalar_t__ oldest_btpo_xact; int /*<<< orphan*/  fastlevel; int /*<<< orphan*/  fastroot; int /*<<< orphan*/  level; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ xl_btree_metadata ;
typedef  scalar_t__ float8 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  scalar_t__ TransactionId ;
struct TYPE_5__ {scalar_t__ btm_version; scalar_t__ btm_oldest_btpo_xact; scalar_t__ btm_last_cleanup_num_heap_tuples; int /*<<< orphan*/  btm_fastlevel; int /*<<< orphan*/  btm_fastroot; int /*<<< orphan*/  btm_level; int /*<<< orphan*/  btm_root; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_2__ BTMetaPageData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_2__* BTPageGetMeta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTREE_METAPAGE ; 
 scalar_t__ BTREE_NOVAC_VERSION ; 
 int /*<<< orphan*/  BT_READ ; 
 int /*<<< orphan*/  BT_WRITE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_BTREE_ID ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  XLOG_BTREE_META_CLEANUP ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _bt_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_upgrademetapage (int /*<<< orphan*/ ) ; 

void
_bt_update_meta_cleanup_info(Relation rel, TransactionId oldestBtpoXact,
							 float8 numHeapTuples)
{
	Buffer		metabuf;
	Page		metapg;
	BTMetaPageData *metad;
	bool		needsRewrite = false;
	XLogRecPtr	recptr;

	/* read the metapage and check if it needs rewrite */
	metabuf = _bt_getbuf(rel, BTREE_METAPAGE, BT_READ);
	metapg = BufferGetPage(metabuf);
	metad = BTPageGetMeta(metapg);

	/* outdated version of metapage always needs rewrite */
	if (metad->btm_version < BTREE_NOVAC_VERSION)
		needsRewrite = true;
	else if (metad->btm_oldest_btpo_xact != oldestBtpoXact ||
			 metad->btm_last_cleanup_num_heap_tuples != numHeapTuples)
		needsRewrite = true;

	if (!needsRewrite)
	{
		_bt_relbuf(rel, metabuf);
		return;
	}

	/* trade in our read lock for a write lock */
	LockBuffer(metabuf, BUFFER_LOCK_UNLOCK);
	LockBuffer(metabuf, BT_WRITE);

	START_CRIT_SECTION();

	/* upgrade meta-page if needed */
	if (metad->btm_version < BTREE_NOVAC_VERSION)
		_bt_upgrademetapage(metapg);

	/* update cleanup-related information */
	metad->btm_oldest_btpo_xact = oldestBtpoXact;
	metad->btm_last_cleanup_num_heap_tuples = numHeapTuples;
	MarkBufferDirty(metabuf);

	/* write wal record if needed */
	if (RelationNeedsWAL(rel))
	{
		xl_btree_metadata md;

		XLogBeginInsert();
		XLogRegisterBuffer(0, metabuf, REGBUF_WILL_INIT | REGBUF_STANDARD);

		Assert(metad->btm_version >= BTREE_NOVAC_VERSION);
		md.version = metad->btm_version;
		md.root = metad->btm_root;
		md.level = metad->btm_level;
		md.fastroot = metad->btm_fastroot;
		md.fastlevel = metad->btm_fastlevel;
		md.oldest_btpo_xact = oldestBtpoXact;
		md.last_cleanup_num_heap_tuples = numHeapTuples;

		XLogRegisterBufData(0, (char *) &md, sizeof(xl_btree_metadata));

		recptr = XLogInsert(RM_BTREE_ID, XLOG_BTREE_META_CLEANUP);

		PageSetLSN(metapg, recptr);
	}

	END_CRIT_SECTION();
	_bt_relbuf(rel, metabuf);
}
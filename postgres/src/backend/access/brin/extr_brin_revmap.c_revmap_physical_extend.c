#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ targetBlk; } ;
typedef  TYPE_1__ xl_brin_revmap_extend ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {scalar_t__ lastRevmapPage; } ;
struct TYPE_9__ {scalar_t__ rm_lastRevmapPage; int /*<<< orphan*/  rm_metaBuf; int /*<<< orphan*/  rm_irel; int /*<<< orphan*/  rm_pagesPerRange; } ;
struct TYPE_8__ {int pd_lower; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_3__ BrinRevmap ;
typedef  TYPE_4__ BrinMetaPageData ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BRIN_IS_REGULAR_PAGE (scalar_t__) ; 
 int /*<<< orphan*/  BRIN_PAGETYPE_REVMAP ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BrinPageType (scalar_t__) ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ P_NEW ; 
 scalar_t__ PageGetContents (scalar_t__) ; 
 int /*<<< orphan*/  PageIsNew (scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RELATION_IS_LOCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RM_BRIN_ID ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfBrinRevmapExtend ; 
 int /*<<< orphan*/  UnlockRelationForExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_BRIN_REVMAP_EXTEND ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_evacuate_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_page_init (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ brin_start_evacuating_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
revmap_physical_extend(BrinRevmap *revmap)
{
	Buffer		buf;
	Page		page;
	Page		metapage;
	BrinMetaPageData *metadata;
	BlockNumber mapBlk;
	BlockNumber nblocks;
	Relation	irel = revmap->rm_irel;
	bool		needLock = !RELATION_IS_LOCAL(irel);

	/*
	 * Lock the metapage. This locks out concurrent extensions of the revmap,
	 * but note that we still need to grab the relation extension lock because
	 * another backend can extend the index with regular BRIN pages.
	 */
	LockBuffer(revmap->rm_metaBuf, BUFFER_LOCK_EXCLUSIVE);
	metapage = BufferGetPage(revmap->rm_metaBuf);
	metadata = (BrinMetaPageData *) PageGetContents(metapage);

	/*
	 * Check that our cached lastRevmapPage value was up-to-date; if it
	 * wasn't, update the cached copy and have caller start over.
	 */
	if (metadata->lastRevmapPage != revmap->rm_lastRevmapPage)
	{
		revmap->rm_lastRevmapPage = metadata->lastRevmapPage;
		LockBuffer(revmap->rm_metaBuf, BUFFER_LOCK_UNLOCK);
		return;
	}
	mapBlk = metadata->lastRevmapPage + 1;

	nblocks = RelationGetNumberOfBlocks(irel);
	if (mapBlk < nblocks)
	{
		buf = ReadBuffer(irel, mapBlk);
		LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);
		page = BufferGetPage(buf);
	}
	else
	{
		if (needLock)
			LockRelationForExtension(irel, ExclusiveLock);

		buf = ReadBuffer(irel, P_NEW);
		if (BufferGetBlockNumber(buf) != mapBlk)
		{
			/*
			 * Very rare corner case: somebody extended the relation
			 * concurrently after we read its length.  If this happens, give
			 * up and have caller start over.  We will have to evacuate that
			 * page from under whoever is using it.
			 */
			if (needLock)
				UnlockRelationForExtension(irel, ExclusiveLock);
			LockBuffer(revmap->rm_metaBuf, BUFFER_LOCK_UNLOCK);
			ReleaseBuffer(buf);
			return;
		}
		LockBuffer(buf, BUFFER_LOCK_EXCLUSIVE);
		page = BufferGetPage(buf);

		if (needLock)
			UnlockRelationForExtension(irel, ExclusiveLock);
	}

	/* Check that it's a regular block (or an empty page) */
	if (!PageIsNew(page) && !BRIN_IS_REGULAR_PAGE(page))
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg("unexpected page type 0x%04X in BRIN index \"%s\" block %u",
						BrinPageType(page),
						RelationGetRelationName(irel),
						BufferGetBlockNumber(buf))));

	/* If the page is in use, evacuate it and restart */
	if (brin_start_evacuating_page(irel, buf))
	{
		LockBuffer(revmap->rm_metaBuf, BUFFER_LOCK_UNLOCK);
		brin_evacuate_page(irel, revmap->rm_pagesPerRange, revmap, buf);

		/* have caller start over */
		return;
	}

	/*
	 * Ok, we have now locked the metapage and the target block. Re-initialize
	 * the target block as a revmap page, and update the metapage.
	 */
	START_CRIT_SECTION();

	/* the rm_tids array is initialized to all invalid by PageInit */
	brin_page_init(page, BRIN_PAGETYPE_REVMAP);
	MarkBufferDirty(buf);

	metadata->lastRevmapPage = mapBlk;

	/*
	 * Set pd_lower just past the end of the metadata.  This is essential,
	 * because without doing so, metadata will be lost if xlog.c compresses
	 * the page.  (We must do this here because pre-v11 versions of PG did not
	 * set the metapage's pd_lower correctly, so a pg_upgraded index might
	 * contain the wrong value.)
	 */
	((PageHeader) metapage)->pd_lower =
		((char *) metadata + sizeof(BrinMetaPageData)) - (char *) metapage;

	MarkBufferDirty(revmap->rm_metaBuf);

	if (RelationNeedsWAL(revmap->rm_irel))
	{
		xl_brin_revmap_extend xlrec;
		XLogRecPtr	recptr;

		xlrec.targetBlk = mapBlk;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfBrinRevmapExtend);
		XLogRegisterBuffer(0, revmap->rm_metaBuf, REGBUF_STANDARD);

		XLogRegisterBuffer(1, buf, REGBUF_WILL_INIT);

		recptr = XLogInsert(RM_BRIN_ID, XLOG_BRIN_REVMAP_EXTEND);
		PageSetLSN(metapage, recptr);
		PageSetLSN(page, recptr);
	}

	END_CRIT_SECTION();

	LockBuffer(revmap->rm_metaBuf, BUFFER_LOCK_UNLOCK);

	UnlockReleaseBuffer(buf);
}
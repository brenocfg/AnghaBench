#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_22__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_27__ {void* buf; TYPE_3__* downlink; } ;
struct TYPE_26__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_23__ {scalar_t__ blkno; int num; } ;
struct TYPE_25__ {void* buffer; struct TYPE_25__* next; void* page; TYPE_1__ block; scalar_t__ list; TYPE_3__* itup; int /*<<< orphan*/  lenlist; } ;
struct TYPE_24__ {scalar_t__ rightlink; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ SplitedPageLayout ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Page ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Item ;
typedef  TYPE_3__* IndexTuple ;
typedef  int /*<<< orphan*/  GistNSN ;
typedef  int /*<<< orphan*/  GISTSTATE ;
typedef  TYPE_4__ GISTPageSplitInfo ;
typedef  void* Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 void* BufferGetBlockNumber (void*) ; 
 void* BufferGetPage (void*) ; 
 scalar_t__ BufferIsValid (void*) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_LEAF ; 
 int FirstOffsetNumber ; 
 int /*<<< orphan*/  GISTInitBuffer (void*,int /*<<< orphan*/ ) ; 
 int GIST_MAX_SPLIT_PAGES ; 
 scalar_t__ GIST_ROOT_BLKNO ; 
 int /*<<< orphan*/  GistBuildLSN ; 
 int /*<<< orphan*/  GistClearFollowRight (void*) ; 
 scalar_t__ GistFollowRight (void*) ; 
 int /*<<< orphan*/  GistMarkFollowRight (void*) ; 
 int /*<<< orphan*/  GistPageGetNSN (void*) ; 
 TYPE_22__* GistPageGetOpaque (void*) ; 
 scalar_t__ GistPageHasGarbage (void*) ; 
 scalar_t__ GistPageIsLeaf (void*) ; 
 int /*<<< orphan*/  GistPageSetNSN (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GistTupleSetValid (TYPE_3__*) ; 
 int /*<<< orphan*/  IndexTupleSize (TYPE_3__*) ; 
 scalar_t__ InvalidBlockNumber ; 
 scalar_t__ InvalidOffsetNumber ; 
 scalar_t__ ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSetBlockNumber (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  MarkBufferDirty (void*) ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ OffsetNumberIsValid (int) ; 
 scalar_t__ PageAddItem (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 void* PageGetTempPageCopySpecial (void*) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (void*,int) ; 
 int /*<<< orphan*/  PageIndexTupleOverwrite (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageRestoreTempPage (void*,void*) ; 
 int /*<<< orphan*/  PageSetLSN (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPageSplit (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (void*) ; 
 int /*<<< orphan*/  XLogEnsureRecordSpace (int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gistGetFakeLSN (int /*<<< orphan*/ ) ; 
 void* gistNewBuffer (int /*<<< orphan*/ ) ; 
 TYPE_2__* gistSplit (int /*<<< orphan*/ ,void*,TYPE_3__**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gistXLogSplit (int,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  gistXLogUpdate (void*,int*,int,TYPE_3__**,int,void*) ; 
 TYPE_3__** gistextractpage (void*,int*) ; 
 int /*<<< orphan*/  gistfillbuffer (void*,TYPE_3__**,int,scalar_t__) ; 
 scalar_t__ gistfillitupvec (TYPE_3__**,int,int /*<<< orphan*/ *) ; 
 TYPE_3__** gistjoinvector (TYPE_3__**,int*,TYPE_3__**,int) ; 
 int gistnospace (void*,TYPE_3__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gistprunepage (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  memmove (TYPE_3__**,TYPE_3__**,int) ; 
 void* palloc (int) ; 

bool
gistplacetopage(Relation rel, Size freespace, GISTSTATE *giststate,
				Buffer buffer,
				IndexTuple *itup, int ntup, OffsetNumber oldoffnum,
				BlockNumber *newblkno,
				Buffer leftchildbuf,
				List **splitinfo,
				bool markfollowright,
				Relation heapRel,
				bool is_build)
{
	BlockNumber blkno = BufferGetBlockNumber(buffer);
	Page		page = BufferGetPage(buffer);
	bool		is_leaf = (GistPageIsLeaf(page)) ? true : false;
	XLogRecPtr	recptr;
	int			i;
	bool		is_split;

	/*
	 * Refuse to modify a page that's incompletely split. This should not
	 * happen because we finish any incomplete splits while we walk down the
	 * tree. However, it's remotely possible that another concurrent inserter
	 * splits a parent page, and errors out before completing the split. We
	 * will just throw an error in that case, and leave any split we had in
	 * progress unfinished too. The next insert that comes along will clean up
	 * the mess.
	 */
	if (GistFollowRight(page))
		elog(ERROR, "concurrent GiST page split was incomplete");

	*splitinfo = NIL;

	/*
	 * if isupdate, remove old key: This node's key has been modified, either
	 * because a child split occurred or because we needed to adjust our key
	 * for an insert in a child node. Therefore, remove the old version of
	 * this node's key.
	 *
	 * for WAL replay, in the non-split case we handle this by setting up a
	 * one-element todelete array; in the split case, it's handled implicitly
	 * because the tuple vector passed to gistSplit won't include this tuple.
	 */
	is_split = gistnospace(page, itup, ntup, oldoffnum, freespace);

	/*
	 * If leaf page is full, try at first to delete dead tuples. And then
	 * check again.
	 */
	if (is_split && GistPageIsLeaf(page) && GistPageHasGarbage(page))
	{
		gistprunepage(rel, page, buffer, heapRel);
		is_split = gistnospace(page, itup, ntup, oldoffnum, freespace);
	}

	if (is_split)
	{
		/* no space for insertion */
		IndexTuple *itvec;
		int			tlen;
		SplitedPageLayout *dist = NULL,
				   *ptr;
		BlockNumber oldrlink = InvalidBlockNumber;
		GistNSN		oldnsn = 0;
		SplitedPageLayout rootpg;
		bool		is_rootsplit;
		int			npage;

		is_rootsplit = (blkno == GIST_ROOT_BLKNO);

		/*
		 * Form index tuples vector to split. If we're replacing an old tuple,
		 * remove the old version from the vector.
		 */
		itvec = gistextractpage(page, &tlen);
		if (OffsetNumberIsValid(oldoffnum))
		{
			/* on inner page we should remove old tuple */
			int			pos = oldoffnum - FirstOffsetNumber;

			tlen--;
			if (pos != tlen)
				memmove(itvec + pos, itvec + pos + 1, sizeof(IndexTuple) * (tlen - pos));
		}
		itvec = gistjoinvector(itvec, &tlen, itup, ntup);
		dist = gistSplit(rel, page, itvec, tlen, giststate);

		/*
		 * Check that split didn't produce too many pages.
		 */
		npage = 0;
		for (ptr = dist; ptr; ptr = ptr->next)
			npage++;
		/* in a root split, we'll add one more page to the list below */
		if (is_rootsplit)
			npage++;
		if (npage > GIST_MAX_SPLIT_PAGES)
			elog(ERROR, "GiST page split into too many halves (%d, maximum %d)",
				 npage, GIST_MAX_SPLIT_PAGES);

		/*
		 * Set up pages to work with. Allocate new buffers for all but the
		 * leftmost page. The original page becomes the new leftmost page, and
		 * is just replaced with the new contents.
		 *
		 * For a root-split, allocate new buffers for all child pages, the
		 * original page is overwritten with new root page containing
		 * downlinks to the new child pages.
		 */
		ptr = dist;
		if (!is_rootsplit)
		{
			/* save old rightlink and NSN */
			oldrlink = GistPageGetOpaque(page)->rightlink;
			oldnsn = GistPageGetNSN(page);

			dist->buffer = buffer;
			dist->block.blkno = BufferGetBlockNumber(buffer);
			dist->page = PageGetTempPageCopySpecial(BufferGetPage(buffer));

			/* clean all flags except F_LEAF */
			GistPageGetOpaque(dist->page)->flags = (is_leaf) ? F_LEAF : 0;

			ptr = ptr->next;
		}
		for (; ptr; ptr = ptr->next)
		{
			/* Allocate new page */
			ptr->buffer = gistNewBuffer(rel);
			GISTInitBuffer(ptr->buffer, (is_leaf) ? F_LEAF : 0);
			ptr->page = BufferGetPage(ptr->buffer);
			ptr->block.blkno = BufferGetBlockNumber(ptr->buffer);
			PredicateLockPageSplit(rel,
								   BufferGetBlockNumber(buffer),
								   BufferGetBlockNumber(ptr->buffer));
		}

		/*
		 * Now that we know which blocks the new pages go to, set up downlink
		 * tuples to point to them.
		 */
		for (ptr = dist; ptr; ptr = ptr->next)
		{
			ItemPointerSetBlockNumber(&(ptr->itup->t_tid), ptr->block.blkno);
			GistTupleSetValid(ptr->itup);
		}

		/*
		 * If this is a root split, we construct the new root page with the
		 * downlinks here directly, instead of requiring the caller to insert
		 * them. Add the new root page to the list along with the child pages.
		 */
		if (is_rootsplit)
		{
			IndexTuple *downlinks;
			int			ndownlinks = 0;
			int			i;

			rootpg.buffer = buffer;
			rootpg.page = PageGetTempPageCopySpecial(BufferGetPage(rootpg.buffer));
			GistPageGetOpaque(rootpg.page)->flags = 0;

			/* Prepare a vector of all the downlinks */
			for (ptr = dist; ptr; ptr = ptr->next)
				ndownlinks++;
			downlinks = palloc(sizeof(IndexTuple) * ndownlinks);
			for (i = 0, ptr = dist; ptr; ptr = ptr->next)
				downlinks[i++] = ptr->itup;

			rootpg.block.blkno = GIST_ROOT_BLKNO;
			rootpg.block.num = ndownlinks;
			rootpg.list = gistfillitupvec(downlinks, ndownlinks,
										  &(rootpg.lenlist));
			rootpg.itup = NULL;

			rootpg.next = dist;
			dist = &rootpg;
		}
		else
		{
			/* Prepare split-info to be returned to caller */
			for (ptr = dist; ptr; ptr = ptr->next)
			{
				GISTPageSplitInfo *si = palloc(sizeof(GISTPageSplitInfo));

				si->buf = ptr->buffer;
				si->downlink = ptr->itup;
				*splitinfo = lappend(*splitinfo, si);
			}
		}

		/*
		 * Fill all pages. All the pages are new, ie. freshly allocated empty
		 * pages, or a temporary copy of the old page.
		 */
		for (ptr = dist; ptr; ptr = ptr->next)
		{
			char	   *data = (char *) (ptr->list);

			for (i = 0; i < ptr->block.num; i++)
			{
				IndexTuple	thistup = (IndexTuple) data;

				if (PageAddItem(ptr->page, (Item) data, IndexTupleSize(thistup), i + FirstOffsetNumber, false, false) == InvalidOffsetNumber)
					elog(ERROR, "failed to add item to index page in \"%s\"", RelationGetRelationName(rel));

				/*
				 * If this is the first inserted/updated tuple, let the caller
				 * know which page it landed on.
				 */
				if (newblkno && ItemPointerEquals(&thistup->t_tid, &(*itup)->t_tid))
					*newblkno = ptr->block.blkno;

				data += IndexTupleSize(thistup);
			}

			/* Set up rightlinks */
			if (ptr->next && ptr->block.blkno != GIST_ROOT_BLKNO)
				GistPageGetOpaque(ptr->page)->rightlink =
					ptr->next->block.blkno;
			else
				GistPageGetOpaque(ptr->page)->rightlink = oldrlink;

			/*
			 * Mark the all but the right-most page with the follow-right
			 * flag. It will be cleared as soon as the downlink is inserted
			 * into the parent, but this ensures that if we error out before
			 * that, the index is still consistent. (in buffering build mode,
			 * any error will abort the index build anyway, so this is not
			 * needed.)
			 */
			if (ptr->next && !is_rootsplit && markfollowright)
				GistMarkFollowRight(ptr->page);
			else
				GistClearFollowRight(ptr->page);

			/*
			 * Copy the NSN of the original page to all pages. The
			 * F_FOLLOW_RIGHT flags ensure that scans will follow the
			 * rightlinks until the downlinks are inserted.
			 */
			GistPageSetNSN(ptr->page, oldnsn);
		}

		/*
		 * gistXLogSplit() needs to WAL log a lot of pages, prepare WAL
		 * insertion for that. NB: The number of pages and data segments
		 * specified here must match the calculations in gistXLogSplit()!
		 */
		if (!is_build && RelationNeedsWAL(rel))
			XLogEnsureRecordSpace(npage, 1 + npage * 2);

		START_CRIT_SECTION();

		/*
		 * Must mark buffers dirty before XLogInsert, even though we'll still
		 * be changing their opaque fields below.
		 */
		for (ptr = dist; ptr; ptr = ptr->next)
			MarkBufferDirty(ptr->buffer);
		if (BufferIsValid(leftchildbuf))
			MarkBufferDirty(leftchildbuf);

		/*
		 * The first page in the chain was a temporary working copy meant to
		 * replace the old page. Copy it over the old page.
		 */
		PageRestoreTempPage(dist->page, BufferGetPage(dist->buffer));
		dist->page = BufferGetPage(dist->buffer);

		/*
		 * Write the WAL record.
		 *
		 * If we're building a new index, however, we don't WAL-log changes
		 * yet. The LSN-NSN interlock between parent and child requires that
		 * LSNs never move backwards, so set the LSNs to a value that's
		 * smaller than any real or fake unlogged LSN that might be generated
		 * later. (There can't be any concurrent scans during index build, so
		 * we don't need to be able to detect concurrent splits yet.)
		 */
		if (is_build)
			recptr = GistBuildLSN;
		else
		{
			if (RelationNeedsWAL(rel))
				recptr = gistXLogSplit(is_leaf,
									   dist, oldrlink, oldnsn, leftchildbuf,
									   markfollowright);
			else
				recptr = gistGetFakeLSN(rel);
		}

		for (ptr = dist; ptr; ptr = ptr->next)
			PageSetLSN(ptr->page, recptr);

		/*
		 * Return the new child buffers to the caller.
		 *
		 * If this was a root split, we've already inserted the downlink
		 * pointers, in the form of a new root page. Therefore we can release
		 * all the new buffers, and keep just the root page locked.
		 */
		if (is_rootsplit)
		{
			for (ptr = dist->next; ptr; ptr = ptr->next)
				UnlockReleaseBuffer(ptr->buffer);
		}
	}
	else
	{
		/*
		 * Enough space.  We always get here if ntup==0.
		 */
		START_CRIT_SECTION();

		/*
		 * Delete old tuple if any, then insert new tuple(s) if any.  If
		 * possible, use the fast path of PageIndexTupleOverwrite.
		 */
		if (OffsetNumberIsValid(oldoffnum))
		{
			if (ntup == 1)
			{
				/* One-for-one replacement, so use PageIndexTupleOverwrite */
				if (!PageIndexTupleOverwrite(page, oldoffnum, (Item) *itup,
											 IndexTupleSize(*itup)))
					elog(ERROR, "failed to add item to index page in \"%s\"",
						 RelationGetRelationName(rel));
			}
			else
			{
				/* Delete old, then append new tuple(s) to page */
				PageIndexTupleDelete(page, oldoffnum);
				gistfillbuffer(page, itup, ntup, InvalidOffsetNumber);
			}
		}
		else
		{
			/* Just append new tuples at the end of the page */
			gistfillbuffer(page, itup, ntup, InvalidOffsetNumber);
		}

		MarkBufferDirty(buffer);

		if (BufferIsValid(leftchildbuf))
			MarkBufferDirty(leftchildbuf);

		if (is_build)
			recptr = GistBuildLSN;
		else
		{
			if (RelationNeedsWAL(rel))
			{
				OffsetNumber ndeloffs = 0,
							deloffs[1];

				if (OffsetNumberIsValid(oldoffnum))
				{
					deloffs[0] = oldoffnum;
					ndeloffs = 1;
				}

				recptr = gistXLogUpdate(buffer,
										deloffs, ndeloffs, itup, ntup,
										leftchildbuf);
			}
			else
				recptr = gistGetFakeLSN(rel);
		}
		PageSetLSN(page, recptr);

		if (newblkno)
			*newblkno = blkno;
	}

	/*
	 * If we inserted the downlink for a child page, set NSN and clear
	 * F_FOLLOW_RIGHT flag on the left child, so that concurrent scans know to
	 * follow the rightlink if and only if they looked at the parent page
	 * before we inserted the downlink.
	 *
	 * Note that we do this *after* writing the WAL record. That means that
	 * the possible full page image in the WAL record does not include these
	 * changes, and they must be replayed even if the page is restored from
	 * the full page image. There's a chicken-and-egg problem: if we updated
	 * the child pages first, we wouldn't know the recptr of the WAL record
	 * we're about to write.
	 */
	if (BufferIsValid(leftchildbuf))
	{
		Page		leftpg = BufferGetPage(leftchildbuf);

		GistPageSetNSN(leftpg, recptr);
		GistClearFollowRight(leftpg);

		PageSetLSN(leftpg, recptr);
	}

	END_CRIT_SECTION();

	return is_split;
}
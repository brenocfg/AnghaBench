#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_3__ {scalar_t__ blkno; int freeSpace; } ;
typedef  TYPE_1__ SpGistLastUsedPage ;
typedef  int /*<<< orphan*/  SpGistCache ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConditionalLockBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GBUF_REQ_LEAF (int) ; 
 scalar_t__ GBUF_REQ_NULLS (int) ; 
 TYPE_1__* GET_LUP (int /*<<< orphan*/ *,int) ; 
 scalar_t__ InvalidBlockNumber ; 
 int Min (int,int) ; 
 int PageGetExactFreeSpace (int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsEmpty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RelationGetTargetPageFreeSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPGIST_DEFAULT_FILLFACTOR ; 
 int /*<<< orphan*/  SPGIST_LEAF ; 
 int /*<<< orphan*/  SPGIST_NULLS ; 
 int SPGIST_PAGE_CAPACITY ; 
 int /*<<< orphan*/  SpGistBlockIsFixed (scalar_t__) ; 
 int /*<<< orphan*/  SpGistInitBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SpGistPageIsDeleted (int /*<<< orphan*/ ) ; 
 int SpGistPageIsLeaf (int /*<<< orphan*/ ) ; 
 int SpGistPageStoresNulls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allocNewBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * spgGetCache (int /*<<< orphan*/ ) ; 

Buffer
SpGistGetBuffer(Relation index, int flags, int needSpace, bool *isNew)
{
	SpGistCache *cache = spgGetCache(index);
	SpGistLastUsedPage *lup;

	/* Bail out if even an empty page wouldn't meet the demand */
	if (needSpace > SPGIST_PAGE_CAPACITY)
		elog(ERROR, "desired SPGiST tuple size is too big");

	/*
	 * If possible, increase the space request to include relation's
	 * fillfactor.  This ensures that when we add unrelated tuples to a page,
	 * we try to keep 100-fillfactor% available for adding tuples that are
	 * related to the ones already on it.  But fillfactor mustn't cause an
	 * error for requests that would otherwise be legal.
	 */
	needSpace += RelationGetTargetPageFreeSpace(index,
												SPGIST_DEFAULT_FILLFACTOR);
	needSpace = Min(needSpace, SPGIST_PAGE_CAPACITY);

	/* Get the cache entry for this flags setting */
	lup = GET_LUP(cache, flags);

	/* If we have nothing cached, just turn it over to allocNewBuffer */
	if (lup->blkno == InvalidBlockNumber)
	{
		*isNew = true;
		return allocNewBuffer(index, flags);
	}

	/* fixed pages should never be in cache */
	Assert(!SpGistBlockIsFixed(lup->blkno));

	/* If cached freeSpace isn't enough, don't bother looking at the page */
	if (lup->freeSpace >= needSpace)
	{
		Buffer		buffer;
		Page		page;

		buffer = ReadBuffer(index, lup->blkno);

		if (!ConditionalLockBuffer(buffer))
		{
			/*
			 * buffer is locked by another process, so return a new buffer
			 */
			ReleaseBuffer(buffer);
			*isNew = true;
			return allocNewBuffer(index, flags);
		}

		page = BufferGetPage(buffer);

		if (PageIsNew(page) || SpGistPageIsDeleted(page) || PageIsEmpty(page))
		{
			/* OK to initialize the page */
			uint16		pageflags = 0;

			if (GBUF_REQ_LEAF(flags))
				pageflags |= SPGIST_LEAF;
			if (GBUF_REQ_NULLS(flags))
				pageflags |= SPGIST_NULLS;
			SpGistInitBuffer(buffer, pageflags);
			lup->freeSpace = PageGetExactFreeSpace(page) - needSpace;
			*isNew = true;
			return buffer;
		}

		/*
		 * Check that page is of right type and has enough space.  We must
		 * recheck this since our cache isn't necessarily up to date.
		 */
		if ((GBUF_REQ_LEAF(flags) ? SpGistPageIsLeaf(page) : !SpGistPageIsLeaf(page)) &&
			(GBUF_REQ_NULLS(flags) ? SpGistPageStoresNulls(page) : !SpGistPageStoresNulls(page)))
		{
			int			freeSpace = PageGetExactFreeSpace(page);

			if (freeSpace >= needSpace)
			{
				/* Success, update freespace info and return the buffer */
				lup->freeSpace = freeSpace - needSpace;
				*isNew = false;
				return buffer;
			}
		}

		/*
		 * fallback to allocation of new buffer
		 */
		UnlockReleaseBuffer(buffer);
	}

	/* No success with cache, so return a new buffer */
	*isNew = true;
	return allocNewBuffer(index, flags);
}
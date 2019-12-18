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
struct TYPE_3__ {scalar_t__ blkno; int freeSpace; } ;
typedef  TYPE_1__ SpGistLastUsedPage ;
typedef  int /*<<< orphan*/  SpGistCache ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int GBUF_INNER_PARITY (scalar_t__) ; 
 int GBUF_LEAF ; 
 int GBUF_NULLS ; 
 TYPE_1__* GET_LUP (int /*<<< orphan*/ *,int) ; 
 scalar_t__ InvalidBlockNumber ; 
 int PageGetExactFreeSpace (int /*<<< orphan*/ ) ; 
 scalar_t__ SpGistBlockIsFixed (scalar_t__) ; 
 scalar_t__ SpGistPageIsLeaf (int /*<<< orphan*/ ) ; 
 scalar_t__ SpGistPageStoresNulls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spgGetCache (int /*<<< orphan*/ ) ; 

void
SpGistSetLastUsedPage(Relation index, Buffer buffer)
{
	SpGistCache *cache = spgGetCache(index);
	SpGistLastUsedPage *lup;
	int			freeSpace;
	Page		page = BufferGetPage(buffer);
	BlockNumber blkno = BufferGetBlockNumber(buffer);
	int			flags;

	/* Never enter fixed pages (root pages) in cache, though */
	if (SpGistBlockIsFixed(blkno))
		return;

	if (SpGistPageIsLeaf(page))
		flags = GBUF_LEAF;
	else
		flags = GBUF_INNER_PARITY(blkno);
	if (SpGistPageStoresNulls(page))
		flags |= GBUF_NULLS;

	lup = GET_LUP(cache, flags);

	freeSpace = PageGetExactFreeSpace(page);
	if (lup->blkno == InvalidBlockNumber || lup->blkno == blkno ||
		lup->freeSpace < freeSpace)
	{
		lup->blkno = blkno;
		lup->freeSpace = freeSpace;
	}
}
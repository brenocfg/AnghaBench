#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
struct TYPE_6__ {TYPE_1__* cachedPage; } ;
struct TYPE_7__ {TYPE_2__ lastUsedPages; } ;
struct TYPE_5__ {int /*<<< orphan*/  freeSpace; int /*<<< orphan*/  blkno; } ;
typedef  TYPE_3__ SpGistCache ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int GBUF_INNER_PARITY (int /*<<< orphan*/ ) ; 
 int GBUF_NULLS ; 
 int GBUF_PARITY_MASK ; 
 scalar_t__ GBUF_REQ_LEAF (int) ; 
 scalar_t__ GBUF_REQ_NULLS (int) ; 
 int /*<<< orphan*/  PageGetExactFreeSpace (int /*<<< orphan*/ ) ; 
 int SPGIST_LEAF ; 
 int SPGIST_NULLS ; 
 int /*<<< orphan*/  SpGistInitBuffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SpGistNewBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 TYPE_3__* spgGetCache (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Buffer
allocNewBuffer(Relation index, int flags)
{
	SpGistCache *cache = spgGetCache(index);
	uint16		pageflags = 0;

	if (GBUF_REQ_LEAF(flags))
		pageflags |= SPGIST_LEAF;
	if (GBUF_REQ_NULLS(flags))
		pageflags |= SPGIST_NULLS;

	for (;;)
	{
		Buffer		buffer;

		buffer = SpGistNewBuffer(index);
		SpGistInitBuffer(buffer, pageflags);

		if (pageflags & SPGIST_LEAF)
		{
			/* Leaf pages have no parity concerns, so just use it */
			return buffer;
		}
		else
		{
			BlockNumber blkno = BufferGetBlockNumber(buffer);
			int			blkFlags = GBUF_INNER_PARITY(blkno);

			if ((flags & GBUF_PARITY_MASK) == blkFlags)
			{
				/* Page has right parity, use it */
				return buffer;
			}
			else
			{
				/* Page has wrong parity, record it in cache and try again */
				if (pageflags & SPGIST_NULLS)
					blkFlags |= GBUF_NULLS;
				cache->lastUsedPages.cachedPage[blkFlags].blkno = blkno;
				cache->lastUsedPages.cachedPage[blkFlags].freeSpace =
					PageGetExactFreeSpace(BufferGetPage(buffer));
				UnlockReleaseBuffer(buffer);
			}
		}
	}
}
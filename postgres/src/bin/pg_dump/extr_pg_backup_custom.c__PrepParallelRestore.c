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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pgoff_t ;
struct TYPE_6__ {scalar_t__ dataState; scalar_t__ dataPos; } ;
typedef  TYPE_1__ lclTocEntry ;
struct TYPE_7__ {scalar_t__ hasSeek; } ;
typedef  TYPE_2__ lclContext ;
struct TYPE_8__ {scalar_t__ dataLength; scalar_t__ formatData; struct TYPE_8__* next; } ;
typedef  TYPE_3__ TocEntry ;
struct TYPE_9__ {int /*<<< orphan*/  FH; TYPE_3__* toc; scalar_t__ formatData; } ;
typedef  TYPE_4__ ArchiveHandle ;

/* Variables and functions */
 scalar_t__ K_OFFSET_POS_SET ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftello (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_PrepParallelRestore(ArchiveHandle *AH)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	TocEntry   *prev_te = NULL;
	lclTocEntry *prev_tctx = NULL;
	TocEntry   *te;

	/*
	 * Knowing that the data items were dumped out in TOC order, we can
	 * reconstruct the length of each item as the delta to the start offset of
	 * the next data item.
	 */
	for (te = AH->toc->next; te != AH->toc; te = te->next)
	{
		lclTocEntry *tctx = (lclTocEntry *) te->formatData;

		/*
		 * Ignore entries without a known data offset; if we were unable to
		 * seek to rewrite the TOC when creating the archive, this'll be all
		 * of them, and we'll end up with no size estimates.
		 */
		if (tctx->dataState != K_OFFSET_POS_SET)
			continue;

		/* Compute previous data item's length */
		if (prev_te)
		{
			if (tctx->dataPos > prev_tctx->dataPos)
				prev_te->dataLength = tctx->dataPos - prev_tctx->dataPos;
		}

		prev_te = te;
		prev_tctx = tctx;
	}

	/* If OK to seek, we can determine the length of the last item */
	if (prev_te && ctx->hasSeek)
	{
		pgoff_t		endpos;

		if (fseeko(AH->FH, 0, SEEK_END) != 0)
			fatal("error during file seek: %m");
		endpos = ftello(AH->FH);
		if (endpos > prev_tctx->dataPos)
			prev_te->dataLength = endpos - prev_tctx->dataPos;
	}
}
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
struct TYPE_5__ {scalar_t__ lastRevmapPage; int /*<<< orphan*/  pagesPerRange; } ;
struct TYPE_4__ {scalar_t__ revmapNumPages; int /*<<< orphan*/  pagesPerRange; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_1__ BrinStatsData ;
typedef  TYPE_2__ BrinMetaPageData ;

/* Variables and functions */
 int /*<<< orphan*/  BRIN_METAPAGE_BLKNO ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetContents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 

void
brinGetStats(Relation index, BrinStatsData *stats)
{
	Buffer		metabuffer;
	Page		metapage;
	BrinMetaPageData *metadata;

	metabuffer = ReadBuffer(index, BRIN_METAPAGE_BLKNO);
	LockBuffer(metabuffer, BUFFER_LOCK_SHARE);
	metapage = BufferGetPage(metabuffer);
	metadata = (BrinMetaPageData *) PageGetContents(metapage);

	stats->pagesPerRange = metadata->pagesPerRange;
	stats->revmapNumPages = metadata->lastRevmapPage - 1;

	UnlockReleaseBuffer(metabuffer);
}
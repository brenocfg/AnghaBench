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
struct TYPE_10__ {int pd_lower; } ;
struct TYPE_7__ {TYPE_2__* cachedPage; } ;
struct TYPE_9__ {TYPE_1__ lastUsedPages; int /*<<< orphan*/  magicNumber; } ;
struct TYPE_8__ {int /*<<< orphan*/  blkno; } ;
typedef  TYPE_3__ SpGistMetaPageData ;
typedef  TYPE_4__* PageHeader ;
typedef  scalar_t__ Page ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int SPGIST_CACHED_PAGES ; 
 int /*<<< orphan*/  SPGIST_MAGIC_NUMBER ; 
 int /*<<< orphan*/  SPGIST_META ; 
 int /*<<< orphan*/  SpGistInitPage (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* SpGistPageGetMeta (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void
SpGistInitMetapage(Page page)
{
	SpGistMetaPageData *metadata;
	int			i;

	SpGistInitPage(page, SPGIST_META);
	metadata = SpGistPageGetMeta(page);
	memset(metadata, 0, sizeof(SpGistMetaPageData));
	metadata->magicNumber = SPGIST_MAGIC_NUMBER;

	/* initialize last-used-page cache to empty */
	for (i = 0; i < SPGIST_CACHED_PAGES; i++)
		metadata->lastUsedPages.cachedPage[i].blkno = InvalidBlockNumber;

	/*
	 * Set pd_lower just past the end of the metadata.  This is essential,
	 * because without doing so, metadata will be lost if xlog.c compresses
	 * the page.
	 */
	((PageHeader) page)->pd_lower =
		((char *) metadata + sizeof(SpGistMetaPageData)) - (char *) page;
}
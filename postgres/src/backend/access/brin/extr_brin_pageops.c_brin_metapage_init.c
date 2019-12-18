#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {scalar_t__ lastRevmapPage; int /*<<< orphan*/  pagesPerRange; int /*<<< orphan*/  brinVersion; int /*<<< orphan*/  brinMagic; } ;
struct TYPE_3__ {int pd_lower; } ;
typedef  TYPE_1__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  TYPE_2__ BrinMetaPageData ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BRIN_META_MAGIC ; 
 int /*<<< orphan*/  BRIN_PAGETYPE_META ; 
 scalar_t__ PageGetContents (scalar_t__) ; 
 int /*<<< orphan*/  brin_page_init (scalar_t__,int /*<<< orphan*/ ) ; 

void
brin_metapage_init(Page page, BlockNumber pagesPerRange, uint16 version)
{
	BrinMetaPageData *metadata;

	brin_page_init(page, BRIN_PAGETYPE_META);

	metadata = (BrinMetaPageData *) PageGetContents(page);

	metadata->brinMagic = BRIN_META_MAGIC;
	metadata->brinVersion = version;
	metadata->pagesPerRange = pagesPerRange;

	/*
	 * Note we cheat here a little.  0 is not a valid revmap block number
	 * (because it's the metapage buffer), but doing this enables the first
	 * revmap page to be created when the index is.
	 */
	metadata->lastRevmapPage = 0;

	/*
	 * Set pd_lower just past the end of the metadata.  This is essential,
	 * because without doing so, metadata will be lost if xlog.c compresses
	 * the page.
	 */
	((PageHeader) page)->pd_lower =
		((char *) metadata + sizeof(BrinMetaPageData)) - (char *) page;
}
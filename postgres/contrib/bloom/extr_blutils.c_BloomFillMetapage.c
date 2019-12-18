#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  opts; int /*<<< orphan*/  magickNumber; } ;
struct TYPE_8__ {scalar_t__ pd_lower; scalar_t__ pd_upper; } ;
struct TYPE_7__ {scalar_t__ rd_options; } ;
typedef  TYPE_1__* Relation ;
typedef  TYPE_2__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  BloomOptions ;
typedef  TYPE_3__ BloomMetaPageData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BLOOM_MAGICK_NUMBER ; 
 int /*<<< orphan*/  BLOOM_META ; 
 int /*<<< orphan*/  BloomInitPage (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* BloomPageGetMeta (scalar_t__) ; 
 int /*<<< orphan*/ * makeDefaultBloomOptions () ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void
BloomFillMetapage(Relation index, Page metaPage)
{
	BloomOptions *opts;
	BloomMetaPageData *metadata;

	/*
	 * Choose the index's options.  If reloptions have been assigned, use
	 * those, otherwise create default options.
	 */
	opts = (BloomOptions *) index->rd_options;
	if (!opts)
		opts = makeDefaultBloomOptions();

	/*
	 * Initialize contents of meta page, including a copy of the options,
	 * which are now frozen for the life of the index.
	 */
	BloomInitPage(metaPage, BLOOM_META);
	metadata = BloomPageGetMeta(metaPage);
	memset(metadata, 0, sizeof(BloomMetaPageData));
	metadata->magickNumber = BLOOM_MAGICK_NUMBER;
	metadata->opts = *opts;
	((PageHeader) metaPage)->pd_lower += sizeof(BloomMetaPageData);

	/* If this fails, probably FreeBlockNumberArray size calc is wrong: */
	Assert(((PageHeader) metaPage)->pd_lower <= ((PageHeader) metaPage)->pd_upper);
}
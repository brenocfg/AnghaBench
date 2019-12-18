#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  free_space; } ;
typedef  TYPE_1__ pgstattuple_type ;
struct TYPE_6__ {int hasho_flag; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  HashPageOpaqueData ;
typedef  TYPE_2__* HashPageOpaque ;
typedef  int /*<<< orphan*/  BufferAccessStrategy ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FirstOffsetNumber ; 
 int /*<<< orphan*/  HASH_READ ; 
#define  LH_BITMAP_PAGE 132 
#define  LH_BUCKET_PAGE 131 
#define  LH_META_PAGE 130 
#define  LH_OVERFLOW_PAGE 129 
 int LH_PAGE_TYPE ; 
#define  LH_UNUSED_PAGE 128 
 scalar_t__ MAXALIGN (int) ; 
 int /*<<< orphan*/  PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_getbuf_with_strategy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_relbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_index_page (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgstat_hash_page(pgstattuple_type *stat, Relation rel, BlockNumber blkno,
				 BufferAccessStrategy bstrategy)
{
	Buffer		buf;
	Page		page;

	buf = _hash_getbuf_with_strategy(rel, blkno, HASH_READ, 0, bstrategy);
	page = BufferGetPage(buf);

	if (PageGetSpecialSize(page) == MAXALIGN(sizeof(HashPageOpaqueData)))
	{
		HashPageOpaque opaque;

		opaque = (HashPageOpaque) PageGetSpecialPointer(page);
		switch (opaque->hasho_flag & LH_PAGE_TYPE)
		{
			case LH_UNUSED_PAGE:
				stat->free_space += BLCKSZ;
				break;
			case LH_BUCKET_PAGE:
			case LH_OVERFLOW_PAGE:
				pgstat_index_page(stat, page, FirstOffsetNumber,
								  PageGetMaxOffsetNumber(page));
				break;
			case LH_BITMAP_PAGE:
			case LH_META_PAGE:
			default:
				break;
		}
	}
	else
	{
		/* maybe corrupted */
	}

	_hash_relbuf(rel, buf);
}
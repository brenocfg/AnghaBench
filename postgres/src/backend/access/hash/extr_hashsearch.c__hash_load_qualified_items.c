#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ hashso_sk_hash; int /*<<< orphan*/  hashso_buc_split; scalar_t__ hashso_buc_populated; } ;
struct TYPE_11__ {scalar_t__ ignore_killed_tuples; int /*<<< orphan*/  opaque; } ;
struct TYPE_10__ {int t_info; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  TYPE_1__* IndexTuple ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  TYPE_3__* HashScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FirstOffsetNumber ; 
 int INDEX_MOVED_BY_SPLIT_MASK ; 
 scalar_t__ ItemIdIsDead (int /*<<< orphan*/ ) ; 
 int MaxIndexTuplesPerPage ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ OffsetNumberPrev (scalar_t__) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 scalar_t__ _hash_checkqual (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ _hash_get_indextuple_hashkey (TYPE_1__*) ; 
 int /*<<< orphan*/  _hash_saveitem (TYPE_3__*,int,scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static int
_hash_load_qualified_items(IndexScanDesc scan, Page page,
						   OffsetNumber offnum, ScanDirection dir)
{
	HashScanOpaque so = (HashScanOpaque) scan->opaque;
	IndexTuple	itup;
	int			itemIndex;
	OffsetNumber maxoff;

	maxoff = PageGetMaxOffsetNumber(page);

	if (ScanDirectionIsForward(dir))
	{
		/* load items[] in ascending order */
		itemIndex = 0;

		while (offnum <= maxoff)
		{
			Assert(offnum >= FirstOffsetNumber);
			itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, offnum));

			/*
			 * skip the tuples that are moved by split operation for the scan
			 * that has started when split was in progress. Also, skip the
			 * tuples that are marked as dead.
			 */
			if ((so->hashso_buc_populated && !so->hashso_buc_split &&
				 (itup->t_info & INDEX_MOVED_BY_SPLIT_MASK)) ||
				(scan->ignore_killed_tuples &&
				 (ItemIdIsDead(PageGetItemId(page, offnum)))))
			{
				offnum = OffsetNumberNext(offnum);	/* move forward */
				continue;
			}

			if (so->hashso_sk_hash == _hash_get_indextuple_hashkey(itup) &&
				_hash_checkqual(scan, itup))
			{
				/* tuple is qualified, so remember it */
				_hash_saveitem(so, itemIndex, offnum, itup);
				itemIndex++;
			}
			else
			{
				/*
				 * No more matching tuples exist in this page. so, exit while
				 * loop.
				 */
				break;
			}

			offnum = OffsetNumberNext(offnum);
		}

		Assert(itemIndex <= MaxIndexTuplesPerPage);
		return itemIndex;
	}
	else
	{
		/* load items[] in descending order */
		itemIndex = MaxIndexTuplesPerPage;

		while (offnum >= FirstOffsetNumber)
		{
			Assert(offnum <= maxoff);
			itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, offnum));

			/*
			 * skip the tuples that are moved by split operation for the scan
			 * that has started when split was in progress. Also, skip the
			 * tuples that are marked as dead.
			 */
			if ((so->hashso_buc_populated && !so->hashso_buc_split &&
				 (itup->t_info & INDEX_MOVED_BY_SPLIT_MASK)) ||
				(scan->ignore_killed_tuples &&
				 (ItemIdIsDead(PageGetItemId(page, offnum)))))
			{
				offnum = OffsetNumberPrev(offnum);	/* move back */
				continue;
			}

			if (so->hashso_sk_hash == _hash_get_indextuple_hashkey(itup) &&
				_hash_checkqual(scan, itup))
			{
				itemIndex--;
				/* tuple is qualified, so remember it */
				_hash_saveitem(so, itemIndex, offnum, itup);
			}
			else
			{
				/*
				 * No more matching tuples exist in this page. so, exit while
				 * loop.
				 */
				break;
			}

			offnum = OffsetNumberPrev(offnum);
		}

		Assert(itemIndex >= 0);
		return itemIndex;
	}
}
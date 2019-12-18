#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ itemIndex; scalar_t__ lastItem; scalar_t__ firstItem; TYPE_2__* items; int /*<<< orphan*/  prevPage; int /*<<< orphan*/  nextPage; } ;
struct TYPE_11__ {scalar_t__ numKilled; scalar_t__ hashso_bucket_buf; scalar_t__ hashso_split_bucket_buf; TYPE_8__ currPos; } ;
struct TYPE_10__ {int /*<<< orphan*/  heapTid; } ;
struct TYPE_9__ {int /*<<< orphan*/  xs_heaptid; int /*<<< orphan*/  xs_snapshot; int /*<<< orphan*/  opaque; int /*<<< orphan*/  indexRelation; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__ HashScanPosItem ;
typedef  TYPE_3__* HashScanOpaque ;
typedef  scalar_t__ Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 scalar_t__ BlockNumberIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  HASH_READ ; 
 int /*<<< orphan*/  HashScanPosInvalidate (TYPE_8__) ; 
 int LH_BUCKET_PAGE ; 
 int LH_OVERFLOW_PAGE ; 
 scalar_t__ ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_dropbuf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _hash_dropscanbuf (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ _hash_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _hash_kill_items (TYPE_1__*) ; 
 int /*<<< orphan*/  _hash_readpage (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ) ; 

bool
_hash_next(IndexScanDesc scan, ScanDirection dir)
{
	Relation	rel = scan->indexRelation;
	HashScanOpaque so = (HashScanOpaque) scan->opaque;
	HashScanPosItem *currItem;
	BlockNumber blkno;
	Buffer		buf;
	bool		end_of_scan = false;

	/*
	 * Advance to the next tuple on the current page; or if done, try to read
	 * data from the next or previous page based on the scan direction. Before
	 * moving to the next or previous page make sure that we deal with all the
	 * killed items.
	 */
	if (ScanDirectionIsForward(dir))
	{
		if (++so->currPos.itemIndex > so->currPos.lastItem)
		{
			if (so->numKilled > 0)
				_hash_kill_items(scan);

			blkno = so->currPos.nextPage;
			if (BlockNumberIsValid(blkno))
			{
				buf = _hash_getbuf(rel, blkno, HASH_READ, LH_OVERFLOW_PAGE);
				TestForOldSnapshot(scan->xs_snapshot, rel, BufferGetPage(buf));
				if (!_hash_readpage(scan, &buf, dir))
					end_of_scan = true;
			}
			else
				end_of_scan = true;
		}
	}
	else
	{
		if (--so->currPos.itemIndex < so->currPos.firstItem)
		{
			if (so->numKilled > 0)
				_hash_kill_items(scan);

			blkno = so->currPos.prevPage;
			if (BlockNumberIsValid(blkno))
			{
				buf = _hash_getbuf(rel, blkno, HASH_READ,
								   LH_BUCKET_PAGE | LH_OVERFLOW_PAGE);
				TestForOldSnapshot(scan->xs_snapshot, rel, BufferGetPage(buf));

				/*
				 * We always maintain the pin on bucket page for whole scan
				 * operation, so releasing the additional pin we have acquired
				 * here.
				 */
				if (buf == so->hashso_bucket_buf ||
					buf == so->hashso_split_bucket_buf)
					_hash_dropbuf(rel, buf);

				if (!_hash_readpage(scan, &buf, dir))
					end_of_scan = true;
			}
			else
				end_of_scan = true;
		}
	}

	if (end_of_scan)
	{
		_hash_dropscanbuf(rel, so);
		HashScanPosInvalidate(so->currPos);
		return false;
	}

	/* OK, itemIndex says what to return */
	currItem = &so->currPos.items[so->currPos.itemIndex];
	scan->xs_heaptid = currItem->heapTid;

	return true;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hasho_nextblkno; } ;
struct TYPE_7__ {scalar_t__ hashso_bucket_buf; scalar_t__ hashso_split_bucket_buf; int hashso_buc_split; scalar_t__ hashso_buc_populated; } ;
struct TYPE_6__ {int /*<<< orphan*/  xs_snapshot; int /*<<< orphan*/  opaque; int /*<<< orphan*/  indexRelation; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__* HashScanOpaque ;
typedef  TYPE_3__* HashPageOpaque ;
typedef  scalar_t__ Buffer ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BlockNumberIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetBlockNumber (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  BufferIsValid (scalar_t__) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  HASH_READ ; 
 scalar_t__ InvalidBuffer ; 
 int /*<<< orphan*/  LH_OVERFLOW_PAGE ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetSpecialPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _hash_getbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hash_relbuf (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
_hash_readnext(IndexScanDesc scan,
			   Buffer *bufp, Page *pagep, HashPageOpaque *opaquep)
{
	BlockNumber blkno;
	Relation	rel = scan->indexRelation;
	HashScanOpaque so = (HashScanOpaque) scan->opaque;
	bool		block_found = false;

	blkno = (*opaquep)->hasho_nextblkno;

	/*
	 * Retain the pin on primary bucket page till the end of scan.  Refer the
	 * comments in _hash_first to know the reason of retaining pin.
	 */
	if (*bufp == so->hashso_bucket_buf || *bufp == so->hashso_split_bucket_buf)
		LockBuffer(*bufp, BUFFER_LOCK_UNLOCK);
	else
		_hash_relbuf(rel, *bufp);

	*bufp = InvalidBuffer;
	/* check for interrupts while we're not holding any buffer lock */
	CHECK_FOR_INTERRUPTS();
	if (BlockNumberIsValid(blkno))
	{
		*bufp = _hash_getbuf(rel, blkno, HASH_READ, LH_OVERFLOW_PAGE);
		block_found = true;
	}
	else if (so->hashso_buc_populated && !so->hashso_buc_split)
	{
		/*
		 * end of bucket, scan bucket being split if there was a split in
		 * progress at the start of scan.
		 */
		*bufp = so->hashso_split_bucket_buf;

		/*
		 * buffer for bucket being split must be valid as we acquire the pin
		 * on it before the start of scan and retain it till end of scan.
		 */
		Assert(BufferIsValid(*bufp));

		LockBuffer(*bufp, BUFFER_LOCK_SHARE);
		PredicateLockPage(rel, BufferGetBlockNumber(*bufp), scan->xs_snapshot);

		/*
		 * setting hashso_buc_split to true indicates that we are scanning
		 * bucket being split.
		 */
		so->hashso_buc_split = true;

		block_found = true;
	}

	if (block_found)
	{
		*pagep = BufferGetPage(*bufp);
		TestForOldSnapshot(scan->xs_snapshot, rel, *pagep);
		*opaquep = (HashPageOpaque) PageGetSpecialPointer(*pagep);
	}
}
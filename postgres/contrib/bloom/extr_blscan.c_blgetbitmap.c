#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_10__ {int bloomLength; } ;
struct TYPE_15__ {TYPE_1__ opts; } ;
struct TYPE_14__ {int* sign; TYPE_6__ state; } ;
struct TYPE_13__ {int* sign; int /*<<< orphan*/  heapPtr; } ;
struct TYPE_12__ {int numberOfKeys; int /*<<< orphan*/  indexRelation; int /*<<< orphan*/  xs_snapshot; TYPE_2__* keyData; int /*<<< orphan*/  opaque; } ;
struct TYPE_11__ {int sk_flags; scalar_t__ sk_attno; int /*<<< orphan*/  sk_argument; } ;
typedef  int /*<<< orphan*/  TIDBitmap ;
typedef  TYPE_2__* ScanKey ;
typedef  int /*<<< orphan*/  Page ;
typedef  int OffsetNumber ;
typedef  TYPE_3__* IndexScanDesc ;
typedef  int /*<<< orphan*/  BufferAccessStrategy ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_4__ BloomTuple ;
typedef  int /*<<< orphan*/  BloomSignatureWord ;
typedef  TYPE_5__* BloomScanOpaque ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BAS_BULKREAD ; 
 scalar_t__ BLOOM_HEAD_BLKNO ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int BloomPageGetMaxOffset (int /*<<< orphan*/ ) ; 
 TYPE_4__* BloomPageGetTuple (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BloomPageIsDeleted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  FreeAccessStrategy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetAccessStrategy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int SK_ISNULL ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int* palloc0 (int) ; 
 int /*<<< orphan*/  pfree (int*) ; 
 int /*<<< orphan*/  signValue (TYPE_6__*,int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tbm_add_tuples (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

int64
blgetbitmap(IndexScanDesc scan, TIDBitmap *tbm)
{
	int64		ntids = 0;
	BlockNumber blkno = BLOOM_HEAD_BLKNO,
				npages;
	int			i;
	BufferAccessStrategy bas;
	BloomScanOpaque so = (BloomScanOpaque) scan->opaque;

	if (so->sign == NULL)
	{
		/* New search: have to calculate search signature */
		ScanKey		skey = scan->keyData;

		so->sign = palloc0(sizeof(BloomSignatureWord) * so->state.opts.bloomLength);

		for (i = 0; i < scan->numberOfKeys; i++)
		{
			/*
			 * Assume bloom-indexable operators to be strict, so nothing could
			 * be found for NULL key.
			 */
			if (skey->sk_flags & SK_ISNULL)
			{
				pfree(so->sign);
				so->sign = NULL;
				return 0;
			}

			/* Add next value to the signature */
			signValue(&so->state, so->sign, skey->sk_argument,
					  skey->sk_attno - 1);

			skey++;
		}
	}

	/*
	 * We're going to read the whole index. This is why we use appropriate
	 * buffer access strategy.
	 */
	bas = GetAccessStrategy(BAS_BULKREAD);
	npages = RelationGetNumberOfBlocks(scan->indexRelation);

	for (blkno = BLOOM_HEAD_BLKNO; blkno < npages; blkno++)
	{
		Buffer		buffer;
		Page		page;

		buffer = ReadBufferExtended(scan->indexRelation, MAIN_FORKNUM,
									blkno, RBM_NORMAL, bas);

		LockBuffer(buffer, BUFFER_LOCK_SHARE);
		page = BufferGetPage(buffer);
		TestForOldSnapshot(scan->xs_snapshot, scan->indexRelation, page);

		if (!PageIsNew(page) && !BloomPageIsDeleted(page))
		{
			OffsetNumber offset,
						maxOffset = BloomPageGetMaxOffset(page);

			for (offset = 1; offset <= maxOffset; offset++)
			{
				BloomTuple *itup = BloomPageGetTuple(&so->state, page, offset);
				bool		res = true;

				/* Check index signature with scan signature */
				for (i = 0; i < so->state.opts.bloomLength; i++)
				{
					if ((itup->sign[i] & so->sign[i]) != so->sign[i])
					{
						res = false;
						break;
					}
				}

				/* Add matching tuples to bitmap */
				if (res)
				{
					tbm_add_tuples(tbm, &itup->heapPtr, 1, true);
					ntids++;
				}
			}
		}

		UnlockReleaseBuffer(buffer);
		CHECK_FOR_INTERRUPTS();
	}
	FreeAccessStrategy(bas);

	return ntids;
}
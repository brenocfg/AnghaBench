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
struct TYPE_7__ {int /*<<< orphan*/  t_cid; } ;
struct TYPE_8__ {TYPE_1__ t_field3; } ;
struct TYPE_9__ {TYPE_2__ t_heap; } ;
struct TYPE_10__ {int /*<<< orphan*/  t_ctid; TYPE_3__ t_choice; int /*<<< orphan*/  t_infomask; } ;
typedef  scalar_t__ Page ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_4__* HeapTupleHeader ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  HEAP_XACT_MASK ; 
 int /*<<< orphan*/  HEAP_XMAX_COMMITTED ; 
 int /*<<< orphan*/  HEAP_XMAX_INVALID ; 
 scalar_t__ HeapTupleHeaderIsSpeculative (TYPE_4__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderXminFrozen (TYPE_4__*) ; 
 int ItemIdGetLength (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdGetOffset (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdHasStorage (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MASK_MARKER ; 
 int MAXALIGN (int) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,int) ; 
 int PageGetMaxOffsetNumber (scalar_t__) ; 
 int /*<<< orphan*/  mask_page_hint_bits (scalar_t__) ; 
 int /*<<< orphan*/  mask_page_lsn_and_checksum (scalar_t__) ; 
 int /*<<< orphan*/  mask_unused_space (scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void
heap_mask(char *pagedata, BlockNumber blkno)
{
	Page		page = (Page) pagedata;
	OffsetNumber off;

	mask_page_lsn_and_checksum(page);

	mask_page_hint_bits(page);
	mask_unused_space(page);

	for (off = 1; off <= PageGetMaxOffsetNumber(page); off++)
	{
		ItemId		iid = PageGetItemId(page, off);
		char	   *page_item;

		page_item = (char *) (page + ItemIdGetOffset(iid));

		if (ItemIdIsNormal(iid))
		{
			HeapTupleHeader page_htup = (HeapTupleHeader) page_item;

			/*
			 * If xmin of a tuple is not yet frozen, we should ignore
			 * differences in hint bits, since they can be set without
			 * emitting WAL.
			 */
			if (!HeapTupleHeaderXminFrozen(page_htup))
				page_htup->t_infomask &= ~HEAP_XACT_MASK;
			else
			{
				/* Still we need to mask xmax hint bits. */
				page_htup->t_infomask &= ~HEAP_XMAX_INVALID;
				page_htup->t_infomask &= ~HEAP_XMAX_COMMITTED;
			}

			/*
			 * During replay, we set Command Id to FirstCommandId. Hence, mask
			 * it. See heap_xlog_insert() for details.
			 */
			page_htup->t_choice.t_heap.t_field3.t_cid = MASK_MARKER;

			/*
			 * For a speculative tuple, heap_insert() does not set ctid in the
			 * caller-passed heap tuple itself, leaving the ctid field to
			 * contain a speculative token value - a per-backend monotonically
			 * increasing identifier. Besides, it does not WAL-log ctid under
			 * any circumstances.
			 *
			 * During redo, heap_xlog_insert() sets t_ctid to current block
			 * number and self offset number. It doesn't care about any
			 * speculative insertions in master. Hence, we set t_ctid to
			 * current block number and self offset number to ignore any
			 * inconsistency.
			 */
			if (HeapTupleHeaderIsSpeculative(page_htup))
				ItemPointerSet(&page_htup->t_ctid, blkno, off);

			/*
			 * NB: Not ignoring ctid changes due to the tuple having moved
			 * (i.e. HeapTupleHeaderIndicatesMovedPartitions), because that's
			 * important information that needs to be in-sync between primary
			 * and standby, and thus is WAL logged.
			 */
		}

		/*
		 * Ignore any padding bytes after the tuple, when the length of the
		 * item is not MAXALIGNed.
		 */
		if (ItemIdHasStorage(iid))
		{
			int			len = ItemIdGetLength(iid);
			int			padlen = MAXALIGN(len) - len;

			if (padlen > 0)
				memset(page_item + len, MASK_MARKER, padlen);
		}
	}
}
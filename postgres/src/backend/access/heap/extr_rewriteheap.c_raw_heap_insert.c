#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  rd_smgr; int /*<<< orphan*/  rd_node; TYPE_1__* rd_rel; } ;
struct TYPE_19__ {scalar_t__ t_len; int /*<<< orphan*/  t_self; TYPE_2__* t_data; } ;
struct TYPE_18__ {int /*<<< orphan*/  t_ctid; } ;
struct TYPE_17__ {int rs_buffer_valid; int /*<<< orphan*/  rs_blockno; TYPE_9__* rs_new_rel; scalar_t__ rs_use_wal; scalar_t__ rs_buffer; } ;
struct TYPE_16__ {int /*<<< orphan*/  t_ctid; } ;
struct TYPE_15__ {scalar_t__ relkind; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_3__* RewriteState ;
typedef  scalar_t__ Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  Item ;
typedef  TYPE_4__* HeapTupleHeader ;
typedef  TYPE_5__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BLCKSZ ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HEAP_DEFAULT_FILLFACTOR ; 
 int HEAP_INSERT_NO_LOGICAL ; 
 int HEAP_INSERT_SKIP_FSM ; 
 int HEAP_INSERT_SKIP_WAL ; 
 scalar_t__ HeapTupleHasExternal (TYPE_5__*) ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ MAXALIGN (scalar_t__) ; 
 scalar_t__ MaxHeapTupleSize ; 
 scalar_t__ PageAddItem (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ PageGetHeapFreeSpace (scalar_t__) ; 
 scalar_t__ PageGetItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PageInit (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetChecksumInplace (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_TOASTVALUE ; 
 scalar_t__ RelationGetTargetPageFreeSpace (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationOpenSmgr (TYPE_9__*) ; 
 scalar_t__ TOAST_TUPLE_THRESHOLD ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_5__*) ; 
 TYPE_5__* heap_toast_insert_or_update (TYPE_9__*,TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_newpage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  smgrextend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
raw_heap_insert(RewriteState state, HeapTuple tup)
{
	Page		page = state->rs_buffer;
	Size		pageFreeSpace,
				saveFreeSpace;
	Size		len;
	OffsetNumber newoff;
	HeapTuple	heaptup;

	/*
	 * If the new tuple is too big for storage or contains already toasted
	 * out-of-line attributes from some other relation, invoke the toaster.
	 *
	 * Note: below this point, heaptup is the data we actually intend to store
	 * into the relation; tup is the caller's original untoasted data.
	 */
	if (state->rs_new_rel->rd_rel->relkind == RELKIND_TOASTVALUE)
	{
		/* toast table entries should never be recursively toasted */
		Assert(!HeapTupleHasExternal(tup));
		heaptup = tup;
	}
	else if (HeapTupleHasExternal(tup) || tup->t_len > TOAST_TUPLE_THRESHOLD)
	{
		int			options = HEAP_INSERT_SKIP_FSM;

		if (!state->rs_use_wal)
			options |= HEAP_INSERT_SKIP_WAL;

		/*
		 * While rewriting the heap for VACUUM FULL / CLUSTER, make sure data
		 * for the TOAST table are not logically decoded.  The main heap is
		 * WAL-logged as XLOG FPI records, which are not logically decoded.
		 */
		options |= HEAP_INSERT_NO_LOGICAL;

		heaptup = heap_toast_insert_or_update(state->rs_new_rel, tup, NULL,
											  options);
	}
	else
		heaptup = tup;

	len = MAXALIGN(heaptup->t_len); /* be conservative */

	/*
	 * If we're gonna fail for oversize tuple, do it right away
	 */
	if (len > MaxHeapTupleSize)
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("row is too big: size %zu, maximum size %zu",
						len, MaxHeapTupleSize)));

	/* Compute desired extra freespace due to fillfactor option */
	saveFreeSpace = RelationGetTargetPageFreeSpace(state->rs_new_rel,
												   HEAP_DEFAULT_FILLFACTOR);

	/* Now we can check to see if there's enough free space already. */
	if (state->rs_buffer_valid)
	{
		pageFreeSpace = PageGetHeapFreeSpace(page);

		if (len + saveFreeSpace > pageFreeSpace)
		{
			/* Doesn't fit, so write out the existing page */

			/* XLOG stuff */
			if (state->rs_use_wal)
				log_newpage(&state->rs_new_rel->rd_node,
							MAIN_FORKNUM,
							state->rs_blockno,
							page,
							true);

			/*
			 * Now write the page. We say skipFsync = true because there's no
			 * need for smgr to schedule an fsync for this write; we'll do it
			 * ourselves in end_heap_rewrite.
			 */
			RelationOpenSmgr(state->rs_new_rel);

			PageSetChecksumInplace(page, state->rs_blockno);

			smgrextend(state->rs_new_rel->rd_smgr, MAIN_FORKNUM,
					   state->rs_blockno, (char *) page, true);

			state->rs_blockno++;
			state->rs_buffer_valid = false;
		}
	}

	if (!state->rs_buffer_valid)
	{
		/* Initialize a new empty page */
		PageInit(page, BLCKSZ, 0);
		state->rs_buffer_valid = true;
	}

	/* And now we can insert the tuple into the page */
	newoff = PageAddItem(page, (Item) heaptup->t_data, heaptup->t_len,
						 InvalidOffsetNumber, false, true);
	if (newoff == InvalidOffsetNumber)
		elog(ERROR, "failed to add tuple");

	/* Update caller's t_self to the actual position where it was stored */
	ItemPointerSet(&(tup->t_self), state->rs_blockno, newoff);

	/*
	 * Insert the correct position into CTID of the stored tuple, too, if the
	 * caller didn't supply a valid CTID.
	 */
	if (!ItemPointerIsValid(&tup->t_data->t_ctid))
	{
		ItemId		newitemid;
		HeapTupleHeader onpage_tup;

		newitemid = PageGetItemId(page, newoff);
		onpage_tup = (HeapTupleHeader) PageGetItem(page, newitemid);

		onpage_tup->t_ctid = tup->t_self;
	}

	/* If heaptup is a private copy, release it. */
	if (heaptup != tup)
		heap_freetuple(heaptup);
}
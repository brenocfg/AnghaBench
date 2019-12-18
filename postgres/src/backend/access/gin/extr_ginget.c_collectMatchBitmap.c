#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_20__ {int /*<<< orphan*/ * supportCollation; int /*<<< orphan*/ * comparePartialFn; int /*<<< orphan*/  origTupdesc; } ;
struct TYPE_19__ {int /*<<< orphan*/  attbyval; int /*<<< orphan*/  attlen; } ;
struct TYPE_18__ {TYPE_8__* ginstate; int /*<<< orphan*/  index; } ;
struct TYPE_17__ {int /*<<< orphan*/  off; int /*<<< orphan*/  buffer; } ;
struct TYPE_16__ {scalar_t__ queryCategory; int attnum; scalar_t__ searchMode; int /*<<< orphan*/  predictNumberResult; int /*<<< orphan*/  matchBitmap; int /*<<< orphan*/  extra_data; int /*<<< orphan*/  strategy; int /*<<< orphan*/  queryKey; scalar_t__ isPartialMatch; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Page ;
typedef  int OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_1__* GinScanEntry ;
typedef  scalar_t__ GinNullCategory ;
typedef  TYPE_2__ GinBtreeStack ;
typedef  TYPE_3__ GinBtreeData ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCall4Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GIN_CAT_NORM_KEY ; 
 scalar_t__ GIN_CAT_NULL_ITEM ; 
 scalar_t__ GIN_SEARCH_MODE_ALL ; 
 int /*<<< orphan*/  GIN_SHARE ; 
 int /*<<< orphan*/  GIN_UNLOCK ; 
 scalar_t__ GinGetNPosting (scalar_t__) ; 
 int /*<<< orphan*/  GinGetPostingTree (scalar_t__) ; 
 scalar_t__ GinIsPostingTree (scalar_t__) ; 
 int /*<<< orphan*/  GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UInt16GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ginCompareEntries (TYPE_8__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ginReadTuple (TYPE_8__*,int,scalar_t__,int*) ; 
 int gintuple_get_attrnum (TYPE_8__*,scalar_t__) ; 
 int /*<<< orphan*/  gintuple_get_key (TYPE_8__*,scalar_t__,scalar_t__*) ; 
 int moveRightIfItNeeded (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scanPostingTree (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbm_add_tuples (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tbm_create (long,int /*<<< orphan*/ *) ; 
 long work_mem ; 

__attribute__((used)) static bool
collectMatchBitmap(GinBtreeData *btree, GinBtreeStack *stack,
				   GinScanEntry scanEntry, Snapshot snapshot)
{
	OffsetNumber attnum;
	Form_pg_attribute attr;

	/* Initialize empty bitmap result */
	scanEntry->matchBitmap = tbm_create(work_mem * 1024L, NULL);

	/* Null query cannot partial-match anything */
	if (scanEntry->isPartialMatch &&
		scanEntry->queryCategory != GIN_CAT_NORM_KEY)
		return true;

	/* Locate tupdesc entry for key column (for attbyval/attlen data) */
	attnum = scanEntry->attnum;
	attr = TupleDescAttr(btree->ginstate->origTupdesc, attnum - 1);

	/*
	 * Predicate lock entry leaf page, following pages will be locked by
	 * moveRightIfItNeeded()
	 */
	PredicateLockPage(btree->index, stack->buffer, snapshot);

	for (;;)
	{
		Page		page;
		IndexTuple	itup;
		Datum		idatum;
		GinNullCategory icategory;

		/*
		 * stack->off points to the interested entry, buffer is already locked
		 */
		if (moveRightIfItNeeded(btree, stack, snapshot) == false)
			return true;

		page = BufferGetPage(stack->buffer);
		TestForOldSnapshot(snapshot, btree->index, page);
		itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, stack->off));

		/*
		 * If tuple stores another attribute then stop scan
		 */
		if (gintuple_get_attrnum(btree->ginstate, itup) != attnum)
			return true;

		/* Safe to fetch attribute value */
		idatum = gintuple_get_key(btree->ginstate, itup, &icategory);

		/*
		 * Check for appropriate scan stop conditions
		 */
		if (scanEntry->isPartialMatch)
		{
			int32		cmp;

			/*
			 * In partial match, stop scan at any null (including
			 * placeholders); partial matches never match nulls
			 */
			if (icategory != GIN_CAT_NORM_KEY)
				return true;

			/*----------
			 * Check of partial match.
			 * case cmp == 0 => match
			 * case cmp > 0 => not match and finish scan
			 * case cmp < 0 => not match and continue scan
			 *----------
			 */
			cmp = DatumGetInt32(FunctionCall4Coll(&btree->ginstate->comparePartialFn[attnum - 1],
												  btree->ginstate->supportCollation[attnum - 1],
												  scanEntry->queryKey,
												  idatum,
												  UInt16GetDatum(scanEntry->strategy),
												  PointerGetDatum(scanEntry->extra_data)));

			if (cmp > 0)
				return true;
			else if (cmp < 0)
			{
				stack->off++;
				continue;
			}
		}
		else if (scanEntry->searchMode == GIN_SEARCH_MODE_ALL)
		{
			/*
			 * In ALL mode, we are not interested in null items, so we can
			 * stop if we get to a null-item placeholder (which will be the
			 * last entry for a given attnum).  We do want to include NULL_KEY
			 * and EMPTY_ITEM entries, though.
			 */
			if (icategory == GIN_CAT_NULL_ITEM)
				return true;
		}

		/*
		 * OK, we want to return the TIDs listed in this entry.
		 */
		if (GinIsPostingTree(itup))
		{
			BlockNumber rootPostingTree = GinGetPostingTree(itup);

			/*
			 * We should unlock current page (but not unpin) during tree scan
			 * to prevent deadlock with vacuum processes.
			 *
			 * We save current entry value (idatum) to be able to re-find our
			 * tuple after re-locking
			 */
			if (icategory == GIN_CAT_NORM_KEY)
				idatum = datumCopy(idatum, attr->attbyval, attr->attlen);

			LockBuffer(stack->buffer, GIN_UNLOCK);

			/*
			 * Acquire predicate lock on the posting tree.  We already hold a
			 * lock on the entry page, but insertions to the posting tree
			 * don't check for conflicts on that level.
			 */
			PredicateLockPage(btree->index, rootPostingTree, snapshot);

			/* Collect all the TIDs in this entry's posting tree */
			scanPostingTree(btree->index, scanEntry, rootPostingTree,
							snapshot);

			/*
			 * We lock again the entry page and while it was unlocked insert
			 * might have occurred, so we need to re-find our position.
			 */
			LockBuffer(stack->buffer, GIN_SHARE);
			page = BufferGetPage(stack->buffer);
			if (!GinPageIsLeaf(page))
			{
				/*
				 * Root page becomes non-leaf while we unlock it. We will
				 * start again, this situation doesn't occur often - root can
				 * became a non-leaf only once per life of index.
				 */
				return false;
			}

			/* Search forward to re-find idatum */
			for (;;)
			{
				Datum		newDatum;
				GinNullCategory newCategory;

				if (moveRightIfItNeeded(btree, stack, snapshot) == false)
					elog(ERROR, "lost saved point in index");	/* must not happen !!! */

				page = BufferGetPage(stack->buffer);
				itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, stack->off));

				if (gintuple_get_attrnum(btree->ginstate, itup) != attnum)
					elog(ERROR, "lost saved point in index");	/* must not happen !!! */
				newDatum = gintuple_get_key(btree->ginstate, itup,
											&newCategory);

				if (ginCompareEntries(btree->ginstate, attnum,
									  newDatum, newCategory,
									  idatum, icategory) == 0)
					break;		/* Found! */

				stack->off++;
			}

			if (icategory == GIN_CAT_NORM_KEY && !attr->attbyval)
				pfree(DatumGetPointer(idatum));
		}
		else
		{
			ItemPointer ipd;
			int			nipd;

			ipd = ginReadTuple(btree->ginstate, scanEntry->attnum, itup, &nipd);
			tbm_add_tuples(scanEntry->matchBitmap, ipd, nipd, false);
			scanEntry->predictNumberResult += GinGetNPosting(itup);
			pfree(ipd);
		}

		/*
		 * Done with this entry, go to the next
		 */
		stack->off++;
	}
}
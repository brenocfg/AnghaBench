#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_19__ ;
typedef  struct TYPE_22__   TYPE_18__ ;

/* Type definitions */
typedef  int int64 ;
struct TYPE_28__ {TYPE_1__* bt_columns; scalar_t__ bt_placeholder; } ;
struct TYPE_27__ {scalar_t__ bo_pagesPerRange; int /*<<< orphan*/  bo_rmAccess; TYPE_1__* bo_bdesc; } ;
struct TYPE_26__ {scalar_t__ fn_oid; } ;
struct TYPE_25__ {int numberOfKeys; TYPE_1__* keyData; int /*<<< orphan*/  xs_snapshot; scalar_t__ opaque; int /*<<< orphan*/  indexRelation; } ;
struct TYPE_24__ {int sk_attno; int sk_flags; scalar_t__ sk_collation; TYPE_19__* bd_tupdesc; } ;
struct TYPE_23__ {int natts; } ;
struct TYPE_22__ {scalar_t__ attcollation; } ;
typedef  int /*<<< orphan*/  TIDBitmap ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_1__* ScanKey ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  TYPE_3__ FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ Buffer ;
typedef  TYPE_1__ BrinValues ;
typedef  int /*<<< orphan*/  BrinTuple ;
typedef  TYPE_5__ BrinOpaque ;
typedef  TYPE_6__ BrinMemTuple ;
typedef  TYPE_1__ BrinDesc ;
typedef  scalar_t__ BlockNumber ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BRIN_PROCNUM_CONSISTENT ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall3Coll (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexGetRelation (int /*<<< orphan*/ ,int) ; 
 scalar_t__ InvalidBuffer ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_1__*) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (scalar_t__) ; 
 int SK_ISNULL ; 
 TYPE_18__* TupleDescAttr (TYPE_19__*,int) ; 
 int /*<<< orphan*/ * brinGetTupleForHeapBlock (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * brin_copy_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__* brin_deform_tuple (TYPE_1__*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 TYPE_6__* brin_new_memtuple (TYPE_1__*) ; 
 int /*<<< orphan*/  fmgr_info_copy (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* index_getprocinfo (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* palloc0 (int) ; 
 int /*<<< orphan*/  pgstat_count_index_scan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbm_add_page (int /*<<< orphan*/ *,scalar_t__) ; 

int64
bringetbitmap(IndexScanDesc scan, TIDBitmap *tbm)
{
	Relation	idxRel = scan->indexRelation;
	Buffer		buf = InvalidBuffer;
	BrinDesc   *bdesc;
	Oid			heapOid;
	Relation	heapRel;
	BrinOpaque *opaque;
	BlockNumber nblocks;
	BlockNumber heapBlk;
	int			totalpages = 0;
	FmgrInfo   *consistentFn;
	MemoryContext oldcxt;
	MemoryContext perRangeCxt;
	BrinMemTuple *dtup;
	BrinTuple  *btup = NULL;
	Size		btupsz = 0;

	opaque = (BrinOpaque *) scan->opaque;
	bdesc = opaque->bo_bdesc;
	pgstat_count_index_scan(idxRel);

	/*
	 * We need to know the size of the table so that we know how long to
	 * iterate on the revmap.
	 */
	heapOid = IndexGetRelation(RelationGetRelid(idxRel), false);
	heapRel = table_open(heapOid, AccessShareLock);
	nblocks = RelationGetNumberOfBlocks(heapRel);
	table_close(heapRel, AccessShareLock);

	/*
	 * Make room for the consistent support procedures of indexed columns.  We
	 * don't look them up here; we do that lazily the first time we see a scan
	 * key reference each of them.  We rely on zeroing fn_oid to InvalidOid.
	 */
	consistentFn = palloc0(sizeof(FmgrInfo) * bdesc->bd_tupdesc->natts);

	/* allocate an initial in-memory tuple, out of the per-range memcxt */
	dtup = brin_new_memtuple(bdesc);

	/*
	 * Setup and use a per-range memory context, which is reset every time we
	 * loop below.  This avoids having to free the tuples within the loop.
	 */
	perRangeCxt = AllocSetContextCreate(CurrentMemoryContext,
										"bringetbitmap cxt",
										ALLOCSET_DEFAULT_SIZES);
	oldcxt = MemoryContextSwitchTo(perRangeCxt);

	/*
	 * Now scan the revmap.  We start by querying for heap page 0,
	 * incrementing by the number of pages per range; this gives us a full
	 * view of the table.
	 */
	for (heapBlk = 0; heapBlk < nblocks; heapBlk += opaque->bo_pagesPerRange)
	{
		bool		addrange;
		bool		gottuple = false;
		BrinTuple  *tup;
		OffsetNumber off;
		Size		size;

		CHECK_FOR_INTERRUPTS();

		MemoryContextResetAndDeleteChildren(perRangeCxt);

		tup = brinGetTupleForHeapBlock(opaque->bo_rmAccess, heapBlk, &buf,
									   &off, &size, BUFFER_LOCK_SHARE,
									   scan->xs_snapshot);
		if (tup)
		{
			gottuple = true;
			btup = brin_copy_tuple(tup, size, btup, &btupsz);
			LockBuffer(buf, BUFFER_LOCK_UNLOCK);
		}

		/*
		 * For page ranges with no indexed tuple, we must return the whole
		 * range; otherwise, compare it to the scan keys.
		 */
		if (!gottuple)
		{
			addrange = true;
		}
		else
		{
			dtup = brin_deform_tuple(bdesc, btup, dtup);
			if (dtup->bt_placeholder)
			{
				/*
				 * Placeholder tuples are always returned, regardless of the
				 * values stored in them.
				 */
				addrange = true;
			}
			else
			{
				int			keyno;

				/*
				 * Compare scan keys with summary values stored for the range.
				 * If scan keys are matched, the page range must be added to
				 * the bitmap.  We initially assume the range needs to be
				 * added; in particular this serves the case where there are
				 * no keys.
				 */
				addrange = true;
				for (keyno = 0; keyno < scan->numberOfKeys; keyno++)
				{
					ScanKey		key = &scan->keyData[keyno];
					AttrNumber	keyattno = key->sk_attno;
					BrinValues *bval = &dtup->bt_columns[keyattno - 1];
					Datum		add;

					/*
					 * The collation of the scan key must match the collation
					 * used in the index column (but only if the search is not
					 * IS NULL/ IS NOT NULL).  Otherwise we shouldn't be using
					 * this index ...
					 */
					Assert((key->sk_flags & SK_ISNULL) ||
						   (key->sk_collation ==
							TupleDescAttr(bdesc->bd_tupdesc,
										  keyattno - 1)->attcollation));

					/* First time this column? look up consistent function */
					if (consistentFn[keyattno - 1].fn_oid == InvalidOid)
					{
						FmgrInfo   *tmp;

						tmp = index_getprocinfo(idxRel, keyattno,
												BRIN_PROCNUM_CONSISTENT);
						fmgr_info_copy(&consistentFn[keyattno - 1], tmp,
									   CurrentMemoryContext);
					}

					/*
					 * Check whether the scan key is consistent with the page
					 * range values; if so, have the pages in the range added
					 * to the output bitmap.
					 *
					 * When there are multiple scan keys, failure to meet the
					 * criteria for a single one of them is enough to discard
					 * the range as a whole, so break out of the loop as soon
					 * as a false return value is obtained.
					 */
					add = FunctionCall3Coll(&consistentFn[keyattno - 1],
											key->sk_collation,
											PointerGetDatum(bdesc),
											PointerGetDatum(bval),
											PointerGetDatum(key));
					addrange = DatumGetBool(add);
					if (!addrange)
						break;
				}
			}
		}

		/* add the pages in the range to the output bitmap, if needed */
		if (addrange)
		{
			BlockNumber pageno;

			for (pageno = heapBlk;
				 pageno <= heapBlk + opaque->bo_pagesPerRange - 1;
				 pageno++)
			{
				MemoryContextSwitchTo(oldcxt);
				tbm_add_page(tbm, pageno);
				totalpages++;
				MemoryContextSwitchTo(perRangeCxt);
			}
		}
	}

	MemoryContextSwitchTo(oldcxt);
	MemoryContextDelete(perRangeCxt);

	if (buf != InvalidBuffer)
		ReleaseBuffer(buf);

	/*
	 * XXX We have an approximation of the number of *pages* that our scan
	 * returns, but we don't have a precise idea of the number of heap tuples
	 * involved.
	 */
	return totalpages * 10;
}
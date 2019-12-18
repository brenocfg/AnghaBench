#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {TYPE_4__* bt_columns; } ;
struct TYPE_26__ {TYPE_1__* bd_tupdesc; } ;
struct TYPE_25__ {void* ii_AmCache; int /*<<< orphan*/ * ii_Context; } ;
struct TYPE_24__ {int /*<<< orphan*/ * rd_indcollation; } ;
struct TYPE_23__ {int natts; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  IndexUniqueCheck ;
typedef  TYPE_3__ IndexInfo ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_4__ BrinValues ;
typedef  int /*<<< orphan*/  BrinTuple ;
typedef  int /*<<< orphan*/  BrinRevmap ;
typedef  TYPE_5__ BrinMemTuple ;
typedef  TYPE_4__ BrinDesc ;
typedef  int BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AVW_BRINSummarizeRange ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int AutoVacuumRequestWork (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BRIN_PROCNUM_ADDVALUE ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int BrinGetAutoSummarize (TYPE_2__*) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/ * CurrentMemoryContext ; 
 int DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  FunctionCall4Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int ItemPointerGetBlockNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerGetOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_4__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * brinGetTupleForHeapBlock (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * brinRevmapInitialize (TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brinRevmapTerminate (int /*<<< orphan*/ *) ; 
 TYPE_4__* brin_build_desc (TYPE_2__*) ; 
 int brin_can_do_samepage_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * brin_copy_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* brin_deform_tuple (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brin_doupdate (TYPE_2__*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * brin_form_tuple (TYPE_4__*,int,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * index_getprocinfo (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

bool
brininsert(Relation idxRel, Datum *values, bool *nulls,
		   ItemPointer heaptid, Relation heapRel,
		   IndexUniqueCheck checkUnique,
		   IndexInfo *indexInfo)
{
	BlockNumber pagesPerRange;
	BlockNumber origHeapBlk;
	BlockNumber heapBlk;
	BrinDesc   *bdesc = (BrinDesc *) indexInfo->ii_AmCache;
	BrinRevmap *revmap;
	Buffer		buf = InvalidBuffer;
	MemoryContext tupcxt = NULL;
	MemoryContext oldcxt = CurrentMemoryContext;
	bool		autosummarize = BrinGetAutoSummarize(idxRel);

	revmap = brinRevmapInitialize(idxRel, &pagesPerRange, NULL);

	/*
	 * origHeapBlk is the block number where the insertion occurred.  heapBlk
	 * is the first block in the corresponding page range.
	 */
	origHeapBlk = ItemPointerGetBlockNumber(heaptid);
	heapBlk = (origHeapBlk / pagesPerRange) * pagesPerRange;

	for (;;)
	{
		bool		need_insert = false;
		OffsetNumber off;
		BrinTuple  *brtup;
		BrinMemTuple *dtup;
		int			keyno;

		CHECK_FOR_INTERRUPTS();

		/*
		 * If auto-summarization is enabled and we just inserted the first
		 * tuple into the first block of a new non-first page range, request a
		 * summarization run of the previous range.
		 */
		if (autosummarize &&
			heapBlk > 0 &&
			heapBlk == origHeapBlk &&
			ItemPointerGetOffsetNumber(heaptid) == FirstOffsetNumber)
		{
			BlockNumber lastPageRange = heapBlk - 1;
			BrinTuple  *lastPageTuple;

			lastPageTuple =
				brinGetTupleForHeapBlock(revmap, lastPageRange, &buf, &off,
										 NULL, BUFFER_LOCK_SHARE, NULL);
			if (!lastPageTuple)
			{
				bool		recorded;

				recorded = AutoVacuumRequestWork(AVW_BRINSummarizeRange,
												 RelationGetRelid(idxRel),
												 lastPageRange);
				if (!recorded)
					ereport(LOG,
							(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
							 errmsg("request for BRIN range summarization for index \"%s\" page %u was not recorded",
									RelationGetRelationName(idxRel),
									lastPageRange)));
			}
			else
				LockBuffer(buf, BUFFER_LOCK_UNLOCK);
		}

		brtup = brinGetTupleForHeapBlock(revmap, heapBlk, &buf, &off,
										 NULL, BUFFER_LOCK_SHARE, NULL);

		/* if range is unsummarized, there's nothing to do */
		if (!brtup)
			break;

		/* First time through in this statement? */
		if (bdesc == NULL)
		{
			MemoryContextSwitchTo(indexInfo->ii_Context);
			bdesc = brin_build_desc(idxRel);
			indexInfo->ii_AmCache = (void *) bdesc;
			MemoryContextSwitchTo(oldcxt);
		}
		/* First time through in this brininsert call? */
		if (tupcxt == NULL)
		{
			tupcxt = AllocSetContextCreate(CurrentMemoryContext,
										   "brininsert cxt",
										   ALLOCSET_DEFAULT_SIZES);
			MemoryContextSwitchTo(tupcxt);
		}

		dtup = brin_deform_tuple(bdesc, brtup, NULL);

		/*
		 * Compare the key values of the new tuple to the stored index values;
		 * our deformed tuple will get updated if the new tuple doesn't fit
		 * the original range (note this means we can't break out of the loop
		 * early). Make a note of whether this happens, so that we know to
		 * insert the modified tuple later.
		 */
		for (keyno = 0; keyno < bdesc->bd_tupdesc->natts; keyno++)
		{
			Datum		result;
			BrinValues *bval;
			FmgrInfo   *addValue;

			bval = &dtup->bt_columns[keyno];
			addValue = index_getprocinfo(idxRel, keyno + 1,
										 BRIN_PROCNUM_ADDVALUE);
			result = FunctionCall4Coll(addValue,
									   idxRel->rd_indcollation[keyno],
									   PointerGetDatum(bdesc),
									   PointerGetDatum(bval),
									   values[keyno],
									   nulls[keyno]);
			/* if that returned true, we need to insert the updated tuple */
			need_insert |= DatumGetBool(result);
		}

		if (!need_insert)
		{
			/*
			 * The tuple is consistent with the new values, so there's nothing
			 * to do.
			 */
			LockBuffer(buf, BUFFER_LOCK_UNLOCK);
		}
		else
		{
			Page		page = BufferGetPage(buf);
			ItemId		lp = PageGetItemId(page, off);
			Size		origsz;
			BrinTuple  *origtup;
			Size		newsz;
			BrinTuple  *newtup;
			bool		samepage;

			/*
			 * Make a copy of the old tuple, so that we can compare it after
			 * re-acquiring the lock.
			 */
			origsz = ItemIdGetLength(lp);
			origtup = brin_copy_tuple(brtup, origsz, NULL, NULL);

			/*
			 * Before releasing the lock, check if we can attempt a same-page
			 * update.  Another process could insert a tuple concurrently in
			 * the same page though, so downstream we must be prepared to cope
			 * if this turns out to not be possible after all.
			 */
			newtup = brin_form_tuple(bdesc, heapBlk, dtup, &newsz);
			samepage = brin_can_do_samepage_update(buf, origsz, newsz);
			LockBuffer(buf, BUFFER_LOCK_UNLOCK);

			/*
			 * Try to update the tuple.  If this doesn't work for whatever
			 * reason, we need to restart from the top; the revmap might be
			 * pointing at a different tuple for this block now, so we need to
			 * recompute to ensure both our new heap tuple and the other
			 * inserter's are covered by the combined tuple.  It might be that
			 * we don't need to update at all.
			 */
			if (!brin_doupdate(idxRel, pagesPerRange, revmap, heapBlk,
							   buf, off, origtup, origsz, newtup, newsz,
							   samepage))
			{
				/* no luck; start over */
				MemoryContextResetAndDeleteChildren(tupcxt);
				continue;
			}
		}

		/* success! */
		break;
	}

	brinRevmapTerminate(revmap);
	if (BufferIsValid(buf))
		ReleaseBuffer(buf);
	MemoryContextSwitchTo(oldcxt);
	if (tupcxt != NULL)
		MemoryContextDelete(tupcxt);

	return false;
}
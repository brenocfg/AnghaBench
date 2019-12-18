#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_24__ {scalar_t__ queueCxt; int firstCall; int qual_ok; TYPE_1__* giststate; int /*<<< orphan*/ * orderByTypes; int /*<<< orphan*/ * queue; void* pageDataCxt; } ;
struct TYPE_23__ {int numberOfKeys; int numberOfOrderBys; int /*<<< orphan*/ * xs_hitup; TYPE_15__* indexRelation; TYPE_2__* orderByData; TYPE_2__* keyData; int /*<<< orphan*/  xs_hitupdesc; scalar_t__ xs_want_itup; int /*<<< orphan*/  opaque; } ;
struct TYPE_18__ {void* fn_extra; int /*<<< orphan*/  fn_oid; } ;
struct TYPE_22__ {int sk_attno; int sk_flags; TYPE_12__ sk_func; } ;
struct TYPE_21__ {scalar_t__ scanCxt; TYPE_5__* distanceFn; TYPE_5__* consistentFn; int /*<<< orphan*/  fetchTupdesc; int /*<<< orphan*/  leafTupdesc; } ;
struct TYPE_20__ {int /*<<< orphan*/ * rd_opcintype; } ;
struct TYPE_19__ {int /*<<< orphan*/  atttypid; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__* ScanKey ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ MemoryContext ;
typedef  TYPE_3__* IndexScanDesc ;
typedef  TYPE_4__* GISTScanOpaque ;
typedef  TYPE_5__ FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 void* AllocSetContextCreate (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CreateTemplateTupleDesc (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GIST_DISTANCE_PROC ; 
 int IndexRelationGetNumberOfKeyAttributes (TYPE_15__*) ; 
 int /*<<< orphan*/  MemoryContextReset (scalar_t__) ; 
 scalar_t__ MemoryContextSwitchTo (scalar_t__) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int RelationGetNumberOfAttributes (TYPE_15__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_15__*) ; 
 int SK_ISNULL ; 
 int SK_SEARCHNOTNULL ; 
 int SK_SEARCHNULL ; 
 TYPE_14__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TupleDescInitEntry (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmgr_info_copy (TYPE_12__*,TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  get_func_rettype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  pairingheap_GISTSearchItem_cmp ; 
 int /*<<< orphan*/ * pairingheap_allocate (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (void**) ; 

void
gistrescan(IndexScanDesc scan, ScanKey key, int nkeys,
		   ScanKey orderbys, int norderbys)
{
	/* nkeys and norderbys arguments are ignored */
	GISTScanOpaque so = (GISTScanOpaque) scan->opaque;
	bool		first_time;
	int			i;
	MemoryContext oldCxt;

	/* rescan an existing indexscan --- reset state */

	/*
	 * The first time through, we create the search queue in the scanCxt.
	 * Subsequent times through, we create the queue in a separate queueCxt,
	 * which is created on the second call and reset on later calls.  Thus, in
	 * the common case where a scan is only rescan'd once, we just put the
	 * queue in scanCxt and don't pay the overhead of making a second memory
	 * context.  If we do rescan more than once, the first queue is just left
	 * for dead until end of scan; this small wastage seems worth the savings
	 * in the common case.
	 */
	if (so->queue == NULL)
	{
		/* first time through */
		Assert(so->queueCxt == so->giststate->scanCxt);
		first_time = true;
	}
	else if (so->queueCxt == so->giststate->scanCxt)
	{
		/* second time through */
		so->queueCxt = AllocSetContextCreate(so->giststate->scanCxt,
											 "GiST queue context",
											 ALLOCSET_DEFAULT_SIZES);
		first_time = false;
	}
	else
	{
		/* third or later time through */
		MemoryContextReset(so->queueCxt);
		first_time = false;
	}

	/*
	 * If we're doing an index-only scan, on the first call, also initialize a
	 * tuple descriptor to represent the returned index tuples and create a
	 * memory context to hold them during the scan.
	 */
	if (scan->xs_want_itup && !scan->xs_hitupdesc)
	{
		int			natts;
		int			nkeyatts;
		int			attno;

		/*
		 * The storage type of the index can be different from the original
		 * datatype being indexed, so we cannot just grab the index's tuple
		 * descriptor. Instead, construct a descriptor with the original data
		 * types.
		 */
		natts = RelationGetNumberOfAttributes(scan->indexRelation);
		nkeyatts = IndexRelationGetNumberOfKeyAttributes(scan->indexRelation);
		so->giststate->fetchTupdesc = CreateTemplateTupleDesc(natts);
		for (attno = 1; attno <= nkeyatts; attno++)
		{
			TupleDescInitEntry(so->giststate->fetchTupdesc, attno, NULL,
							   scan->indexRelation->rd_opcintype[attno - 1],
							   -1, 0);
		}

		for (; attno <= natts; attno++)
		{
			/* taking opcintype from giststate->tupdesc */
			TupleDescInitEntry(so->giststate->fetchTupdesc, attno, NULL,
							   TupleDescAttr(so->giststate->leafTupdesc,
											 attno - 1)->atttypid,
							   -1, 0);
		}
		scan->xs_hitupdesc = so->giststate->fetchTupdesc;

		/* Also create a memory context that will hold the returned tuples */
		so->pageDataCxt = AllocSetContextCreate(so->giststate->scanCxt,
												"GiST page data context",
												ALLOCSET_DEFAULT_SIZES);
	}

	/* create new, empty pairing heap for search queue */
	oldCxt = MemoryContextSwitchTo(so->queueCxt);
	so->queue = pairingheap_allocate(pairingheap_GISTSearchItem_cmp, scan);
	MemoryContextSwitchTo(oldCxt);

	so->firstCall = true;

	/* Update scan key, if a new one is given */
	if (key && scan->numberOfKeys > 0)
	{
		void	  **fn_extras = NULL;

		/*
		 * If this isn't the first time through, preserve the fn_extra
		 * pointers, so that if the consistentFns are using them to cache
		 * data, that data is not leaked across a rescan.
		 */
		if (!first_time)
		{
			fn_extras = (void **) palloc(scan->numberOfKeys * sizeof(void *));
			for (i = 0; i < scan->numberOfKeys; i++)
				fn_extras[i] = scan->keyData[i].sk_func.fn_extra;
		}

		memmove(scan->keyData, key,
				scan->numberOfKeys * sizeof(ScanKeyData));

		/*
		 * Modify the scan key so that the Consistent method is called for all
		 * comparisons. The original operator is passed to the Consistent
		 * function in the form of its strategy number, which is available
		 * from the sk_strategy field, and its subtype from the sk_subtype
		 * field.
		 *
		 * Next, if any of keys is a NULL and that key is not marked with
		 * SK_SEARCHNULL/SK_SEARCHNOTNULL then nothing can be found (ie, we
		 * assume all indexable operators are strict).
		 */
		so->qual_ok = true;

		for (i = 0; i < scan->numberOfKeys; i++)
		{
			ScanKey		skey = scan->keyData + i;

			/*
			 * Copy consistent support function to ScanKey structure instead
			 * of function implementing filtering operator.
			 */
			fmgr_info_copy(&(skey->sk_func),
						   &(so->giststate->consistentFn[skey->sk_attno - 1]),
						   so->giststate->scanCxt);

			/* Restore prior fn_extra pointers, if not first time */
			if (!first_time)
				skey->sk_func.fn_extra = fn_extras[i];

			if (skey->sk_flags & SK_ISNULL)
			{
				if (!(skey->sk_flags & (SK_SEARCHNULL | SK_SEARCHNOTNULL)))
					so->qual_ok = false;
			}
		}

		if (!first_time)
			pfree(fn_extras);
	}

	/* Update order-by key, if a new one is given */
	if (orderbys && scan->numberOfOrderBys > 0)
	{
		void	  **fn_extras = NULL;

		/* As above, preserve fn_extra if not first time through */
		if (!first_time)
		{
			fn_extras = (void **) palloc(scan->numberOfOrderBys * sizeof(void *));
			for (i = 0; i < scan->numberOfOrderBys; i++)
				fn_extras[i] = scan->orderByData[i].sk_func.fn_extra;
		}

		memmove(scan->orderByData, orderbys,
				scan->numberOfOrderBys * sizeof(ScanKeyData));

		so->orderByTypes = (Oid *) palloc(scan->numberOfOrderBys * sizeof(Oid));

		/*
		 * Modify the order-by key so that the Distance method is called for
		 * all comparisons. The original operator is passed to the Distance
		 * function in the form of its strategy number, which is available
		 * from the sk_strategy field, and its subtype from the sk_subtype
		 * field.
		 */
		for (i = 0; i < scan->numberOfOrderBys; i++)
		{
			ScanKey		skey = scan->orderByData + i;
			FmgrInfo   *finfo = &(so->giststate->distanceFn[skey->sk_attno - 1]);

			/* Check we actually have a distance function ... */
			if (!OidIsValid(finfo->fn_oid))
				elog(ERROR, "missing support function %d for attribute %d of index \"%s\"",
					 GIST_DISTANCE_PROC, skey->sk_attno,
					 RelationGetRelationName(scan->indexRelation));

			/*
			 * Look up the datatype returned by the original ordering
			 * operator. GiST always uses a float8 for the distance function,
			 * but the ordering operator could be anything else.
			 *
			 * XXX: The distance function is only allowed to be lossy if the
			 * ordering operator's result type is float4 or float8.  Otherwise
			 * we don't know how to return the distance to the executor.  But
			 * we cannot check that here, as we won't know if the distance
			 * function is lossy until it returns *recheck = true for the
			 * first time.
			 */
			so->orderByTypes[i] = get_func_rettype(skey->sk_func.fn_oid);

			/*
			 * Copy distance support function to ScanKey structure instead of
			 * function implementing ordering operator.
			 */
			fmgr_info_copy(&(skey->sk_func), finfo, so->giststate->scanCxt);

			/* Restore prior fn_extra pointers, if not first time */
			if (!first_time)
				skey->sk_func.fn_extra = fn_extras[i];
		}

		if (!first_time)
			pfree(fn_extras);
	}

	/* any previous xs_hitup will have been pfree'd in context resets above */
	scan->xs_hitup = NULL;
}
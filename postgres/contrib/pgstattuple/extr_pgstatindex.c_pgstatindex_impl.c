#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_12__ {double version; double level; double root_blkno; int internal_pages; int leaf_pages; int empty_pages; int deleted_pages; scalar_t__ max_avail; scalar_t__ fragments; scalar_t__ free_space; } ;
struct TYPE_11__ {double btm_version; double btm_level; double btm_root; } ;
struct TYPE_10__ {scalar_t__ btpo_next; } ;
struct TYPE_9__ {int pd_special; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  BufferAccessStrategy ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_2__* BTPageOpaque ;
typedef  TYPE_3__ BTMetaPageData ;
typedef  TYPE_4__ BTIndexStat ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  BAS_BULKREAD ; 
 int BLCKSZ ; 
 TYPE_3__* BTPageGetMeta (scalar_t__) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BuildTupleFromCStrings (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetAccessStrategy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 char* INT64_FORMAT ; 
 int /*<<< orphan*/  IS_BTREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ P_IGNORE (TYPE_2__*) ; 
 scalar_t__ P_ISDELETED (TYPE_2__*) ; 
 scalar_t__ P_ISLEAF (TYPE_2__*) ; 
 scalar_t__ P_NONE ; 
 scalar_t__ PageGetFreeSpace (scalar_t__) ; 
 scalar_t__ PageGetSpecialPointer (scalar_t__) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 scalar_t__ RELATION_IS_OTHER_TEMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int SizeOfPageHeaderData ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 int /*<<< orphan*/  TupleDescGetAttInMetadata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ get_call_result_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* psprintf (char*,double) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
pgstatindex_impl(Relation rel, FunctionCallInfo fcinfo)
{
	Datum		result;
	BlockNumber nblocks;
	BlockNumber blkno;
	BTIndexStat indexStat;
	BufferAccessStrategy bstrategy = GetAccessStrategy(BAS_BULKREAD);

	if (!IS_INDEX(rel) || !IS_BTREE(rel))
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("relation \"%s\" is not a btree index",
						RelationGetRelationName(rel))));

	/*
	 * Reject attempts to read non-local temporary relations; we would be
	 * likely to get wrong data since we have no visibility into the owning
	 * session's local buffers.
	 */
	if (RELATION_IS_OTHER_TEMP(rel))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot access temporary tables of other sessions")));

	/*
	 * Read metapage
	 */
	{
		Buffer		buffer = ReadBufferExtended(rel, MAIN_FORKNUM, 0, RBM_NORMAL, bstrategy);
		Page		page = BufferGetPage(buffer);
		BTMetaPageData *metad = BTPageGetMeta(page);

		indexStat.version = metad->btm_version;
		indexStat.level = metad->btm_level;
		indexStat.root_blkno = metad->btm_root;

		ReleaseBuffer(buffer);
	}

	/* -- init counters -- */
	indexStat.internal_pages = 0;
	indexStat.leaf_pages = 0;
	indexStat.empty_pages = 0;
	indexStat.deleted_pages = 0;

	indexStat.max_avail = 0;
	indexStat.free_space = 0;

	indexStat.fragments = 0;

	/*
	 * Scan all blocks except the metapage
	 */
	nblocks = RelationGetNumberOfBlocks(rel);

	for (blkno = 1; blkno < nblocks; blkno++)
	{
		Buffer		buffer;
		Page		page;
		BTPageOpaque opaque;

		CHECK_FOR_INTERRUPTS();

		/* Read and lock buffer */
		buffer = ReadBufferExtended(rel, MAIN_FORKNUM, blkno, RBM_NORMAL, bstrategy);
		LockBuffer(buffer, BUFFER_LOCK_SHARE);

		page = BufferGetPage(buffer);
		opaque = (BTPageOpaque) PageGetSpecialPointer(page);

		/* Determine page type, and update totals */

		if (P_ISDELETED(opaque))
			indexStat.deleted_pages++;
		else if (P_IGNORE(opaque))
			indexStat.empty_pages++;	/* this is the "half dead" state */
		else if (P_ISLEAF(opaque))
		{
			int			max_avail;

			max_avail = BLCKSZ - (BLCKSZ - ((PageHeader) page)->pd_special + SizeOfPageHeaderData);
			indexStat.max_avail += max_avail;
			indexStat.free_space += PageGetFreeSpace(page);

			indexStat.leaf_pages++;

			/*
			 * If the next leaf is on an earlier block, it means a
			 * fragmentation.
			 */
			if (opaque->btpo_next != P_NONE && opaque->btpo_next < blkno)
				indexStat.fragments++;
		}
		else
			indexStat.internal_pages++;

		/* Unlock and release buffer */
		LockBuffer(buffer, BUFFER_LOCK_UNLOCK);
		ReleaseBuffer(buffer);
	}

	relation_close(rel, AccessShareLock);

	/*----------------------------
	 * Build a result tuple
	 *----------------------------
	 */
	{
		TupleDesc	tupleDesc;
		int			j;
		char	   *values[10];
		HeapTuple	tuple;

		/* Build a tuple descriptor for our result type */
		if (get_call_result_type(fcinfo, NULL, &tupleDesc) != TYPEFUNC_COMPOSITE)
			elog(ERROR, "return type must be a row type");

		j = 0;
		values[j++] = psprintf("%d", indexStat.version);
		values[j++] = psprintf("%d", indexStat.level);
		values[j++] = psprintf(INT64_FORMAT,
							   (1 + /* include the metapage in index_size */
								indexStat.leaf_pages +
								indexStat.internal_pages +
								indexStat.deleted_pages +
								indexStat.empty_pages) * BLCKSZ);
		values[j++] = psprintf("%u", indexStat.root_blkno);
		values[j++] = psprintf(INT64_FORMAT, indexStat.internal_pages);
		values[j++] = psprintf(INT64_FORMAT, indexStat.leaf_pages);
		values[j++] = psprintf(INT64_FORMAT, indexStat.empty_pages);
		values[j++] = psprintf(INT64_FORMAT, indexStat.deleted_pages);
		if (indexStat.max_avail > 0)
			values[j++] = psprintf("%.2f",
								   100.0 - (double) indexStat.free_space / (double) indexStat.max_avail * 100.0);
		else
			values[j++] = pstrdup("NaN");
		if (indexStat.leaf_pages > 0)
			values[j++] = psprintf("%.2f",
								   (double) indexStat.fragments / (double) indexStat.leaf_pages * 100.0);
		else
			values[j++] = pstrdup("NaN");

		tuple = BuildTupleFromCStrings(TupleDescGetAttInMetadata(tupleDesc),
									   values);

		result = HeapTupleGetDatum(tuple);
	}

	return result;
}
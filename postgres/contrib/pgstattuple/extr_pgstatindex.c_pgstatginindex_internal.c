#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {int /*<<< orphan*/  pending_tuples; int /*<<< orphan*/  pending_pages; int /*<<< orphan*/  version; } ;
struct TYPE_4__ {int /*<<< orphan*/  nPendingHeapTuples; int /*<<< orphan*/  nPendingPages; int /*<<< orphan*/  ginVersion; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__ GinMetaPageData ;
typedef  TYPE_2__ GinIndexStat ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GIN_METAPAGE_BLKNO ; 
 int /*<<< orphan*/  GIN_SHARE ; 
 TYPE_1__* GinPageGetMeta (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_GIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RELATION_IS_OTHER_TEMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 int /*<<< orphan*/  UInt32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ get_call_result_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Datum
pgstatginindex_internal(Oid relid, FunctionCallInfo fcinfo)
{
	Relation	rel;
	Buffer		buffer;
	Page		page;
	GinMetaPageData *metadata;
	GinIndexStat stats;
	HeapTuple	tuple;
	TupleDesc	tupleDesc;
	Datum		values[3];
	bool		nulls[3] = {false, false, false};
	Datum		result;

	rel = relation_open(relid, AccessShareLock);

	if (!IS_INDEX(rel) || !IS_GIN(rel))
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("relation \"%s\" is not a GIN index",
						RelationGetRelationName(rel))));

	/*
	 * Reject attempts to read non-local temporary relations; we would be
	 * likely to get wrong data since we have no visibility into the owning
	 * session's local buffers.
	 */
	if (RELATION_IS_OTHER_TEMP(rel))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot access temporary indexes of other sessions")));

	/*
	 * Read metapage
	 */
	buffer = ReadBuffer(rel, GIN_METAPAGE_BLKNO);
	LockBuffer(buffer, GIN_SHARE);
	page = BufferGetPage(buffer);
	metadata = GinPageGetMeta(page);

	stats.version = metadata->ginVersion;
	stats.pending_pages = metadata->nPendingPages;
	stats.pending_tuples = metadata->nPendingHeapTuples;

	UnlockReleaseBuffer(buffer);
	relation_close(rel, AccessShareLock);

	/*
	 * Build a tuple descriptor for our result type
	 */
	if (get_call_result_type(fcinfo, NULL, &tupleDesc) != TYPEFUNC_COMPOSITE)
		elog(ERROR, "return type must be a row type");

	values[0] = Int32GetDatum(stats.version);
	values[1] = UInt32GetDatum(stats.pending_pages);
	values[2] = Int64GetDatum(stats.pending_tuples);

	/*
	 * Build and return the tuple
	 */
	tuple = heap_form_tuple(tupleDesc, values, nulls);
	result = HeapTupleGetDatum(tuple);

	return result;
}
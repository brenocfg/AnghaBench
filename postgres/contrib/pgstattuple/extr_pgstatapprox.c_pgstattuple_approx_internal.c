#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  free_percent; int /*<<< orphan*/  free_space; int /*<<< orphan*/  dead_tuple_percent; int /*<<< orphan*/  dead_tuple_len; int /*<<< orphan*/  dead_tuple_count; int /*<<< orphan*/  tuple_percent; int /*<<< orphan*/  tuple_len; int /*<<< orphan*/  tuple_count; int /*<<< orphan*/  scanned_percent; int /*<<< orphan*/  table_len; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ output_type ;
typedef  int /*<<< orphan*/  nulls ;
typedef  TYPE_3__* TupleDesc ;
struct TYPE_16__ {TYPE_1__* rd_rel; } ;
struct TYPE_15__ {int natts; } ;
struct TYPE_13__ {scalar_t__ relkind; scalar_t__ relam; } ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  Float8GetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ HEAP_TABLE_AM_OID ; 
 int /*<<< orphan*/  HeapTupleGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int NUM_OUTPUT_COLUMNS ; 
 scalar_t__ RELATION_IS_OTHER_TEMP (TYPE_4__*) ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_4__*) ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ get_call_result_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  heap_form_tuple (TYPE_3__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  relation_close (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statapprox_heap (TYPE_4__*,TYPE_2__*) ; 

Datum
pgstattuple_approx_internal(Oid relid, FunctionCallInfo fcinfo)
{
	Relation	rel;
	output_type stat = {0};
	TupleDesc	tupdesc;
	bool		nulls[NUM_OUTPUT_COLUMNS];
	Datum		values[NUM_OUTPUT_COLUMNS];
	HeapTuple	ret;
	int			i = 0;

	if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE)
		elog(ERROR, "return type must be a row type");

	if (tupdesc->natts != NUM_OUTPUT_COLUMNS)
		elog(ERROR, "incorrect number of output arguments");

	rel = relation_open(relid, AccessShareLock);

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
	 * We support only ordinary relations and materialised views, because we
	 * depend on the visibility map and free space map for our estimates about
	 * unscanned pages.
	 */
	if (!(rel->rd_rel->relkind == RELKIND_RELATION ||
		  rel->rd_rel->relkind == RELKIND_MATVIEW))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("\"%s\" is not a table or materialized view",
						RelationGetRelationName(rel))));

	if (rel->rd_rel->relam != HEAP_TABLE_AM_OID)
		ereport(ERROR, (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						errmsg("only heap AM is supported")));

	statapprox_heap(rel, &stat);

	relation_close(rel, AccessShareLock);

	memset(nulls, 0, sizeof(nulls));

	values[i++] = Int64GetDatum(stat.table_len);
	values[i++] = Float8GetDatum(stat.scanned_percent);
	values[i++] = Int64GetDatum(stat.tuple_count);
	values[i++] = Int64GetDatum(stat.tuple_len);
	values[i++] = Float8GetDatum(stat.tuple_percent);
	values[i++] = Int64GetDatum(stat.dead_tuple_count);
	values[i++] = Int64GetDatum(stat.dead_tuple_len);
	values[i++] = Float8GetDatum(stat.dead_tuple_percent);
	values[i++] = Int64GetDatum(stat.free_space);
	values[i++] = Float8GetDatum(stat.free_percent);

	ret = heap_form_tuple(tupdesc, values, nulls);
	return HeapTupleGetDatum(ret);
}
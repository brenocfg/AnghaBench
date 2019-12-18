#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_12__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_24__ {TYPE_9__ cmp_proc_finfo; } ;
typedef  TYPE_1__ TypeCacheEntry ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_28__ {int atttypmod; int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attcollation; int /*<<< orphan*/  attndims; } ;
struct TYPE_27__ {int oneCol; int* canPartialMatch; int /*<<< orphan*/ * supportCollation; TYPE_12__* comparePartialFn; TYPE_12__* triConsistentFn; TYPE_12__* consistentFn; TYPE_12__* extractQueryFn; TYPE_12__* extractValueFn; TYPE_12__* compareFn; TYPE_2__** tupdesc; TYPE_2__* origTupdesc; TYPE_3__* index; } ;
struct TYPE_26__ {int /*<<< orphan*/ * rd_indcollation; } ;
struct TYPE_25__ {int natts; } ;
struct TYPE_23__ {scalar_t__ fn_oid; } ;
typedef  TYPE_3__* Relation ;
typedef  TYPE_4__ GinState ;
typedef  TYPE_5__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 TYPE_2__* CreateTemplateTupleDesc (int) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FUNCTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GIN_COMPARE_PARTIAL_PROC ; 
 int /*<<< orphan*/  GIN_COMPARE_PROC ; 
 int /*<<< orphan*/  GIN_CONSISTENT_PROC ; 
 int /*<<< orphan*/  GIN_EXTRACTQUERY_PROC ; 
 int /*<<< orphan*/  GIN_EXTRACTVALUE_PROC ; 
 int /*<<< orphan*/  GIN_TRICONSISTENT_PROC ; 
 int /*<<< orphan*/  INT2OID ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  MemSet (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 TYPE_2__* RelationGetDescr (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 int /*<<< orphan*/  TYPECACHE_CMP_PROC_FINFO ; 
 TYPE_5__* TupleDescAttr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  TupleDescInitEntry (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupleDescInitEntryCollation (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmgr_info_copy (TYPE_12__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 scalar_t__ index_getprocid (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 TYPE_9__* index_getprocinfo (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* lookup_type_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
initGinState(GinState *state, Relation index)
{
	TupleDesc	origTupdesc = RelationGetDescr(index);
	int			i;

	MemSet(state, 0, sizeof(GinState));

	state->index = index;
	state->oneCol = (origTupdesc->natts == 1) ? true : false;
	state->origTupdesc = origTupdesc;

	for (i = 0; i < origTupdesc->natts; i++)
	{
		Form_pg_attribute attr = TupleDescAttr(origTupdesc, i);

		if (state->oneCol)
			state->tupdesc[i] = state->origTupdesc;
		else
		{
			state->tupdesc[i] = CreateTemplateTupleDesc(2);

			TupleDescInitEntry(state->tupdesc[i], (AttrNumber) 1, NULL,
							   INT2OID, -1, 0);
			TupleDescInitEntry(state->tupdesc[i], (AttrNumber) 2, NULL,
							   attr->atttypid,
							   attr->atttypmod,
							   attr->attndims);
			TupleDescInitEntryCollation(state->tupdesc[i], (AttrNumber) 2,
										attr->attcollation);
		}

		/*
		 * If the compare proc isn't specified in the opclass definition, look
		 * up the index key type's default btree comparator.
		 */
		if (index_getprocid(index, i + 1, GIN_COMPARE_PROC) != InvalidOid)
		{
			fmgr_info_copy(&(state->compareFn[i]),
						   index_getprocinfo(index, i + 1, GIN_COMPARE_PROC),
						   CurrentMemoryContext);
		}
		else
		{
			TypeCacheEntry *typentry;

			typentry = lookup_type_cache(attr->atttypid,
										 TYPECACHE_CMP_PROC_FINFO);
			if (!OidIsValid(typentry->cmp_proc_finfo.fn_oid))
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_FUNCTION),
						 errmsg("could not identify a comparison function for type %s",
								format_type_be(attr->atttypid))));
			fmgr_info_copy(&(state->compareFn[i]),
						   &(typentry->cmp_proc_finfo),
						   CurrentMemoryContext);
		}

		/* Opclass must always provide extract procs */
		fmgr_info_copy(&(state->extractValueFn[i]),
					   index_getprocinfo(index, i + 1, GIN_EXTRACTVALUE_PROC),
					   CurrentMemoryContext);
		fmgr_info_copy(&(state->extractQueryFn[i]),
					   index_getprocinfo(index, i + 1, GIN_EXTRACTQUERY_PROC),
					   CurrentMemoryContext);

		/*
		 * Check opclass capability to do tri-state or binary logic consistent
		 * check.
		 */
		if (index_getprocid(index, i + 1, GIN_TRICONSISTENT_PROC) != InvalidOid)
		{
			fmgr_info_copy(&(state->triConsistentFn[i]),
						   index_getprocinfo(index, i + 1, GIN_TRICONSISTENT_PROC),
						   CurrentMemoryContext);
		}

		if (index_getprocid(index, i + 1, GIN_CONSISTENT_PROC) != InvalidOid)
		{
			fmgr_info_copy(&(state->consistentFn[i]),
						   index_getprocinfo(index, i + 1, GIN_CONSISTENT_PROC),
						   CurrentMemoryContext);
		}

		if (state->consistentFn[i].fn_oid == InvalidOid &&
			state->triConsistentFn[i].fn_oid == InvalidOid)
		{
			elog(ERROR, "missing GIN support function (%d or %d) for attribute %d of index \"%s\"",
				 GIN_CONSISTENT_PROC, GIN_TRICONSISTENT_PROC,
				 i + 1, RelationGetRelationName(index));
		}

		/*
		 * Check opclass capability to do partial match.
		 */
		if (index_getprocid(index, i + 1, GIN_COMPARE_PARTIAL_PROC) != InvalidOid)
		{
			fmgr_info_copy(&(state->comparePartialFn[i]),
						   index_getprocinfo(index, i + 1, GIN_COMPARE_PARTIAL_PROC),
						   CurrentMemoryContext);
			state->canPartialMatch[i] = true;
		}
		else
		{
			state->canPartialMatch[i] = false;
		}

		/*
		 * If the index column has a specified collation, we should honor that
		 * while doing comparisons.  However, we may have a collatable storage
		 * type for a noncollatable indexed data type (for instance, hstore
		 * uses text index entries).  If there's no index collation then
		 * specify default collation in case the support functions need
		 * collation.  This is harmless if the support functions don't care
		 * about collation, so we just do it unconditionally.  (We could
		 * alternatively call get_typcollation, but that seems like expensive
		 * overkill --- there aren't going to be any cases where a GIN storage
		 * type has a nondefault collation.)
		 */
		if (OidIsValid(index->rd_indcollation[i]))
			state->supportCollation[i] = index->rd_indcollation[i];
		else
			state->supportCollation[i] = DEFAULT_COLLATION_OID;
	}
}
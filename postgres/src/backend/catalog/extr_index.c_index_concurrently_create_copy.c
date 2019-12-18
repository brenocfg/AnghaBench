#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  values; } ;
typedef  TYPE_2__ oidvector ;
struct TYPE_19__ {int /*<<< orphan*/  values; } ;
typedef  TYPE_3__ int2vector ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_22__ {int /*<<< orphan*/  attname; } ;
struct TYPE_21__ {int ii_NumIndexAttrs; int /*<<< orphan*/ * ii_IndexAttrNumbers; int /*<<< orphan*/  ii_Unique; int /*<<< orphan*/  ii_Am; int /*<<< orphan*/  ii_NumIndexKeyAttrs; int /*<<< orphan*/ * ii_Predicate; int /*<<< orphan*/ * ii_Expressions; int /*<<< orphan*/ * ii_ExclusionOps; } ;
struct TYPE_20__ {int /*<<< orphan*/  rd_indcollation; TYPE_1__* rd_rel; } ;
struct TYPE_17__ {int /*<<< orphan*/  reltablespace; int /*<<< orphan*/  relam; } ;
typedef  TYPE_4__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_5__ IndexInfo ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_6__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_class_reloptions ; 
 int /*<<< orphan*/  Anum_pg_index_indclass ; 
 int /*<<< orphan*/  Anum_pg_index_indexprs ; 
 int /*<<< orphan*/  Anum_pg_index_indoption ; 
 int /*<<< orphan*/  Anum_pg_index_indpred ; 
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_5__* BuildIndexInfo (TYPE_4__*) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int INDEX_CREATE_CONCURRENT ; 
 int INDEX_CREATE_SKIP_BUILD ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_4__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 TYPE_6__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  index_close (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_create (TYPE_4__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 TYPE_4__* index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* makeIndexInfo (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * make_ands_implicit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 scalar_t__ stringToNode (char*) ; 

Oid
index_concurrently_create_copy(Relation heapRelation, Oid oldIndexId, const char *newName)
{
	Relation	indexRelation;
	IndexInfo  *oldInfo,
			   *newInfo;
	Oid			newIndexId = InvalidOid;
	HeapTuple	indexTuple,
				classTuple;
	Datum		indclassDatum,
				colOptionDatum,
				optionDatum;
	oidvector  *indclass;
	int2vector *indcoloptions;
	bool		isnull;
	List	   *indexColNames = NIL;
	List	   *indexExprs = NIL;
	List	   *indexPreds = NIL;

	indexRelation = index_open(oldIndexId, RowExclusiveLock);

	/* The new index needs some information from the old index */
	oldInfo = BuildIndexInfo(indexRelation);

	/*
	 * Concurrent build of an index with exclusion constraints is not
	 * supported.
	 */
	if (oldInfo->ii_ExclusionOps != NULL)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("concurrent index creation for exclusion constraints is not supported")));

	/* Get the array of class and column options IDs from index info */
	indexTuple = SearchSysCache1(INDEXRELID, ObjectIdGetDatum(oldIndexId));
	if (!HeapTupleIsValid(indexTuple))
		elog(ERROR, "cache lookup failed for index %u", oldIndexId);
	indclassDatum = SysCacheGetAttr(INDEXRELID, indexTuple,
									Anum_pg_index_indclass, &isnull);
	Assert(!isnull);
	indclass = (oidvector *) DatumGetPointer(indclassDatum);

	colOptionDatum = SysCacheGetAttr(INDEXRELID, indexTuple,
									 Anum_pg_index_indoption, &isnull);
	Assert(!isnull);
	indcoloptions = (int2vector *) DatumGetPointer(colOptionDatum);

	/* Fetch options of index if any */
	classTuple = SearchSysCache1(RELOID, oldIndexId);
	if (!HeapTupleIsValid(classTuple))
		elog(ERROR, "cache lookup failed for relation %u", oldIndexId);
	optionDatum = SysCacheGetAttr(RELOID, classTuple,
								  Anum_pg_class_reloptions, &isnull);

	/*
	 * Fetch the list of expressions and predicates directly from the
	 * catalogs.  This cannot rely on the information from IndexInfo of the
	 * old index as these have been flattened for the planner.
	 */
	if (oldInfo->ii_Expressions != NIL)
	{
		Datum		exprDatum;
		char	   *exprString;

		exprDatum = SysCacheGetAttr(INDEXRELID, indexTuple,
									Anum_pg_index_indexprs, &isnull);
		Assert(!isnull);
		exprString = TextDatumGetCString(exprDatum);
		indexExprs = (List *) stringToNode(exprString);
		pfree(exprString);
	}
	if (oldInfo->ii_Predicate != NIL)
	{
		Datum		predDatum;
		char	   *predString;

		predDatum = SysCacheGetAttr(INDEXRELID, indexTuple,
									Anum_pg_index_indpred, &isnull);
		Assert(!isnull);
		predString = TextDatumGetCString(predDatum);
		indexPreds = (List *) stringToNode(predString);

		/* Also convert to implicit-AND format */
		indexPreds = make_ands_implicit((Expr *) indexPreds);
		pfree(predString);
	}

	/*
	 * Build the index information for the new index.  Note that rebuild of
	 * indexes with exclusion constraints is not supported, hence there is no
	 * need to fill all the ii_Exclusion* fields.
	 */
	newInfo = makeIndexInfo(oldInfo->ii_NumIndexAttrs,
							oldInfo->ii_NumIndexKeyAttrs,
							oldInfo->ii_Am,
							indexExprs,
							indexPreds,
							oldInfo->ii_Unique,
							false,	/* not ready for inserts */
							true);

	/*
	 * Extract the list of column names and the column numbers for the new
	 * index information.  All this information will be used for the index
	 * creation.
	 */
	for (int i = 0; i < oldInfo->ii_NumIndexAttrs; i++)
	{
		TupleDesc	indexTupDesc = RelationGetDescr(indexRelation);
		Form_pg_attribute att = TupleDescAttr(indexTupDesc, i);

		indexColNames = lappend(indexColNames, NameStr(att->attname));
		newInfo->ii_IndexAttrNumbers[i] = oldInfo->ii_IndexAttrNumbers[i];
	}

	/*
	 * Now create the new index.
	 *
	 * For a partition index, we adjust the partition dependency later, to
	 * ensure a consistent state at all times.  That is why parentIndexRelid
	 * is not set here.
	 */
	newIndexId = index_create(heapRelation,
							  newName,
							  InvalidOid,	/* indexRelationId */
							  InvalidOid,	/* parentIndexRelid */
							  InvalidOid,	/* parentConstraintId */
							  InvalidOid,	/* relFileNode */
							  newInfo,
							  indexColNames,
							  indexRelation->rd_rel->relam,
							  indexRelation->rd_rel->reltablespace,
							  indexRelation->rd_indcollation,
							  indclass->values,
							  indcoloptions->values,
							  optionDatum,
							  INDEX_CREATE_SKIP_BUILD | INDEX_CREATE_CONCURRENT,
							  0,
							  true, /* allow table to be a system catalog? */
							  false,	/* is_internal? */
							  NULL);

	/* Close the relations used and clean up */
	index_close(indexRelation, NoLock);
	ReleaseSysCache(indexTuple);
	ReleaseSysCache(classTuple);

	return newIndexId;
}
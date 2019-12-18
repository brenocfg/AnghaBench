#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * values; } ;
typedef  TYPE_1__ oidvector ;
typedef  int /*<<< orphan*/  nulls ;
typedef  TYPE_1__ int2vector ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_9__ {int ii_NumIndexAttrs; int ii_NumIndexKeyAttrs; scalar_t__ ii_Expressions; scalar_t__ ii_Predicate; int ii_Unique; int /*<<< orphan*/ * ii_IndexAttrNumbers; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ IndexInfo ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int Anum_pg_index_indcheckxmin ; 
 int Anum_pg_index_indclass ; 
 int Anum_pg_index_indcollation ; 
 int Anum_pg_index_indexprs ; 
 int Anum_pg_index_indexrelid ; 
 int Anum_pg_index_indimmediate ; 
 int Anum_pg_index_indisclustered ; 
 int Anum_pg_index_indisexclusion ; 
 int Anum_pg_index_indislive ; 
 int Anum_pg_index_indisprimary ; 
 int Anum_pg_index_indisready ; 
 int Anum_pg_index_indisreplident ; 
 int Anum_pg_index_indisunique ; 
 int Anum_pg_index_indisvalid ; 
 int Anum_pg_index_indkey ; 
 int Anum_pg_index_indnatts ; 
 int Anum_pg_index_indnkeyatts ; 
 int Anum_pg_index_indoption ; 
 int Anum_pg_index_indpred ; 
 int Anum_pg_index_indrelid ; 
 scalar_t__ BoolGetDatum (int) ; 
 scalar_t__ CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexRelationId ; 
 scalar_t__ Int16GetDatum (int) ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 scalar_t__ NIL ; 
 int Natts_pg_index ; 
 scalar_t__ ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ PointerGetDatum (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* buildint2vector (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* buildoidvector (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 scalar_t__ make_ands_explicit (scalar_t__) ; 
 char* nodeToString (scalar_t__) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
UpdateIndexRelation(Oid indexoid,
					Oid heapoid,
					Oid parentIndexId,
					IndexInfo *indexInfo,
					Oid *collationOids,
					Oid *classOids,
					int16 *coloptions,
					bool primary,
					bool isexclusion,
					bool immediate,
					bool isvalid,
					bool isready)
{
	int2vector *indkey;
	oidvector  *indcollation;
	oidvector  *indclass;
	int2vector *indoption;
	Datum		exprsDatum;
	Datum		predDatum;
	Datum		values[Natts_pg_index];
	bool		nulls[Natts_pg_index];
	Relation	pg_index;
	HeapTuple	tuple;
	int			i;

	/*
	 * Copy the index key, opclass, and indoption info into arrays (should we
	 * make the caller pass them like this to start with?)
	 */
	indkey = buildint2vector(NULL, indexInfo->ii_NumIndexAttrs);
	for (i = 0; i < indexInfo->ii_NumIndexAttrs; i++)
		indkey->values[i] = indexInfo->ii_IndexAttrNumbers[i];
	indcollation = buildoidvector(collationOids, indexInfo->ii_NumIndexKeyAttrs);
	indclass = buildoidvector(classOids, indexInfo->ii_NumIndexKeyAttrs);
	indoption = buildint2vector(coloptions, indexInfo->ii_NumIndexKeyAttrs);

	/*
	 * Convert the index expressions (if any) to a text datum
	 */
	if (indexInfo->ii_Expressions != NIL)
	{
		char	   *exprsString;

		exprsString = nodeToString(indexInfo->ii_Expressions);
		exprsDatum = CStringGetTextDatum(exprsString);
		pfree(exprsString);
	}
	else
		exprsDatum = (Datum) 0;

	/*
	 * Convert the index predicate (if any) to a text datum.  Note we convert
	 * implicit-AND format to normal explicit-AND for storage.
	 */
	if (indexInfo->ii_Predicate != NIL)
	{
		char	   *predString;

		predString = nodeToString(make_ands_explicit(indexInfo->ii_Predicate));
		predDatum = CStringGetTextDatum(predString);
		pfree(predString);
	}
	else
		predDatum = (Datum) 0;

	/*
	 * open the system catalog index relation
	 */
	pg_index = table_open(IndexRelationId, RowExclusiveLock);

	/*
	 * Build a pg_index tuple
	 */
	MemSet(nulls, false, sizeof(nulls));

	values[Anum_pg_index_indexrelid - 1] = ObjectIdGetDatum(indexoid);
	values[Anum_pg_index_indrelid - 1] = ObjectIdGetDatum(heapoid);
	values[Anum_pg_index_indnatts - 1] = Int16GetDatum(indexInfo->ii_NumIndexAttrs);
	values[Anum_pg_index_indnkeyatts - 1] = Int16GetDatum(indexInfo->ii_NumIndexKeyAttrs);
	values[Anum_pg_index_indisunique - 1] = BoolGetDatum(indexInfo->ii_Unique);
	values[Anum_pg_index_indisprimary - 1] = BoolGetDatum(primary);
	values[Anum_pg_index_indisexclusion - 1] = BoolGetDatum(isexclusion);
	values[Anum_pg_index_indimmediate - 1] = BoolGetDatum(immediate);
	values[Anum_pg_index_indisclustered - 1] = BoolGetDatum(false);
	values[Anum_pg_index_indisvalid - 1] = BoolGetDatum(isvalid);
	values[Anum_pg_index_indcheckxmin - 1] = BoolGetDatum(false);
	values[Anum_pg_index_indisready - 1] = BoolGetDatum(isready);
	values[Anum_pg_index_indislive - 1] = BoolGetDatum(true);
	values[Anum_pg_index_indisreplident - 1] = BoolGetDatum(false);
	values[Anum_pg_index_indkey - 1] = PointerGetDatum(indkey);
	values[Anum_pg_index_indcollation - 1] = PointerGetDatum(indcollation);
	values[Anum_pg_index_indclass - 1] = PointerGetDatum(indclass);
	values[Anum_pg_index_indoption - 1] = PointerGetDatum(indoption);
	values[Anum_pg_index_indexprs - 1] = exprsDatum;
	if (exprsDatum == (Datum) 0)
		nulls[Anum_pg_index_indexprs - 1] = true;
	values[Anum_pg_index_indpred - 1] = predDatum;
	if (predDatum == (Datum) 0)
		nulls[Anum_pg_index_indpred - 1] = true;

	tuple = heap_form_tuple(RelationGetDescr(pg_index), values, nulls);

	/*
	 * insert the tuple into the pg_index catalog
	 */
	CatalogTupleInsert(pg_index, tuple);

	/*
	 * close the relation and free the tuple
	 */
	table_close(pg_index, RowExclusiveLock);
	heap_freetuple(tuple);
}
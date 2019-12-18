#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_4__ {scalar_t__ objectSubId; void* objectId; void* classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* RegProcedure ;
typedef  void* Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_pg_range_rngcanonical ; 
 int Anum_pg_range_rngcollation ; 
 int Anum_pg_range_rngsubdiff ; 
 int Anum_pg_range_rngsubopc ; 
 int Anum_pg_range_rngsubtype ; 
 int Anum_pg_range_rngtypid ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* CollationRelationId ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int Natts_pg_range ; 
 int /*<<< orphan*/  ObjectIdGetDatum (void*) ; 
 scalar_t__ OidIsValid (void*) ; 
 void* OperatorClassRelationId ; 
 void* ProcedureRelationId ; 
 int /*<<< orphan*/  RangeRelationId ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 void* TypeRelationId ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RangeCreate(Oid rangeTypeOid, Oid rangeSubType, Oid rangeCollation,
			Oid rangeSubOpclass, RegProcedure rangeCanonical,
			RegProcedure rangeSubDiff)
{
	Relation	pg_range;
	Datum		values[Natts_pg_range];
	bool		nulls[Natts_pg_range];
	HeapTuple	tup;
	ObjectAddress myself;
	ObjectAddress referenced;

	pg_range = table_open(RangeRelationId, RowExclusiveLock);

	memset(nulls, 0, sizeof(nulls));

	values[Anum_pg_range_rngtypid - 1] = ObjectIdGetDatum(rangeTypeOid);
	values[Anum_pg_range_rngsubtype - 1] = ObjectIdGetDatum(rangeSubType);
	values[Anum_pg_range_rngcollation - 1] = ObjectIdGetDatum(rangeCollation);
	values[Anum_pg_range_rngsubopc - 1] = ObjectIdGetDatum(rangeSubOpclass);
	values[Anum_pg_range_rngcanonical - 1] = ObjectIdGetDatum(rangeCanonical);
	values[Anum_pg_range_rngsubdiff - 1] = ObjectIdGetDatum(rangeSubDiff);

	tup = heap_form_tuple(RelationGetDescr(pg_range), values, nulls);

	CatalogTupleInsert(pg_range, tup);
	heap_freetuple(tup);

	/* record type's dependencies on range-related items */

	myself.classId = TypeRelationId;
	myself.objectId = rangeTypeOid;
	myself.objectSubId = 0;

	referenced.classId = TypeRelationId;
	referenced.objectId = rangeSubType;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	referenced.classId = OperatorClassRelationId;
	referenced.objectId = rangeSubOpclass;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	if (OidIsValid(rangeCollation))
	{
		referenced.classId = CollationRelationId;
		referenced.objectId = rangeCollation;
		referenced.objectSubId = 0;
		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
	}

	if (OidIsValid(rangeCanonical))
	{
		referenced.classId = ProcedureRelationId;
		referenced.objectId = rangeCanonical;
		referenced.objectSubId = 0;
		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
	}

	if (OidIsValid(rangeSubDiff))
	{
		referenced.classId = ProcedureRelationId;
		referenced.objectId = rangeSubDiff;
		referenced.objectSubId = 0;
		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
	}

	table_close(pg_range, RowExclusiveLock);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  replace ;
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int Datum ;
typedef  int /*<<< orphan*/  CatalogIndexState ;

/* Variables and functions */
 int Anum_pg_shdepend_dbid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogCloseIndexes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogOpenIndexes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleInsertWithInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int Natts_pg_shdepend ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SharedDependDependerIndexId ; 
 int /*<<< orphan*/  SharedDependRelationId ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_modify_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
copyTemplateDependencies(Oid templateDbId, Oid newDbId)
{
	Relation	sdepRel;
	TupleDesc	sdepDesc;
	ScanKeyData key[1];
	SysScanDesc scan;
	HeapTuple	tup;
	CatalogIndexState indstate;
	Datum		values[Natts_pg_shdepend];
	bool		nulls[Natts_pg_shdepend];
	bool		replace[Natts_pg_shdepend];

	sdepRel = table_open(SharedDependRelationId, RowExclusiveLock);
	sdepDesc = RelationGetDescr(sdepRel);

	indstate = CatalogOpenIndexes(sdepRel);

	/* Scan all entries with dbid = templateDbId */
	ScanKeyInit(&key[0],
				Anum_pg_shdepend_dbid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(templateDbId));

	scan = systable_beginscan(sdepRel, SharedDependDependerIndexId, true,
							  NULL, 1, key);

	/* Set up to copy the tuples except for inserting newDbId */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));
	memset(replace, false, sizeof(replace));

	replace[Anum_pg_shdepend_dbid - 1] = true;
	values[Anum_pg_shdepend_dbid - 1] = ObjectIdGetDatum(newDbId);

	/*
	 * Copy the entries of the original database, changing the database Id to
	 * that of the new database.  Note that because we are not copying rows
	 * with dbId == 0 (ie, rows describing dependent shared objects) we won't
	 * copy the ownership dependency of the template database itself; this is
	 * what we want.
	 */
	while (HeapTupleIsValid(tup = systable_getnext(scan)))
	{
		HeapTuple	newtup;

		newtup = heap_modify_tuple(tup, sdepDesc, values, nulls, replace);
		CatalogTupleInsertWithInfo(sdepRel, newtup, indstate);

		heap_freetuple(newtup);
	}

	systable_endscan(scan);

	CatalogCloseIndexes(indstate);
	table_close(sdepRel, RowExclusiveLock);
}
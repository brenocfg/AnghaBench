#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_9__ {TYPE_1__* rd_rel; } ;
struct TYPE_8__ {int reltoastrelid; int /*<<< orphan*/  relam; int /*<<< orphan*/  relowner; } ;
typedef  TYPE_2__* Relation ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  NewHeapName ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_class_reloptions ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int InvalidOid ; 
 int LookupCreationNamespace (char*) ; 
 int NAMEDATALEN ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  NewHeapCreateToastTable (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ONCOMMIT_NOOP ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int) ; 
 scalar_t__ OidIsValid (int) ; 
 int /*<<< orphan*/  RELKIND_RELATION ; 
 int /*<<< orphan*/  RELOID ; 
 char RELPERSISTENCE_TEMP ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_2__*) ; 
 int RelationGetNamespace (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationIsMapped (TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int heap_create_with_catalog (char*,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int,int /*<<< orphan*/ ) ; 

Oid
make_new_heap(Oid OIDOldHeap, Oid NewTableSpace, char relpersistence,
			  LOCKMODE lockmode)
{
	TupleDesc	OldHeapDesc;
	char		NewHeapName[NAMEDATALEN];
	Oid			OIDNewHeap;
	Oid			toastid;
	Relation	OldHeap;
	HeapTuple	tuple;
	Datum		reloptions;
	bool		isNull;
	Oid			namespaceid;

	OldHeap = table_open(OIDOldHeap, lockmode);
	OldHeapDesc = RelationGetDescr(OldHeap);

	/*
	 * Note that the NewHeap will not receive any of the defaults or
	 * constraints associated with the OldHeap; we don't need 'em, and there's
	 * no reason to spend cycles inserting them into the catalogs only to
	 * delete them.
	 */

	/*
	 * But we do want to use reloptions of the old heap for new heap.
	 */
	tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(OIDOldHeap));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for relation %u", OIDOldHeap);
	reloptions = SysCacheGetAttr(RELOID, tuple, Anum_pg_class_reloptions,
								 &isNull);
	if (isNull)
		reloptions = (Datum) 0;

	if (relpersistence == RELPERSISTENCE_TEMP)
		namespaceid = LookupCreationNamespace("pg_temp");
	else
		namespaceid = RelationGetNamespace(OldHeap);

	/*
	 * Create the new heap, using a temporary name in the same namespace as
	 * the existing table.  NOTE: there is some risk of collision with user
	 * relnames.  Working around this seems more trouble than it's worth; in
	 * particular, we can't create the new heap in a different namespace from
	 * the old, or we will have problems with the TEMP status of temp tables.
	 *
	 * Note: the new heap is not a shared relation, even if we are rebuilding
	 * a shared rel.  However, we do make the new heap mapped if the source is
	 * mapped.  This simplifies swap_relation_files, and is absolutely
	 * necessary for rebuilding pg_class, for reasons explained there.
	 */
	snprintf(NewHeapName, sizeof(NewHeapName), "pg_temp_%u", OIDOldHeap);

	OIDNewHeap = heap_create_with_catalog(NewHeapName,
										  namespaceid,
										  NewTableSpace,
										  InvalidOid,
										  InvalidOid,
										  InvalidOid,
										  OldHeap->rd_rel->relowner,
										  OldHeap->rd_rel->relam,
										  OldHeapDesc,
										  NIL,
										  RELKIND_RELATION,
										  relpersistence,
										  false,
										  RelationIsMapped(OldHeap),
										  ONCOMMIT_NOOP,
										  reloptions,
										  false,
										  true,
										  true,
										  OIDOldHeap,
										  NULL);
	Assert(OIDNewHeap != InvalidOid);

	ReleaseSysCache(tuple);

	/*
	 * Advance command counter so that the newly-created relation's catalog
	 * tuples will be visible to table_open.
	 */
	CommandCounterIncrement();

	/*
	 * If necessary, create a TOAST table for the new relation.
	 *
	 * If the relation doesn't have a TOAST table already, we can't need one
	 * for the new relation.  The other way around is possible though: if some
	 * wide columns have been dropped, NewHeapCreateToastTable can decide that
	 * no TOAST table is needed for the new table.
	 *
	 * Note that NewHeapCreateToastTable ends with CommandCounterIncrement, so
	 * that the TOAST table will be visible for insertion.
	 */
	toastid = OldHeap->rd_rel->reltoastrelid;
	if (OidIsValid(toastid))
	{
		/* keep the existing toast table's reloptions, if any */
		tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(toastid));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for relation %u", toastid);
		reloptions = SysCacheGetAttr(RELOID, tuple, Anum_pg_class_reloptions,
									 &isNull);
		if (isNull)
			reloptions = (Datum) 0;

		NewHeapCreateToastTable(OIDNewHeap, reloptions, lockmode);

		ReleaseSysCache(tuple);
	}

	table_close(OldHeap, NoLock);

	return OIDNewHeap;
}
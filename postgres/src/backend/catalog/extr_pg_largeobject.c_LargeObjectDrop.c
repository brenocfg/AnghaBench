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
struct TYPE_4__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_largeobject_loid ; 
 int /*<<< orphan*/  Anum_pg_largeobject_metadata_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  LargeObjectLOidPNIndexId ; 
 int /*<<< orphan*/  LargeObjectMetadataOidIndexId ; 
 int /*<<< orphan*/  LargeObjectMetadataRelationId ; 
 int /*<<< orphan*/  LargeObjectRelationId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
LargeObjectDrop(Oid loid)
{
	Relation	pg_lo_meta;
	Relation	pg_largeobject;
	ScanKeyData skey[1];
	SysScanDesc scan;
	HeapTuple	tuple;

	pg_lo_meta = table_open(LargeObjectMetadataRelationId,
							RowExclusiveLock);

	pg_largeobject = table_open(LargeObjectRelationId,
								RowExclusiveLock);

	/*
	 * Delete an entry from pg_largeobject_metadata
	 */
	ScanKeyInit(&skey[0],
				Anum_pg_largeobject_metadata_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(loid));

	scan = systable_beginscan(pg_lo_meta,
							  LargeObjectMetadataOidIndexId, true,
							  NULL, 1, skey);

	tuple = systable_getnext(scan);
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("large object %u does not exist", loid)));

	CatalogTupleDelete(pg_lo_meta, &tuple->t_self);

	systable_endscan(scan);

	/*
	 * Delete all the associated entries from pg_largeobject
	 */
	ScanKeyInit(&skey[0],
				Anum_pg_largeobject_loid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(loid));

	scan = systable_beginscan(pg_largeobject,
							  LargeObjectLOidPNIndexId, true,
							  NULL, 1, skey);
	while (HeapTupleIsValid(tuple = systable_getnext(scan)))
	{
		CatalogTupleDelete(pg_largeobject, &tuple->t_self);
	}

	systable_endscan(scan);

	table_close(pg_largeobject, RowExclusiveLock);

	table_close(pg_lo_meta, RowExclusiveLock);
}
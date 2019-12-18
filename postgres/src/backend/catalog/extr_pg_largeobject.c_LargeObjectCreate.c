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
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int Anum_pg_largeobject_metadata_lomacl ; 
 int Anum_pg_largeobject_metadata_lomowner ; 
 int Anum_pg_largeobject_metadata_oid ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetNewOidWithIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  LargeObjectMetadataOidIndexId ; 
 int /*<<< orphan*/  LargeObjectMetadataRelationId ; 
 int Natts_pg_largeobject_metadata ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Oid
LargeObjectCreate(Oid loid)
{
	Relation	pg_lo_meta;
	HeapTuple	ntup;
	Oid			loid_new;
	Datum		values[Natts_pg_largeobject_metadata];
	bool		nulls[Natts_pg_largeobject_metadata];

	pg_lo_meta = table_open(LargeObjectMetadataRelationId,
							RowExclusiveLock);

	/*
	 * Insert metadata of the largeobject
	 */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));

	if (OidIsValid(loid))
		loid_new = loid;
	else
		loid_new = GetNewOidWithIndex(pg_lo_meta,
									  LargeObjectMetadataOidIndexId,
									  Anum_pg_largeobject_metadata_oid);

	values[Anum_pg_largeobject_metadata_oid - 1] = ObjectIdGetDatum(loid_new);
	values[Anum_pg_largeobject_metadata_lomowner - 1]
		= ObjectIdGetDatum(GetUserId());
	nulls[Anum_pg_largeobject_metadata_lomacl - 1] = true;

	ntup = heap_form_tuple(RelationGetDescr(pg_lo_meta),
						   values, nulls);

	CatalogTupleInsert(pg_lo_meta, ntup);

	heap_freetuple(ntup);

	table_close(pg_lo_meta, RowExclusiveLock);

	return loid_new;
}
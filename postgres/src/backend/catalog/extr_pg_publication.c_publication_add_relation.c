#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ Publication ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int Datum ;

/* Variables and functions */
 int Anum_pg_publication_rel_oid ; 
 int Anum_pg_publication_rel_prpubid ; 
 int Anum_pg_publication_rel_prrelid ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPENDENCY_AUTO ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetNewOidWithIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* GetPublication (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidObjectAddress ; 
 int Natts_pg_publication_rel ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUBLICATIONRELMAP ; 
 int /*<<< orphan*/  PublicationRelObjectIndexId ; 
 int /*<<< orphan*/  PublicationRelRelationId ; 
 int /*<<< orphan*/  PublicationRelationId ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 scalar_t__ SearchSysCacheExists2 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  check_publication_add_relation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  recordDependencyOn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
publication_add_relation(Oid pubid, Relation targetrel,
						 bool if_not_exists)
{
	Relation	rel;
	HeapTuple	tup;
	Datum		values[Natts_pg_publication_rel];
	bool		nulls[Natts_pg_publication_rel];
	Oid			relid = RelationGetRelid(targetrel);
	Oid			prrelid;
	Publication *pub = GetPublication(pubid);
	ObjectAddress myself,
				referenced;

	rel = table_open(PublicationRelRelationId, RowExclusiveLock);

	/*
	 * Check for duplicates. Note that this does not really prevent
	 * duplicates, it's here just to provide nicer error message in common
	 * case. The real protection is the unique key on the catalog.
	 */
	if (SearchSysCacheExists2(PUBLICATIONRELMAP, ObjectIdGetDatum(relid),
							  ObjectIdGetDatum(pubid)))
	{
		table_close(rel, RowExclusiveLock);

		if (if_not_exists)
			return InvalidObjectAddress;

		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("relation \"%s\" is already member of publication \"%s\"",
						RelationGetRelationName(targetrel), pub->name)));
	}

	check_publication_add_relation(targetrel);

	/* Form a tuple. */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));

	prrelid = GetNewOidWithIndex(rel, PublicationRelObjectIndexId,
								 Anum_pg_publication_rel_oid);
	values[Anum_pg_publication_rel_oid - 1] = ObjectIdGetDatum(prrelid);
	values[Anum_pg_publication_rel_prpubid - 1] =
		ObjectIdGetDatum(pubid);
	values[Anum_pg_publication_rel_prrelid - 1] =
		ObjectIdGetDatum(relid);

	tup = heap_form_tuple(RelationGetDescr(rel), values, nulls);

	/* Insert tuple into catalog. */
	CatalogTupleInsert(rel, tup);
	heap_freetuple(tup);

	ObjectAddressSet(myself, PublicationRelRelationId, prrelid);

	/* Add dependency on the publication */
	ObjectAddressSet(referenced, PublicationRelationId, pubid);
	recordDependencyOn(&myself, &referenced, DEPENDENCY_AUTO);

	/* Add dependency on the relation */
	ObjectAddressSet(referenced, RelationRelationId, relid);
	recordDependencyOn(&myself, &referenced, DEPENDENCY_AUTO);

	/* Close the table. */
	table_close(rel, RowExclusiveLock);

	/* Invalidate relcache so that publication info is rebuilt. */
	CacheInvalidateRelcache(targetrel);

	return myself;
}
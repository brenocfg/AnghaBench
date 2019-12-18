#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nulls ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {char const* objectId; scalar_t__ objectSubId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  char const* Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_pg_collation_collcollate ; 
 int Anum_pg_collation_collctype ; 
 int Anum_pg_collation_collencoding ; 
 int Anum_pg_collation_collisdeterministic ; 
 int Anum_pg_collation_collname ; 
 int Anum_pg_collation_collnamespace ; 
 int Anum_pg_collation_collowner ; 
 int Anum_pg_collation_collprovider ; 
 int Anum_pg_collation_collversion ; 
 int Anum_pg_collation_oid ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AssertArg (char const*) ; 
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int /*<<< orphan*/  COLLNAMEENCNSP ; 
 int /*<<< orphan*/  CStringGetTextDatum (char const*) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CharGetDatum (char) ; 
 int /*<<< orphan*/  CollationOidIndexId ; 
 int /*<<< orphan*/  CollationRelationId ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int GetDatabaseEncoding () ; 
 char* GetNewOidWithIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 char const* InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int Natts_pg_collation ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (char const*) ; 
 int /*<<< orphan*/  OidIsValid (char const*) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 scalar_t__ SearchSysCacheExists3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareRowExclusiveLock ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pg_encoding_to_char (int) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnCurrentExtension (TYPE_1__*,int) ; 
 int /*<<< orphan*/  recordDependencyOnOwner (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Oid
CollationCreate(const char *collname, Oid collnamespace,
				Oid collowner,
				char collprovider,
				bool collisdeterministic,
				int32 collencoding,
				const char *collcollate, const char *collctype,
				const char *collversion,
				bool if_not_exists,
				bool quiet)
{
	Relation	rel;
	TupleDesc	tupDesc;
	HeapTuple	tup;
	Datum		values[Natts_pg_collation];
	bool		nulls[Natts_pg_collation];
	NameData	name_name,
				name_collate,
				name_ctype;
	Oid			oid;
	ObjectAddress myself,
				referenced;

	AssertArg(collname);
	AssertArg(collnamespace);
	AssertArg(collowner);
	AssertArg(collcollate);
	AssertArg(collctype);

	/*
	 * Make sure there is no existing collation of same name & encoding.
	 *
	 * This would be caught by the unique index anyway; we're just giving a
	 * friendlier error message.  The unique index provides a backstop against
	 * race conditions.
	 */
	if (SearchSysCacheExists3(COLLNAMEENCNSP,
							  PointerGetDatum(collname),
							  Int32GetDatum(collencoding),
							  ObjectIdGetDatum(collnamespace)))
	{
		if (quiet)
			return InvalidOid;
		else if (if_not_exists)
		{
			ereport(NOTICE,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 collencoding == -1
					 ? errmsg("collation \"%s\" already exists, skipping",
							  collname)
					 : errmsg("collation \"%s\" for encoding \"%s\" already exists, skipping",
							  collname, pg_encoding_to_char(collencoding))));
			return InvalidOid;
		}
		else
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 collencoding == -1
					 ? errmsg("collation \"%s\" already exists",
							  collname)
					 : errmsg("collation \"%s\" for encoding \"%s\" already exists",
							  collname, pg_encoding_to_char(collencoding))));
	}

	/* open pg_collation; see below about the lock level */
	rel = table_open(CollationRelationId, ShareRowExclusiveLock);

	/*
	 * Also forbid a specific-encoding collation shadowing an any-encoding
	 * collation, or an any-encoding collation being shadowed (see
	 * get_collation_name()).  This test is not backed up by the unique index,
	 * so we take a ShareRowExclusiveLock earlier, to protect against
	 * concurrent changes fooling this check.
	 */
	if ((collencoding == -1 &&
		 SearchSysCacheExists3(COLLNAMEENCNSP,
							   PointerGetDatum(collname),
							   Int32GetDatum(GetDatabaseEncoding()),
							   ObjectIdGetDatum(collnamespace))) ||
		(collencoding != -1 &&
		 SearchSysCacheExists3(COLLNAMEENCNSP,
							   PointerGetDatum(collname),
							   Int32GetDatum(-1),
							   ObjectIdGetDatum(collnamespace))))
	{
		if (quiet)
		{
			table_close(rel, NoLock);
			return InvalidOid;
		}
		else if (if_not_exists)
		{
			table_close(rel, NoLock);
			ereport(NOTICE,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("collation \"%s\" already exists, skipping",
							collname)));
			return InvalidOid;
		}
		else
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("collation \"%s\" already exists",
							collname)));
	}

	tupDesc = RelationGetDescr(rel);

	/* form a tuple */
	memset(nulls, 0, sizeof(nulls));

	namestrcpy(&name_name, collname);
	oid = GetNewOidWithIndex(rel, CollationOidIndexId,
							 Anum_pg_collation_oid);
	values[Anum_pg_collation_oid - 1] = ObjectIdGetDatum(oid);
	values[Anum_pg_collation_collname - 1] = NameGetDatum(&name_name);
	values[Anum_pg_collation_collnamespace - 1] = ObjectIdGetDatum(collnamespace);
	values[Anum_pg_collation_collowner - 1] = ObjectIdGetDatum(collowner);
	values[Anum_pg_collation_collprovider - 1] = CharGetDatum(collprovider);
	values[Anum_pg_collation_collisdeterministic - 1] = BoolGetDatum(collisdeterministic);
	values[Anum_pg_collation_collencoding - 1] = Int32GetDatum(collencoding);
	namestrcpy(&name_collate, collcollate);
	values[Anum_pg_collation_collcollate - 1] = NameGetDatum(&name_collate);
	namestrcpy(&name_ctype, collctype);
	values[Anum_pg_collation_collctype - 1] = NameGetDatum(&name_ctype);
	if (collversion)
		values[Anum_pg_collation_collversion - 1] = CStringGetTextDatum(collversion);
	else
		nulls[Anum_pg_collation_collversion - 1] = true;

	tup = heap_form_tuple(tupDesc, values, nulls);

	/* insert a new tuple */
	CatalogTupleInsert(rel, tup);
	Assert(OidIsValid(oid));

	/* set up dependencies for the new collation */
	myself.classId = CollationRelationId;
	myself.objectId = oid;
	myself.objectSubId = 0;

	/* create dependency on namespace */
	referenced.classId = NamespaceRelationId;
	referenced.objectId = collnamespace;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	/* create dependency on owner */
	recordDependencyOnOwner(CollationRelationId, oid, collowner);

	/* dependency on extension */
	recordDependencyOnCurrentExtension(&myself, false);

	/* Post creation hook for new collation */
	InvokeObjectPostCreateHook(CollationRelationId, oid, 0);

	heap_freetuple(tup);
	table_close(rel, NoLock);

	return oid;
}
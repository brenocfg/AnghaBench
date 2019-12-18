#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  replaces ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_15__ {int /*<<< orphan*/  collname; } ;
struct TYPE_14__ {int /*<<< orphan*/  collcollate; int /*<<< orphan*/  collprovider; } ;
struct TYPE_13__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_collation ;
typedef  int Datum ;
typedef  TYPE_3__ AlterCollationStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int Anum_pg_collation_collversion ; 
 int /*<<< orphan*/  COLLOID ; 
 int CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CollationRelationId ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int Natts_pg_collation ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OBJECT_COLLATION ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SysCacheGetAttr (int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 char* TextDatumGetCString (int) ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* get_collation_actual_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_collation_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  pg_collation_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
AlterCollation(AlterCollationStmt *stmt)
{
	Relation	rel;
	Oid			collOid;
	HeapTuple	tup;
	Form_pg_collation collForm;
	Datum		collversion;
	bool		isnull;
	char	   *oldversion;
	char	   *newversion;
	ObjectAddress address;

	rel = table_open(CollationRelationId, RowExclusiveLock);
	collOid = get_collation_oid(stmt->collname, false);

	if (!pg_collation_ownercheck(collOid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_COLLATION,
					   NameListToString(stmt->collname));

	tup = SearchSysCacheCopy1(COLLOID, ObjectIdGetDatum(collOid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for collation %u", collOid);

	collForm = (Form_pg_collation) GETSTRUCT(tup);
	collversion = SysCacheGetAttr(COLLOID, tup, Anum_pg_collation_collversion,
								  &isnull);
	oldversion = isnull ? NULL : TextDatumGetCString(collversion);

	newversion = get_collation_actual_version(collForm->collprovider, NameStr(collForm->collcollate));

	/* cannot change from NULL to non-NULL or vice versa */
	if ((!oldversion && newversion) || (oldversion && !newversion))
		elog(ERROR, "invalid collation version change");
	else if (oldversion && newversion && strcmp(newversion, oldversion) != 0)
	{
		bool		nulls[Natts_pg_collation];
		bool		replaces[Natts_pg_collation];
		Datum		values[Natts_pg_collation];

		ereport(NOTICE,
				(errmsg("changing version from %s to %s",
						oldversion, newversion)));

		memset(values, 0, sizeof(values));
		memset(nulls, false, sizeof(nulls));
		memset(replaces, false, sizeof(replaces));

		values[Anum_pg_collation_collversion - 1] = CStringGetTextDatum(newversion);
		replaces[Anum_pg_collation_collversion - 1] = true;

		tup = heap_modify_tuple(tup, RelationGetDescr(rel),
								values, nulls, replaces);
	}
	else
		ereport(NOTICE,
				(errmsg("version has not changed")));

	CatalogTupleUpdate(rel, &tup->t_self, tup);

	InvokeObjectPostAlterHook(CollationRelationId, collOid, 0);

	ObjectAddressSet(address, CollationRelationId, collOid);

	heap_freetuple(tup);
	table_close(rel, NoLock);

	return address;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  replace ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_9__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  int Datum ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int Anum_pg_init_privs_classoid ; 
 int Anum_pg_init_privs_initprivs ; 
 int Anum_pg_init_privs_objoid ; 
 int Anum_pg_init_privs_objsubid ; 
 int Anum_pg_init_privs_privtype ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int CharGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  INITPRIVS_EXTENSION ; 
 int /*<<< orphan*/  InitPrivsObjIndexId ; 
 int /*<<< orphan*/  InitPrivsRelationId ; 
 int Int32GetDatum (int) ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 int Natts_pg_init_privs ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
recordExtensionInitPrivWorker(Oid objoid, Oid classoid, int objsubid, Acl *new_acl)
{
	Relation	relation;
	ScanKeyData key[3];
	SysScanDesc scan;
	HeapTuple	tuple;
	HeapTuple	oldtuple;

	relation = table_open(InitPrivsRelationId, RowExclusiveLock);

	ScanKeyInit(&key[0],
				Anum_pg_init_privs_objoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(objoid));
	ScanKeyInit(&key[1],
				Anum_pg_init_privs_classoid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(classoid));
	ScanKeyInit(&key[2],
				Anum_pg_init_privs_objsubid,
				BTEqualStrategyNumber, F_INT4EQ,
				Int32GetDatum(objsubid));

	scan = systable_beginscan(relation, InitPrivsObjIndexId, true,
							  NULL, 3, key);

	/* There should exist only one entry or none. */
	oldtuple = systable_getnext(scan);

	/* If we find an entry, update it with the latest ACL. */
	if (HeapTupleIsValid(oldtuple))
	{
		Datum		values[Natts_pg_init_privs];
		bool		nulls[Natts_pg_init_privs];
		bool		replace[Natts_pg_init_privs];

		/* If we have a new ACL to set, then update the row with it. */
		if (new_acl)
		{
			MemSet(values, 0, sizeof(values));
			MemSet(nulls, false, sizeof(nulls));
			MemSet(replace, false, sizeof(replace));

			values[Anum_pg_init_privs_initprivs - 1] = PointerGetDatum(new_acl);
			replace[Anum_pg_init_privs_initprivs - 1] = true;

			oldtuple = heap_modify_tuple(oldtuple, RelationGetDescr(relation),
										 values, nulls, replace);

			CatalogTupleUpdate(relation, &oldtuple->t_self, oldtuple);
		}
		else
		{
			/* new_acl is NULL, so delete the entry we found. */
			CatalogTupleDelete(relation, &oldtuple->t_self);
		}
	}
	else
	{
		Datum		values[Natts_pg_init_privs];
		bool		nulls[Natts_pg_init_privs];

		/*
		 * Only add a new entry if the new ACL is non-NULL.
		 *
		 * If we are passed in a NULL ACL and no entry exists, we can just
		 * fall through and do nothing.
		 */
		if (new_acl)
		{
			/* No entry found, so add it. */
			MemSet(nulls, false, sizeof(nulls));

			values[Anum_pg_init_privs_objoid - 1] = ObjectIdGetDatum(objoid);
			values[Anum_pg_init_privs_classoid - 1] = ObjectIdGetDatum(classoid);
			values[Anum_pg_init_privs_objsubid - 1] = Int32GetDatum(objsubid);

			/* This function only handles initial privileges of extensions */
			values[Anum_pg_init_privs_privtype - 1] =
				CharGetDatum(INITPRIVS_EXTENSION);

			values[Anum_pg_init_privs_initprivs - 1] = PointerGetDatum(new_acl);

			tuple = heap_form_tuple(RelationGetDescr(relation), values, nulls);

			CatalogTupleInsert(relation, tuple);
		}
	}

	systable_endscan(scan);

	/* prevent error when processing objects multiple times */
	CommandCounterIncrement();

	table_close(relation, RowExclusiveLock);
}
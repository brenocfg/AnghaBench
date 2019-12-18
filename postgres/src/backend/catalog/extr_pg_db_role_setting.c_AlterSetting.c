#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  repl_repl ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_13__ {scalar_t__ kind; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ VariableSetStmt ;
struct TYPE_14__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__* HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int Anum_pg_db_role_setting_setconfig ; 
 int Anum_pg_db_role_setting_setdatabase ; 
 int Anum_pg_db_role_setting_setrole ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbRoleSettingDatidRolidIndexId ; 
 int /*<<< orphan*/  DbRoleSettingRelationId ; 
 char* ExtractSetVariableArgs (TYPE_1__*) ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/ * GUCArrayAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GUCArrayDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GUCArrayReset (int /*<<< orphan*/ *) ; 
 scalar_t__ HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHookArg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int Natts_pg_db_role_setting ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_RESET_ALL ; 
 TYPE_2__* heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_getattr (TYPE_2__*,int,int /*<<< orphan*/ ,int*) ; 
 TYPE_2__* heap_modify_tuple (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_2__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AlterSetting(Oid databaseid, Oid roleid, VariableSetStmt *setstmt)
{
	char	   *valuestr;
	HeapTuple	tuple;
	Relation	rel;
	ScanKeyData scankey[2];
	SysScanDesc scan;

	valuestr = ExtractSetVariableArgs(setstmt);

	/* Get the old tuple, if any. */

	rel = table_open(DbRoleSettingRelationId, RowExclusiveLock);
	ScanKeyInit(&scankey[0],
				Anum_pg_db_role_setting_setdatabase,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(databaseid));
	ScanKeyInit(&scankey[1],
				Anum_pg_db_role_setting_setrole,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(roleid));
	scan = systable_beginscan(rel, DbRoleSettingDatidRolidIndexId, true,
							  NULL, 2, scankey);
	tuple = systable_getnext(scan);

	/*
	 * There are three cases:
	 *
	 * - in RESET ALL, request GUC to reset the settings array and update the
	 * catalog if there's anything left, delete it otherwise
	 *
	 * - in other commands, if there's a tuple in pg_db_role_setting, update
	 * it; if it ends up empty, delete it
	 *
	 * - otherwise, insert a new pg_db_role_setting tuple, but only if the
	 * command is not RESET
	 */
	if (setstmt->kind == VAR_RESET_ALL)
	{
		if (HeapTupleIsValid(tuple))
		{
			ArrayType  *new = NULL;
			Datum		datum;
			bool		isnull;

			datum = heap_getattr(tuple, Anum_pg_db_role_setting_setconfig,
								 RelationGetDescr(rel), &isnull);

			if (!isnull)
				new = GUCArrayReset(DatumGetArrayTypeP(datum));

			if (new)
			{
				Datum		repl_val[Natts_pg_db_role_setting];
				bool		repl_null[Natts_pg_db_role_setting];
				bool		repl_repl[Natts_pg_db_role_setting];
				HeapTuple	newtuple;

				memset(repl_repl, false, sizeof(repl_repl));

				repl_val[Anum_pg_db_role_setting_setconfig - 1] =
					PointerGetDatum(new);
				repl_repl[Anum_pg_db_role_setting_setconfig - 1] = true;
				repl_null[Anum_pg_db_role_setting_setconfig - 1] = false;

				newtuple = heap_modify_tuple(tuple, RelationGetDescr(rel),
											 repl_val, repl_null, repl_repl);
				CatalogTupleUpdate(rel, &tuple->t_self, newtuple);
			}
			else
				CatalogTupleDelete(rel, &tuple->t_self);
		}
	}
	else if (HeapTupleIsValid(tuple))
	{
		Datum		repl_val[Natts_pg_db_role_setting];
		bool		repl_null[Natts_pg_db_role_setting];
		bool		repl_repl[Natts_pg_db_role_setting];
		HeapTuple	newtuple;
		Datum		datum;
		bool		isnull;
		ArrayType  *a;

		memset(repl_repl, false, sizeof(repl_repl));
		repl_repl[Anum_pg_db_role_setting_setconfig - 1] = true;
		repl_null[Anum_pg_db_role_setting_setconfig - 1] = false;

		/* Extract old value of setconfig */
		datum = heap_getattr(tuple, Anum_pg_db_role_setting_setconfig,
							 RelationGetDescr(rel), &isnull);
		a = isnull ? NULL : DatumGetArrayTypeP(datum);

		/* Update (valuestr is NULL in RESET cases) */
		if (valuestr)
			a = GUCArrayAdd(a, setstmt->name, valuestr);
		else
			a = GUCArrayDelete(a, setstmt->name);

		if (a)
		{
			repl_val[Anum_pg_db_role_setting_setconfig - 1] =
				PointerGetDatum(a);

			newtuple = heap_modify_tuple(tuple, RelationGetDescr(rel),
										 repl_val, repl_null, repl_repl);
			CatalogTupleUpdate(rel, &tuple->t_self, newtuple);
		}
		else
			CatalogTupleDelete(rel, &tuple->t_self);
	}
	else if (valuestr)
	{
		/* non-null valuestr means it's not RESET, so insert a new tuple */
		HeapTuple	newtuple;
		Datum		values[Natts_pg_db_role_setting];
		bool		nulls[Natts_pg_db_role_setting];
		ArrayType  *a;

		memset(nulls, false, sizeof(nulls));

		a = GUCArrayAdd(NULL, setstmt->name, valuestr);

		values[Anum_pg_db_role_setting_setdatabase - 1] =
			ObjectIdGetDatum(databaseid);
		values[Anum_pg_db_role_setting_setrole - 1] = ObjectIdGetDatum(roleid);
		values[Anum_pg_db_role_setting_setconfig - 1] = PointerGetDatum(a);
		newtuple = heap_form_tuple(RelationGetDescr(rel), values, nulls);

		CatalogTupleInsert(rel, newtuple);
	}

	InvokeObjectPostAlterHookArg(DbRoleSettingRelationId,
								 databaseid, 0, roleid, false);

	systable_endscan(scan);

	/* Close pg_db_role_setting, but keep lock till commit */
	table_close(rel, NoLock);
}
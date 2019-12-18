#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  repl_repl ;
typedef  int /*<<< orphan*/  repl_null ;
struct TYPE_10__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  fdwowner; int /*<<< orphan*/  fdwname; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_foreign_data_wrapper ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int Anum_pg_foreign_data_wrapper_fdwacl ; 
 int Anum_pg_foreign_data_wrapper_fdwowner ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  DatumGetAclP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ForeignDataWrapperRelationId ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int Natts_pg_foreign_data_wrapper ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * aclnewowner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  changeDependencyOnOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (TYPE_1__*,int,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  superuser () ; 
 int /*<<< orphan*/  superuser_arg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AlterForeignDataWrapperOwner_internal(Relation rel, HeapTuple tup, Oid newOwnerId)
{
	Form_pg_foreign_data_wrapper form;
	Datum		repl_val[Natts_pg_foreign_data_wrapper];
	bool		repl_null[Natts_pg_foreign_data_wrapper];
	bool		repl_repl[Natts_pg_foreign_data_wrapper];
	Acl		   *newAcl;
	Datum		aclDatum;
	bool		isNull;

	form = (Form_pg_foreign_data_wrapper) GETSTRUCT(tup);

	/* Must be a superuser to change a FDW owner */
	if (!superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied to change owner of foreign-data wrapper \"%s\"",
						NameStr(form->fdwname)),
				 errhint("Must be superuser to change owner of a foreign-data wrapper.")));

	/* New owner must also be a superuser */
	if (!superuser_arg(newOwnerId))
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied to change owner of foreign-data wrapper \"%s\"",
						NameStr(form->fdwname)),
				 errhint("The owner of a foreign-data wrapper must be a superuser.")));

	if (form->fdwowner != newOwnerId)
	{
		memset(repl_null, false, sizeof(repl_null));
		memset(repl_repl, false, sizeof(repl_repl));

		repl_repl[Anum_pg_foreign_data_wrapper_fdwowner - 1] = true;
		repl_val[Anum_pg_foreign_data_wrapper_fdwowner - 1] = ObjectIdGetDatum(newOwnerId);

		aclDatum = heap_getattr(tup,
								Anum_pg_foreign_data_wrapper_fdwacl,
								RelationGetDescr(rel),
								&isNull);
		/* Null ACLs do not require changes */
		if (!isNull)
		{
			newAcl = aclnewowner(DatumGetAclP(aclDatum),
								 form->fdwowner, newOwnerId);
			repl_repl[Anum_pg_foreign_data_wrapper_fdwacl - 1] = true;
			repl_val[Anum_pg_foreign_data_wrapper_fdwacl - 1] = PointerGetDatum(newAcl);
		}

		tup = heap_modify_tuple(tup, RelationGetDescr(rel), repl_val, repl_null,
								repl_repl);

		CatalogTupleUpdate(rel, &tup->t_self, tup);

		/* Update owner dependency reference */
		changeDependencyOnOwner(ForeignDataWrapperRelationId,
								form->oid,
								newOwnerId);
	}

	InvokeObjectPostAlterHook(ForeignDataWrapperRelationId,
							  form->oid, 0);
}
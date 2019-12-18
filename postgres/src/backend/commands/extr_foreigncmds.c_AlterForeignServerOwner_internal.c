#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  repl_repl ;
typedef  int /*<<< orphan*/  repl_null ;
struct TYPE_13__ {int /*<<< orphan*/  fdwname; } ;
struct TYPE_12__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  srvowner; int /*<<< orphan*/  srvfdw; int /*<<< orphan*/  srvname; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_foreign_server ;
typedef  TYPE_3__ ForeignDataWrapper ;
typedef  int /*<<< orphan*/  Datum ;
typedef  scalar_t__ AclResult ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 scalar_t__ ACLCHECK_NOT_OWNER ; 
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_USAGE ; 
 int Anum_pg_foreign_server_srvacl ; 
 int Anum_pg_foreign_server_srvowner ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  DatumGetAclP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ForeignServerRelationId ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 TYPE_3__* GetForeignDataWrapper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int Natts_pg_foreign_server ; 
 int /*<<< orphan*/  OBJECT_FDW ; 
 int /*<<< orphan*/  OBJECT_FOREIGN_SERVER ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * aclnewowner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  changeDependencyOnOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_is_member_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (TYPE_1__*,int,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 scalar_t__ pg_foreign_data_wrapper_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_foreign_server_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superuser () ; 

__attribute__((used)) static void
AlterForeignServerOwner_internal(Relation rel, HeapTuple tup, Oid newOwnerId)
{
	Form_pg_foreign_server form;
	Datum		repl_val[Natts_pg_foreign_server];
	bool		repl_null[Natts_pg_foreign_server];
	bool		repl_repl[Natts_pg_foreign_server];
	Acl		   *newAcl;
	Datum		aclDatum;
	bool		isNull;

	form = (Form_pg_foreign_server) GETSTRUCT(tup);

	if (form->srvowner != newOwnerId)
	{
		/* Superusers can always do it */
		if (!superuser())
		{
			Oid			srvId;
			AclResult	aclresult;

			srvId = form->oid;

			/* Must be owner */
			if (!pg_foreign_server_ownercheck(srvId, GetUserId()))
				aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_FOREIGN_SERVER,
							   NameStr(form->srvname));

			/* Must be able to become new owner */
			check_is_member_of_role(GetUserId(), newOwnerId);

			/* New owner must have USAGE privilege on foreign-data wrapper */
			aclresult = pg_foreign_data_wrapper_aclcheck(form->srvfdw, newOwnerId, ACL_USAGE);
			if (aclresult != ACLCHECK_OK)
			{
				ForeignDataWrapper *fdw = GetForeignDataWrapper(form->srvfdw);

				aclcheck_error(aclresult, OBJECT_FDW, fdw->fdwname);
			}
		}

		memset(repl_null, false, sizeof(repl_null));
		memset(repl_repl, false, sizeof(repl_repl));

		repl_repl[Anum_pg_foreign_server_srvowner - 1] = true;
		repl_val[Anum_pg_foreign_server_srvowner - 1] = ObjectIdGetDatum(newOwnerId);

		aclDatum = heap_getattr(tup,
								Anum_pg_foreign_server_srvacl,
								RelationGetDescr(rel),
								&isNull);
		/* Null ACLs do not require changes */
		if (!isNull)
		{
			newAcl = aclnewowner(DatumGetAclP(aclDatum),
								 form->srvowner, newOwnerId);
			repl_repl[Anum_pg_foreign_server_srvacl - 1] = true;
			repl_val[Anum_pg_foreign_server_srvacl - 1] = PointerGetDatum(newAcl);
		}

		tup = heap_modify_tuple(tup, RelationGetDescr(rel), repl_val, repl_null,
								repl_repl);

		CatalogTupleUpdate(rel, &tup->t_self, tup);

		/* Update owner dependency reference */
		changeDependencyOnOwner(ForeignServerRelationId, form->oid,
								newOwnerId);
	}

	InvokeObjectPostAlterHook(ForeignServerRelationId,
							  form->oid, 0);
}
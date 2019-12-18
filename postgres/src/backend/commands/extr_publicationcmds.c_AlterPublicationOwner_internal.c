#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  pubowner; int /*<<< orphan*/  pubname; scalar_t__ puballtables; } ;
struct TYPE_6__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_publication ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_NOT_OWNER ; 
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJECT_DATABASE ; 
 int /*<<< orphan*/  OBJECT_PUBLICATION ; 
 int /*<<< orphan*/  PublicationRelationId ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  changeDependencyOnOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_is_member_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_database_name (int /*<<< orphan*/ ) ; 
 scalar_t__ pg_database_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_publication_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superuser () ; 
 int /*<<< orphan*/  superuser_arg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AlterPublicationOwner_internal(Relation rel, HeapTuple tup, Oid newOwnerId)
{
	Form_pg_publication form;

	form = (Form_pg_publication) GETSTRUCT(tup);

	if (form->pubowner == newOwnerId)
		return;

	if (!superuser())
	{
		AclResult	aclresult;

		/* Must be owner */
		if (!pg_publication_ownercheck(form->oid, GetUserId()))
			aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_PUBLICATION,
						   NameStr(form->pubname));

		/* Must be able to become new owner */
		check_is_member_of_role(GetUserId(), newOwnerId);

		/* New owner must have CREATE privilege on database */
		aclresult = pg_database_aclcheck(MyDatabaseId, newOwnerId, ACL_CREATE);
		if (aclresult != ACLCHECK_OK)
			aclcheck_error(aclresult, OBJECT_DATABASE,
						   get_database_name(MyDatabaseId));

		if (form->puballtables && !superuser_arg(newOwnerId))
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("permission denied to change owner of publication \"%s\"",
							NameStr(form->pubname)),
					 errhint("The owner of a FOR ALL TABLES publication must be a superuser.")));
	}

	form->pubowner = newOwnerId;
	CatalogTupleUpdate(rel, &tup->t_self, tup);

	/* Update owner dependency reference */
	changeDependencyOnOwner(PublicationRelationId,
							form->oid,
							newOwnerId);

	InvokeObjectPostAlterHook(PublicationRelationId,
							  form->oid, 0);
}
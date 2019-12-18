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
struct TYPE_3__ {int /*<<< orphan*/  amname; int /*<<< orphan*/  opfamilyname; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_1__ CreateOpFamilyStmt ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/  CreateOpFamily (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  OBJECT_SCHEMA ; 
 int /*<<< orphan*/  QualifiedNameGetCreationNamespace (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  get_index_am_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_namespace_name (int /*<<< orphan*/ ) ; 
 scalar_t__ pg_namespace_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superuser () ; 

ObjectAddress
DefineOpFamily(CreateOpFamilyStmt *stmt)
{
	char	   *opfname;		/* name of opfamily we're creating */
	Oid			amoid,			/* our AM's oid */
				namespaceoid;	/* namespace to create opfamily in */
	AclResult	aclresult;

	/* Convert list of names to a name and namespace */
	namespaceoid = QualifiedNameGetCreationNamespace(stmt->opfamilyname,
													 &opfname);

	/* Check we have creation rights in target namespace */
	aclresult = pg_namespace_aclcheck(namespaceoid, GetUserId(), ACL_CREATE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_SCHEMA,
					   get_namespace_name(namespaceoid));

	/* Get access method OID, throwing an error if it doesn't exist. */
	amoid = get_index_am_oid(stmt->amname, false);

	/* XXX Should we make any privilege check against the AM? */

	/*
	 * Currently, we require superuser privileges to create an opfamily. See
	 * comments in DefineOpClass.
	 */
	if (!superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("must be superuser to create an operator family")));

	/* Insert pg_opfamily catalog entry */
	return CreateOpFamily(stmt->amname, opfname, namespaceoid, amoid);
}
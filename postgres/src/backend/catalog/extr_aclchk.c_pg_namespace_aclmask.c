#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  nspowner; } ;
typedef  scalar_t__ Pointer ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_namespace ;
typedef  scalar_t__ Datum ;
typedef  int AclMode ;
typedef  int /*<<< orphan*/  AclMaskHow ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int ACL_ALL_RIGHTS_SCHEMA ; 
 int /*<<< orphan*/  ACL_CREATE_TEMP ; 
 int ACL_USAGE ; 
 int /*<<< orphan*/  Anum_pg_namespace_nspacl ; 
 int /*<<< orphan*/ * DatumGetAclP (scalar_t__) ; 
 scalar_t__ DatumGetPointer (scalar_t__) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_SCHEMA ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  NAMESPACEOID ; 
 int /*<<< orphan*/  OBJECT_SCHEMA ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * acldefault (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int aclmask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isTempNamespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 scalar_t__ pg_database_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ superuser_arg (int /*<<< orphan*/ ) ; 

AclMode
pg_namespace_aclmask(Oid nsp_oid, Oid roleid,
					 AclMode mask, AclMaskHow how)
{
	AclMode		result;
	HeapTuple	tuple;
	Datum		aclDatum;
	bool		isNull;
	Acl		   *acl;
	Oid			ownerId;

	/* Superusers bypass all permission checking. */
	if (superuser_arg(roleid))
		return mask;

	/*
	 * If we have been assigned this namespace as a temp namespace, check to
	 * make sure we have CREATE TEMP permission on the database, and if so act
	 * as though we have all standard (but not GRANT OPTION) permissions on
	 * the namespace.  If we don't have CREATE TEMP, act as though we have
	 * only USAGE (and not CREATE) rights.
	 *
	 * This may seem redundant given the check in InitTempTableNamespace, but
	 * it really isn't since current user ID may have changed since then. The
	 * upshot of this behavior is that a SECURITY DEFINER function can create
	 * temp tables that can then be accessed (if permission is granted) by
	 * code in the same session that doesn't have permissions to create temp
	 * tables.
	 *
	 * XXX Would it be safe to ereport a special error message as
	 * InitTempTableNamespace does?  Returning zero here means we'll get a
	 * generic "permission denied for schema pg_temp_N" message, which is not
	 * remarkably user-friendly.
	 */
	if (isTempNamespace(nsp_oid))
	{
		if (pg_database_aclcheck(MyDatabaseId, roleid,
								 ACL_CREATE_TEMP) == ACLCHECK_OK)
			return mask & ACL_ALL_RIGHTS_SCHEMA;
		else
			return mask & ACL_USAGE;
	}

	/*
	 * Get the schema's ACL from pg_namespace
	 */
	tuple = SearchSysCache1(NAMESPACEOID, ObjectIdGetDatum(nsp_oid));
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_SCHEMA),
				 errmsg("schema with OID %u does not exist", nsp_oid)));

	ownerId = ((Form_pg_namespace) GETSTRUCT(tuple))->nspowner;

	aclDatum = SysCacheGetAttr(NAMESPACEOID, tuple, Anum_pg_namespace_nspacl,
							   &isNull);
	if (isNull)
	{
		/* No ACL, so build default ACL */
		acl = acldefault(OBJECT_SCHEMA, ownerId);
		aclDatum = (Datum) 0;
	}
	else
	{
		/* detoast ACL if necessary */
		acl = DatumGetAclP(aclDatum);
	}

	result = aclmask(acl, roleid, ownerId, mask, how);

	/* if we have a detoasted copy, free it */
	if (acl && (Pointer) acl != DatumGetPointer(aclDatum))
		pfree(acl);

	ReleaseSysCache(tuple);

	return result;
}
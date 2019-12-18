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
struct TYPE_2__ {int typlen; int /*<<< orphan*/  typowner; int /*<<< orphan*/  typelem; } ;
typedef  scalar_t__ Pointer ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_type ;
typedef  scalar_t__ Datum ;
typedef  int /*<<< orphan*/  AclMode ;
typedef  int /*<<< orphan*/  AclMaskHow ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_type_typacl ; 
 int /*<<< orphan*/ * DatumGetAclP (scalar_t__) ; 
 scalar_t__ DatumGetPointer (scalar_t__) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJECT_TYPE ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TYPEOID ; 
 int /*<<< orphan*/ * acldefault (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclmask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 scalar_t__ superuser_arg (int /*<<< orphan*/ ) ; 

AclMode
pg_type_aclmask(Oid type_oid, Oid roleid, AclMode mask, AclMaskHow how)
{
	AclMode		result;
	HeapTuple	tuple;
	Datum		aclDatum;
	bool		isNull;
	Acl		   *acl;
	Oid			ownerId;

	Form_pg_type typeForm;

	/* Bypass permission checks for superusers */
	if (superuser_arg(roleid))
		return mask;

	/*
	 * Must get the type's tuple from pg_type
	 */
	tuple = SearchSysCache1(TYPEOID, ObjectIdGetDatum(type_oid));
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("type with OID %u does not exist",
						type_oid)));
	typeForm = (Form_pg_type) GETSTRUCT(tuple);

	/*
	 * "True" array types don't manage permissions of their own; consult the
	 * element type instead.
	 */
	if (OidIsValid(typeForm->typelem) && typeForm->typlen == -1)
	{
		Oid			elttype_oid = typeForm->typelem;

		ReleaseSysCache(tuple);

		tuple = SearchSysCache1(TYPEOID, ObjectIdGetDatum(elttype_oid));
		/* this case is not a user-facing error, so elog not ereport */
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for type %u", elttype_oid);
		typeForm = (Form_pg_type) GETSTRUCT(tuple);
	}

	/*
	 * Now get the type's owner and ACL from the tuple
	 */
	ownerId = typeForm->typowner;

	aclDatum = SysCacheGetAttr(TYPEOID, tuple,
							   Anum_pg_type_typacl, &isNull);
	if (isNull)
	{
		/* No ACL, so build default ACL */
		acl = acldefault(OBJECT_TYPE, ownerId);
		aclDatum = (Datum) 0;
	}
	else
	{
		/* detoast rel's ACL if necessary */
		acl = DatumGetAclP(aclDatum);
	}

	result = aclmask(acl, roleid, ownerId, mask, how);

	/* if we have a detoasted copy, free it */
	if (acl && (Pointer) acl != DatumGetPointer(aclDatum))
		pfree(acl);

	ReleaseSysCache(tuple);

	return result;
}
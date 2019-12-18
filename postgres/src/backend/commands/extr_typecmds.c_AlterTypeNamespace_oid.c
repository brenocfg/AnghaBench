#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ObjectAddresses ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 scalar_t__ AlterTypeNamespaceInternal (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  aclcheck_error_type (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 scalar_t__ get_array_type (scalar_t__) ; 
 scalar_t__ get_element_type (scalar_t__) ; 
 int /*<<< orphan*/  pg_type_ownercheck (scalar_t__,int /*<<< orphan*/ ) ; 

Oid
AlterTypeNamespace_oid(Oid typeOid, Oid nspOid, ObjectAddresses *objsMoved)
{
	Oid			elemOid;

	/* check permissions on type */
	if (!pg_type_ownercheck(typeOid, GetUserId()))
		aclcheck_error_type(ACLCHECK_NOT_OWNER, typeOid);

	/* don't allow direct alteration of array types */
	elemOid = get_element_type(typeOid);
	if (OidIsValid(elemOid) && get_array_type(elemOid) == typeOid)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot alter array type %s",
						format_type_be(typeOid)),
				 errhint("You can alter type %s, which will alter the array type as well.",
						 format_type_be(elemOid))));

	/* and do the work */
	return AlterTypeNamespaceInternal(typeOid, nspOid, false, true, objsMoved);
}
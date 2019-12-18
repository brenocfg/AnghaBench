#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ attisdropped; } ;
struct TYPE_3__ {int /*<<< orphan*/  relowner; } ;
typedef  scalar_t__ Pointer ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_class ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;
typedef  int /*<<< orphan*/  AclMode ;
typedef  int /*<<< orphan*/  AclMaskHow ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNUM ; 
 int /*<<< orphan*/  Anum_pg_attribute_attacl ; 
 int /*<<< orphan*/ * DatumGetAclP (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int16GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  aclmask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

AclMode
pg_attribute_aclmask(Oid table_oid, AttrNumber attnum, Oid roleid,
					 AclMode mask, AclMaskHow how)
{
	AclMode		result;
	HeapTuple	classTuple;
	HeapTuple	attTuple;
	Form_pg_class classForm;
	Form_pg_attribute attributeForm;
	Datum		aclDatum;
	bool		isNull;
	Acl		   *acl;
	Oid			ownerId;

	/*
	 * First, get the column's ACL from its pg_attribute entry
	 */
	attTuple = SearchSysCache2(ATTNUM,
							   ObjectIdGetDatum(table_oid),
							   Int16GetDatum(attnum));
	if (!HeapTupleIsValid(attTuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_COLUMN),
				 errmsg("attribute %d of relation with OID %u does not exist",
						attnum, table_oid)));
	attributeForm = (Form_pg_attribute) GETSTRUCT(attTuple);

	/* Throw error on dropped columns, too */
	if (attributeForm->attisdropped)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_COLUMN),
				 errmsg("attribute %d of relation with OID %u does not exist",
						attnum, table_oid)));

	aclDatum = SysCacheGetAttr(ATTNUM, attTuple, Anum_pg_attribute_attacl,
							   &isNull);

	/*
	 * Here we hard-wire knowledge that the default ACL for a column grants no
	 * privileges, so that we can fall out quickly in the very common case
	 * where attacl is null.
	 */
	if (isNull)
	{
		ReleaseSysCache(attTuple);
		return 0;
	}

	/*
	 * Must get the relation's ownerId from pg_class.  Since we already found
	 * a pg_attribute entry, the only likely reason for this to fail is that a
	 * concurrent DROP of the relation committed since then (which could only
	 * happen if we don't have lock on the relation).  We prefer to report "no
	 * privileges" rather than failing in such a case, so as to avoid unwanted
	 * failures in has_column_privilege() tests.
	 */
	classTuple = SearchSysCache1(RELOID, ObjectIdGetDatum(table_oid));
	if (!HeapTupleIsValid(classTuple))
	{
		ReleaseSysCache(attTuple);
		return 0;
	}
	classForm = (Form_pg_class) GETSTRUCT(classTuple);

	ownerId = classForm->relowner;

	ReleaseSysCache(classTuple);

	/* detoast column's ACL if necessary */
	acl = DatumGetAclP(aclDatum);

	result = aclmask(acl, roleid, ownerId, mask, how);

	/* if we have a detoasted copy, free it */
	if (acl && (Pointer) acl != DatumGetPointer(aclDatum))
		pfree(acl);

	ReleaseSysCache(attTuple);

	return result;
}
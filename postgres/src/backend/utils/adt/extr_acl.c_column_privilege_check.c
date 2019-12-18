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
struct TYPE_2__ {scalar_t__ attisdropped; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_attribute ;
typedef  scalar_t__ AttrNumber ;
typedef  scalar_t__ AclResult ;
typedef  int /*<<< orphan*/  AclMode ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ATTNUM ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int16GetDatum (scalar_t__) ; 
 scalar_t__ InvalidAttrNumber ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCacheExists1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_attribute_aclcheck (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_class_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
column_privilege_check(Oid tableoid, AttrNumber attnum,
					   Oid roleid, AclMode mode)
{
	AclResult	aclresult;
	HeapTuple	attTuple;
	Form_pg_attribute attributeForm;

	/*
	 * If convert_column_name failed, we can just return -1 immediately.
	 */
	if (attnum == InvalidAttrNumber)
		return -1;

	/*
	 * First check if we have the privilege at the table level.  We check
	 * existence of the pg_class row before risking calling pg_class_aclcheck.
	 * Note: it might seem there's a race condition against concurrent DROP,
	 * but really it's safe because there will be no syscache flush between
	 * here and there.  So if we see the row in the syscache, so will
	 * pg_class_aclcheck.
	 */
	if (!SearchSysCacheExists1(RELOID, ObjectIdGetDatum(tableoid)))
		return -1;

	aclresult = pg_class_aclcheck(tableoid, roleid, mode);

	if (aclresult == ACLCHECK_OK)
		return true;

	/*
	 * No table privilege, so try per-column privileges.  Again, we have to
	 * check for dropped attribute first, and we rely on the syscache not to
	 * notice a concurrent drop before pg_attribute_aclcheck fetches the row.
	 */
	attTuple = SearchSysCache2(ATTNUM,
							   ObjectIdGetDatum(tableoid),
							   Int16GetDatum(attnum));
	if (!HeapTupleIsValid(attTuple))
		return -1;
	attributeForm = (Form_pg_attribute) GETSTRUCT(attTuple);
	if (attributeForm->attisdropped)
	{
		ReleaseSysCache(attTuple);
		return -1;
	}
	ReleaseSysCache(attTuple);

	aclresult = pg_attribute_aclcheck(tableoid, attnum, roleid, mode);

	return (aclresult == ACLCHECK_OK);
}
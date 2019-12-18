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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_type_oid ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetNewOidWithIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ IsBinaryUpgrade ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TypeOidIndexId ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  binary_upgrade_next_array_pg_type_oid ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Oid
AssignTypeArrayOid(void)
{
	Oid			type_array_oid;

	/* Use binary-upgrade override for pg_type.typarray? */
	if (IsBinaryUpgrade)
	{
		if (!OidIsValid(binary_upgrade_next_array_pg_type_oid))
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("pg_type array OID value not set when in binary upgrade mode")));

		type_array_oid = binary_upgrade_next_array_pg_type_oid;
		binary_upgrade_next_array_pg_type_oid = InvalidOid;
	}
	else
	{
		Relation	pg_type = table_open(TypeRelationId, AccessShareLock);

		type_array_oid = GetNewOidWithIndex(pg_type, TypeOidIndexId,
											Anum_pg_type_oid);
		table_close(pg_type, AccessShareLock);
	}

	return type_array_oid;
}
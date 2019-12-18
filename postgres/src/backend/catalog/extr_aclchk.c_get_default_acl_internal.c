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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Acl ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_default_acl_defaclacl ; 
 int /*<<< orphan*/  CharGetDatum (char) ; 
 int /*<<< orphan*/  DEFACLROLENSPOBJ ; 
 int /*<<< orphan*/ * DatumGetAclPCopy (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static Acl *
get_default_acl_internal(Oid roleId, Oid nsp_oid, char objtype)
{
	Acl		   *result = NULL;
	HeapTuple	tuple;

	tuple = SearchSysCache3(DEFACLROLENSPOBJ,
							ObjectIdGetDatum(roleId),
							ObjectIdGetDatum(nsp_oid),
							CharGetDatum(objtype));

	if (HeapTupleIsValid(tuple))
	{
		Datum		aclDatum;
		bool		isNull;

		aclDatum = SysCacheGetAttr(DEFACLROLENSPOBJ, tuple,
								   Anum_pg_default_acl_defaclacl,
								   &isNull);
		if (!isNull)
			result = DatumGetAclPCopy(aclDatum);
		ReleaseSysCache(tuple);
	}

	return result;
}
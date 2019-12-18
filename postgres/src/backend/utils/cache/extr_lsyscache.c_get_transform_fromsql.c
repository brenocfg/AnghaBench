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
struct TYPE_2__ {int /*<<< orphan*/  trffromsql; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_transform ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRFTYPELANG ; 
 int /*<<< orphan*/  list_member_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Oid
get_transform_fromsql(Oid typid, Oid langid, List *trftypes)
{
	HeapTuple	tup;

	if (!list_member_oid(trftypes, typid))
		return InvalidOid;

	tup = SearchSysCache2(TRFTYPELANG, typid, langid);
	if (HeapTupleIsValid(tup))
	{
		Oid			funcid;

		funcid = ((Form_pg_transform) GETSTRUCT(tup))->trffromsql;
		ReleaseSysCache(tup);
		return funcid;
	}
	else
		return InvalidOid;
}
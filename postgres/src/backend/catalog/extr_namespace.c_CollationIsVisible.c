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
struct TYPE_2__ {scalar_t__ collnamespace; int /*<<< orphan*/  collname; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_collation ;

/* Variables and functions */
 int /*<<< orphan*/  COLLOID ; 
 scalar_t__ CollationGetCollid (char*) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ PG_CATALOG_NAMESPACE ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  activeSearchPath ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  list_member_oid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  recomputeNamespacePath () ; 

bool
CollationIsVisible(Oid collid)
{
	HeapTuple	colltup;
	Form_pg_collation collform;
	Oid			collnamespace;
	bool		visible;

	colltup = SearchSysCache1(COLLOID, ObjectIdGetDatum(collid));
	if (!HeapTupleIsValid(colltup))
		elog(ERROR, "cache lookup failed for collation %u", collid);
	collform = (Form_pg_collation) GETSTRUCT(colltup);

	recomputeNamespacePath();

	/*
	 * Quick check: if it ain't in the path at all, it ain't visible. Items in
	 * the system namespace are surely in the path and so we needn't even do
	 * list_member_oid() for them.
	 */
	collnamespace = collform->collnamespace;
	if (collnamespace != PG_CATALOG_NAMESPACE &&
		!list_member_oid(activeSearchPath, collnamespace))
		visible = false;
	else
	{
		/*
		 * If it is in the path, it might still not be visible; it could be
		 * hidden by another collation of the same name earlier in the path,
		 * or it might not work with the current DB encoding.  So we must do a
		 * slow check to see if this collation would be found by
		 * CollationGetCollid.
		 */
		char	   *collname = NameStr(collform->collname);

		visible = (CollationGetCollid(collname) == collid);
	}

	ReleaseSysCache(colltup);

	return visible;
}
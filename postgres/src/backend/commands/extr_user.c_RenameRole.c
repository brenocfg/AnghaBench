#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_12__ {scalar_t__ oid; scalar_t__ rolsuper; int /*<<< orphan*/  rolname; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_authid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHNAME ; 
 int Anum_pg_authid_rolname ; 
 int Anum_pg_authid_rolpassword ; 
 int /*<<< orphan*/  AuthIdRelationId ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_RESERVED_NAME ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 scalar_t__ GetOuterUserId () ; 
 scalar_t__ GetSessionUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IsReservedName (char const*) ; 
 int /*<<< orphan*/  NOTICE ; 
 char const* NameStr (int /*<<< orphan*/ ) ; 
 int Natts_pg_authid ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PASSWORD_TYPE_MD5 ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SearchSysCacheExists1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ get_password_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  have_createrole_privilege () ; 
 int /*<<< orphan*/  heap_getattr (TYPE_1__*,int,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  namein ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  superuser () ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
RenameRole(const char *oldname, const char *newname)
{
	HeapTuple	oldtuple,
				newtuple;
	TupleDesc	dsc;
	Relation	rel;
	Datum		datum;
	bool		isnull;
	Datum		repl_val[Natts_pg_authid];
	bool		repl_null[Natts_pg_authid];
	bool		repl_repl[Natts_pg_authid];
	int			i;
	Oid			roleid;
	ObjectAddress address;
	Form_pg_authid authform;

	rel = table_open(AuthIdRelationId, RowExclusiveLock);
	dsc = RelationGetDescr(rel);

	oldtuple = SearchSysCache1(AUTHNAME, CStringGetDatum(oldname));
	if (!HeapTupleIsValid(oldtuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("role \"%s\" does not exist", oldname)));

	/*
	 * XXX Client applications probably store the session user somewhere, so
	 * renaming it could cause confusion.  On the other hand, there may not be
	 * an actual problem besides a little confusion, so think about this and
	 * decide.  Same for SET ROLE ... we don't restrict renaming the current
	 * effective userid, though.
	 */

	authform = (Form_pg_authid) GETSTRUCT(oldtuple);
	roleid = authform->oid;

	if (roleid == GetSessionUserId())
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("session user cannot be renamed")));
	if (roleid == GetOuterUserId())
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("current user cannot be renamed")));

	/*
	 * Check that the user is not trying to rename a system role and not
	 * trying to rename a role into the reserved "pg_" namespace.
	 */
	if (IsReservedName(NameStr(authform->rolname)))
		ereport(ERROR,
				(errcode(ERRCODE_RESERVED_NAME),
				 errmsg("role name \"%s\" is reserved",
						NameStr(authform->rolname)),
				 errdetail("Role names starting with \"pg_\" are reserved.")));

	if (IsReservedName(newname))
		ereport(ERROR,
				(errcode(ERRCODE_RESERVED_NAME),
				 errmsg("role name \"%s\" is reserved",
						newname),
				 errdetail("Role names starting with \"pg_\" are reserved.")));

	/*
	 * If built with appropriate switch, whine when regression-testing
	 * conventions for role names are violated.
	 */
#ifdef ENFORCE_REGRESSION_TEST_NAME_RESTRICTIONS
	if (strncmp(newname, "regress_", 8) != 0)
		elog(WARNING, "roles created by regression test cases should have names starting with \"regress_\"");
#endif

	/* make sure the new name doesn't exist */
	if (SearchSysCacheExists1(AUTHNAME, CStringGetDatum(newname)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("role \"%s\" already exists", newname)));

	/*
	 * createrole is enough privilege unless you want to mess with a superuser
	 */
	if (((Form_pg_authid) GETSTRUCT(oldtuple))->rolsuper)
	{
		if (!superuser())
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("must be superuser to rename superusers")));
	}
	else
	{
		if (!have_createrole_privilege())
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("permission denied to rename role")));
	}

	/* OK, construct the modified tuple */
	for (i = 0; i < Natts_pg_authid; i++)
		repl_repl[i] = false;

	repl_repl[Anum_pg_authid_rolname - 1] = true;
	repl_val[Anum_pg_authid_rolname - 1] = DirectFunctionCall1(namein,
															   CStringGetDatum(newname));
	repl_null[Anum_pg_authid_rolname - 1] = false;

	datum = heap_getattr(oldtuple, Anum_pg_authid_rolpassword, dsc, &isnull);

	if (!isnull && get_password_type(TextDatumGetCString(datum)) == PASSWORD_TYPE_MD5)
	{
		/* MD5 uses the username as salt, so just clear it on a rename */
		repl_repl[Anum_pg_authid_rolpassword - 1] = true;
		repl_null[Anum_pg_authid_rolpassword - 1] = true;

		ereport(NOTICE,
				(errmsg("MD5 password cleared because of role rename")));
	}

	newtuple = heap_modify_tuple(oldtuple, dsc, repl_val, repl_null, repl_repl);
	CatalogTupleUpdate(rel, &oldtuple->t_self, newtuple);

	InvokeObjectPostAlterHook(AuthIdRelationId, roleid, 0);

	ObjectAddressSet(address, AuthIdRelationId, roleid);

	ReleaseSysCache(oldtuple);

	/*
	 * Close pg_authid, but keep lock till commit.
	 */
	table_close(rel, NoLock);

	return address;
}
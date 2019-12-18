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
struct TYPE_2__ {int relrowsecurity; int relforcerowsecurity; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstNormalObjectId ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InNoForceRLSOperation () ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  RELOID ; 
 int RLS_ENABLED ; 
 int RLS_NONE ; 
 int RLS_NONE_ENV ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (scalar_t__) ; 
 scalar_t__ has_bypassrls_privilege (scalar_t__) ; 
 int pg_class_ownercheck (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  row_security ; 

int
check_enable_rls(Oid relid, Oid checkAsUser, bool noError)
{
	Oid			user_id = checkAsUser ? checkAsUser : GetUserId();
	HeapTuple	tuple;
	Form_pg_class classform;
	bool		relrowsecurity;
	bool		relforcerowsecurity;
	bool		amowner;

	/* Nothing to do for built-in relations */
	if (relid < (Oid) FirstNormalObjectId)
		return RLS_NONE;

	/* Fetch relation's relrowsecurity and relforcerowsecurity flags */
	tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(relid));
	if (!HeapTupleIsValid(tuple))
		return RLS_NONE;
	classform = (Form_pg_class) GETSTRUCT(tuple);

	relrowsecurity = classform->relrowsecurity;
	relforcerowsecurity = classform->relforcerowsecurity;

	ReleaseSysCache(tuple);

	/* Nothing to do if the relation does not have RLS */
	if (!relrowsecurity)
		return RLS_NONE;

	/*
	 * BYPASSRLS users always bypass RLS.  Note that superusers are always
	 * considered to have BYPASSRLS.
	 *
	 * Return RLS_NONE_ENV to indicate that this decision depends on the
	 * environment (in this case, the user_id).
	 */
	if (has_bypassrls_privilege(user_id))
		return RLS_NONE_ENV;

	/*
	 * Table owners generally bypass RLS, except if the table has been set (by
	 * an owner) to FORCE ROW SECURITY, and this is not a referential
	 * integrity check.
	 *
	 * Return RLS_NONE_ENV to indicate that this decision depends on the
	 * environment (in this case, the user_id).
	 */
	amowner = pg_class_ownercheck(relid, user_id);
	if (amowner)
	{
		/*
		 * If FORCE ROW LEVEL SECURITY has been set on the relation then we
		 * should return RLS_ENABLED to indicate that RLS should be applied.
		 * If not, or if we are in an InNoForceRLSOperation context, we return
		 * RLS_NONE_ENV.
		 *
		 * InNoForceRLSOperation indicates that we should not apply RLS even
		 * if the table has FORCE RLS set - IF the current user is the owner.
		 * This is specifically to ensure that referential integrity checks
		 * are able to still run correctly.
		 *
		 * This is intentionally only done after we have checked that the user
		 * is the table owner, which should always be the case for referential
		 * integrity checks.
		 */
		if (!relforcerowsecurity || InNoForceRLSOperation())
			return RLS_NONE_ENV;
	}

	/*
	 * We should apply RLS.  However, the user may turn off the row_security
	 * GUC to get a forced error instead.
	 */
	if (!row_security && !noError)
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("query would be affected by row-level security policy for table \"%s\"",
						get_rel_name(relid)),
				 amowner ? errhint("To disable the policy for the table's owner, use ALTER TABLE NO FORCE ROW LEVEL SECURITY.") : 0));

	/* RLS should be fully enabled for this relation. */
	return RLS_ENABLED;
}
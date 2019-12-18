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
typedef  scalar_t__ TimestampTz ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHNAME ; 
 int /*<<< orphan*/  Anum_pg_authid_rolpassword ; 
 int /*<<< orphan*/  Anum_pg_authid_rolvaliduntil ; 
 scalar_t__ DatumGetTimestampTz (int /*<<< orphan*/ ) ; 
 scalar_t__ GetCurrentTimestamp () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* psprintf (int /*<<< orphan*/ ,char const*) ; 

char *
get_role_password(const char *role, char **logdetail)
{
	TimestampTz vuntil = 0;
	HeapTuple	roleTup;
	Datum		datum;
	bool		isnull;
	char	   *shadow_pass;

	/* Get role info from pg_authid */
	roleTup = SearchSysCache1(AUTHNAME, PointerGetDatum(role));
	if (!HeapTupleIsValid(roleTup))
	{
		*logdetail = psprintf(_("Role \"%s\" does not exist."),
							  role);
		return NULL;			/* no such user */
	}

	datum = SysCacheGetAttr(AUTHNAME, roleTup,
							Anum_pg_authid_rolpassword, &isnull);
	if (isnull)
	{
		ReleaseSysCache(roleTup);
		*logdetail = psprintf(_("User \"%s\" has no password assigned."),
							  role);
		return NULL;			/* user has no password */
	}
	shadow_pass = TextDatumGetCString(datum);

	datum = SysCacheGetAttr(AUTHNAME, roleTup,
							Anum_pg_authid_rolvaliduntil, &isnull);
	if (!isnull)
		vuntil = DatumGetTimestampTz(datum);

	ReleaseSysCache(roleTup);

	/*
	 * Password OK, but check to be sure we are not past rolvaliduntil
	 */
	if (!isnull && vuntil < GetCurrentTimestamp())
	{
		*logdetail = psprintf(_("User \"%s\" has an expired password."),
							  role);
		return NULL;
	}

	return shadow_pass;
}
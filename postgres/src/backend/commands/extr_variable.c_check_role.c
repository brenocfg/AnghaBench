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
struct TYPE_3__ {int is_superuser; int /*<<< orphan*/  roleid; } ;
typedef  TYPE_1__ role_auth_extra ;
struct TYPE_4__ {int rolsuper; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  GucSource ;
typedef  TYPE_2__* Form_pg_authid ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHNAME ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUC_check_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUC_check_errmsg (char*,char*) ; 
 int /*<<< orphan*/  GetSessionUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializingParallelWorker ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsTransactionState () ; 
 int /*<<< orphan*/  PointerGetDatum (char*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_member_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ strcmp (char*,char*) ; 

bool
check_role(char **newval, void **extra, GucSource source)
{
	HeapTuple	roleTup;
	Oid			roleid;
	bool		is_superuser;
	role_auth_extra *myextra;
	Form_pg_authid roleform;

	if (strcmp(*newval, "none") == 0)
	{
		/* hardwired translation */
		roleid = InvalidOid;
		is_superuser = false;
	}
	else
	{
		if (!IsTransactionState())
		{
			/*
			 * Can't do catalog lookups, so fail.  The result of this is that
			 * role cannot be set in postgresql.conf, which seems like a good
			 * thing anyway, so we don't work hard to avoid it.
			 */
			return false;
		}

		/* Look up the username */
		roleTup = SearchSysCache1(AUTHNAME, PointerGetDatum(*newval));
		if (!HeapTupleIsValid(roleTup))
		{
			GUC_check_errmsg("role \"%s\" does not exist", *newval);
			return false;
		}

		roleform = (Form_pg_authid) GETSTRUCT(roleTup);
		roleid = roleform->oid;
		is_superuser = roleform->rolsuper;

		ReleaseSysCache(roleTup);

		/*
		 * Verify that session user is allowed to become this role, but skip
		 * this in parallel mode, where we must blindly recreate the parallel
		 * leader's state.
		 */
		if (!InitializingParallelWorker &&
			!is_member_of_role(GetSessionUserId(), roleid))
		{
			GUC_check_errcode(ERRCODE_INSUFFICIENT_PRIVILEGE);
			GUC_check_errmsg("permission denied to set role \"%s\"",
							 *newval);
			return false;
		}
	}

	/* Set up "extra" struct for assign_role to use */
	myextra = (role_auth_extra *) malloc(sizeof(role_auth_extra));
	if (!myextra)
		return false;
	myextra->roleid = roleid;
	myextra->is_superuser = is_superuser;
	*extra = (void *) myextra;

	return true;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  setstmt; int /*<<< orphan*/ * database; scalar_t__ role; } ;
struct TYPE_4__ {scalar_t__ oid; scalar_t__ rolsuper; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_authid ;
typedef  TYPE_2__ AlterRoleSetStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  AlterSetting (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AuthIdRelationId ; 
 int /*<<< orphan*/  DatabaseRelationId ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ GetUserId () ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  OBJECT_DATABASE ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_rolespec_name (scalar_t__,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ get_database_oid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_rolespec_tuple (scalar_t__) ; 
 int /*<<< orphan*/  have_createrole_privilege () ; 
 int /*<<< orphan*/  pg_database_ownercheck (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  shdepLockAndCheckObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  superuser () ; 

Oid
AlterRoleSet(AlterRoleSetStmt *stmt)
{
	HeapTuple	roletuple;
	Form_pg_authid roleform;
	Oid			databaseid = InvalidOid;
	Oid			roleid = InvalidOid;

	if (stmt->role)
	{
		check_rolespec_name(stmt->role,
							"Cannot alter reserved roles.");

		roletuple = get_rolespec_tuple(stmt->role);
		roleform = (Form_pg_authid) GETSTRUCT(roletuple);
		roleid = roleform->oid;

		/*
		 * Obtain a lock on the role and make sure it didn't go away in the
		 * meantime.
		 */
		shdepLockAndCheckObject(AuthIdRelationId, roleid);

		/*
		 * To mess with a superuser you gotta be superuser; else you need
		 * createrole, or just want to change your own settings
		 */
		if (roleform->rolsuper)
		{
			if (!superuser())
				ereport(ERROR,
						(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
						 errmsg("must be superuser to alter superusers")));
		}
		else
		{
			if (!have_createrole_privilege() && roleid != GetUserId())
				ereport(ERROR,
						(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
						 errmsg("permission denied")));
		}

		ReleaseSysCache(roletuple);
	}

	/* look up and lock the database, if specified */
	if (stmt->database != NULL)
	{
		databaseid = get_database_oid(stmt->database, false);
		shdepLockAndCheckObject(DatabaseRelationId, databaseid);

		if (!stmt->role)
		{
			/*
			 * If no role is specified, then this is effectively the same as
			 * ALTER DATABASE ... SET, so use the same permission check.
			 */
			if (!pg_database_ownercheck(databaseid, GetUserId()))
				aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_DATABASE,
							   stmt->database);
		}
	}

	if (!stmt->role && !stmt->database)
	{
		/* Must be superuser to alter settings globally. */
		if (!superuser())
			ereport(ERROR,
					(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
					 errmsg("must be superuser to alter settings globally")));
	}

	AlterSetting(databaseid, roleid, stmt->setstmt);

	return roleid;
}
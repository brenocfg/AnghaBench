#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  setstmt; int /*<<< orphan*/  dbname; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ AlterDatabaseSetStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  AlterSetting (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatabaseRelationId ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  OBJECT_DATABASE ; 
 int /*<<< orphan*/  UnlockSharedObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_database_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pg_database_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shdepLockAndCheckObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Oid
AlterDatabaseSet(AlterDatabaseSetStmt *stmt)
{
	Oid			datid = get_database_oid(stmt->dbname, false);

	/*
	 * Obtain a lock on the database and make sure it didn't go away in the
	 * meantime.
	 */
	shdepLockAndCheckObject(DatabaseRelationId, datid);

	if (!pg_database_ownercheck(datid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_DATABASE,
					   stmt->dbname);

	AlterSetting(datid, InvalidOid, stmt->setstmt);

	UnlockSharedObject(DatabaseRelationId, datid, 0, AccessShareLock);

	return datid;
}
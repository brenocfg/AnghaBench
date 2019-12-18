#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  datname; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_database ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ CountOtherDBBackends (scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  DATABASEOID ; 
 int /*<<< orphan*/  DatabaseRelationId ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_DATABASE ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_IN_USE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_DATABASE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MyDatabaseId ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OBJECT_DATABASE ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_busy_db (int,int) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_database_oid (char const*,int) ; 
 int /*<<< orphan*/  get_db_info (char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  have_createdb_privilege () ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pg_database_ownercheck (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
RenameDatabase(const char *oldname, const char *newname)
{
	Oid			db_id;
	HeapTuple	newtup;
	Relation	rel;
	int			notherbackends;
	int			npreparedxacts;
	ObjectAddress address;

	/*
	 * Look up the target database's OID, and get exclusive lock on it. We
	 * need this for the same reasons as DROP DATABASE.
	 */
	rel = table_open(DatabaseRelationId, RowExclusiveLock);

	if (!get_db_info(oldname, AccessExclusiveLock, &db_id, NULL, NULL,
					 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_DATABASE),
				 errmsg("database \"%s\" does not exist", oldname)));

	/* must be owner */
	if (!pg_database_ownercheck(db_id, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_DATABASE,
					   oldname);

	/* must have createdb rights */
	if (!have_createdb_privilege())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied to rename database")));

	/*
	 * If built with appropriate switch, whine when regression-testing
	 * conventions for database names are violated.
	 */
#ifdef ENFORCE_REGRESSION_TEST_NAME_RESTRICTIONS
	if (strstr(newname, "regression") == NULL)
		elog(WARNING, "databases created by regression test cases should have names including \"regression\"");
#endif

	/*
	 * Make sure the new name doesn't exist.  See notes for same error in
	 * CREATE DATABASE.
	 */
	if (OidIsValid(get_database_oid(newname, true)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_DATABASE),
				 errmsg("database \"%s\" already exists", newname)));

	/*
	 * XXX Client applications probably store the current database somewhere,
	 * so renaming it could cause confusion.  On the other hand, there may not
	 * be an actual problem besides a little confusion, so think about this
	 * and decide.
	 */
	if (db_id == MyDatabaseId)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("current database cannot be renamed")));

	/*
	 * Make sure the database does not have active sessions.  This is the same
	 * concern as above, but applied to other sessions.
	 *
	 * As in CREATE DATABASE, check this after other error conditions.
	 */
	if (CountOtherDBBackends(db_id, &notherbackends, &npreparedxacts))
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_IN_USE),
				 errmsg("database \"%s\" is being accessed by other users",
						oldname),
				 errdetail_busy_db(notherbackends, npreparedxacts)));

	/* rename */
	newtup = SearchSysCacheCopy1(DATABASEOID, ObjectIdGetDatum(db_id));
	if (!HeapTupleIsValid(newtup))
		elog(ERROR, "cache lookup failed for database %u", db_id);
	namestrcpy(&(((Form_pg_database) GETSTRUCT(newtup))->datname), newname);
	CatalogTupleUpdate(rel, &newtup->t_self, newtup);

	InvokeObjectPostAlterHook(DatabaseRelationId, db_id, 0);

	ObjectAddressSet(address, DatabaseRelationId, db_id);

	/*
	 * Close pg_database, but keep lock till commit.
	 */
	table_close(rel, NoLock);

	return address;
}
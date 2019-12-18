#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int CHECKPOINT_FORCE ; 
 int CHECKPOINT_IMMEDIATE ; 
 int CHECKPOINT_WAIT ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CountDBSubscriptions (scalar_t__) ; 
 scalar_t__ CountOtherDBBackends (scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  DATABASEOID ; 
 int /*<<< orphan*/  DatabaseRelationId ; 
 int /*<<< orphan*/  DeleteSharedComments (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteSharedSecurityLabel (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DropDatabaseBuffers (scalar_t__) ; 
 int /*<<< orphan*/  DropSetting (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_IN_USE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_DATABASE ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ForceSyncCommit () ; 
 int /*<<< orphan*/  ForgetDatabaseSyncRequests (scalar_t__) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectDropHook (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MyDatabaseId ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OBJECT_DATABASE ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  ReplicationSlotsCountDBSlots (scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  ReplicationSlotsDropDBSlots (scalar_t__) ; 
 int /*<<< orphan*/  RequestCheckpoint (int) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TerminateOtherDBBackends (scalar_t__) ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dropDatabaseDependencies (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_busy_db (int,int) ; 
 int /*<<< orphan*/  errdetail_plural (char*,char*,int,int) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_db_info (char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_database_ownercheck (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_drop_database (scalar_t__) ; 
 int /*<<< orphan*/  remove_dbtablespaces (scalar_t__) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dropdb(const char *dbname, bool missing_ok, bool force)
{
	Oid			db_id;
	bool		db_istemplate;
	Relation	pgdbrel;
	HeapTuple	tup;
	int			notherbackends;
	int			npreparedxacts;
	int			nslots,
				nslots_active;
	int			nsubscriptions;

	/*
	 * Look up the target database's OID, and get exclusive lock on it. We
	 * need this to ensure that no new backend starts up in the target
	 * database while we are deleting it (see postinit.c), and that no one is
	 * using it as a CREATE DATABASE template or trying to delete it for
	 * themselves.
	 */
	pgdbrel = table_open(DatabaseRelationId, RowExclusiveLock);

	if (!get_db_info(dbname, AccessExclusiveLock, &db_id, NULL, NULL,
					 &db_istemplate, NULL, NULL, NULL, NULL, NULL, NULL, NULL))
	{
		if (!missing_ok)
		{
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_DATABASE),
					 errmsg("database \"%s\" does not exist", dbname)));
		}
		else
		{
			/* Close pg_database, release the lock, since we changed nothing */
			table_close(pgdbrel, RowExclusiveLock);
			ereport(NOTICE,
					(errmsg("database \"%s\" does not exist, skipping",
							dbname)));
			return;
		}
	}

	/*
	 * Permission checks
	 */
	if (!pg_database_ownercheck(db_id, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_DATABASE,
					   dbname);

	/* DROP hook for the database being removed */
	InvokeObjectDropHook(DatabaseRelationId, db_id, 0);

	/*
	 * Disallow dropping a DB that is marked istemplate.  This is just to
	 * prevent people from accidentally dropping template0 or template1; they
	 * can do so if they're really determined ...
	 */
	if (db_istemplate)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot drop a template database")));

	/* Obviously can't drop my own database */
	if (db_id == MyDatabaseId)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_IN_USE),
				 errmsg("cannot drop the currently open database")));

	/*
	 * Check whether there are active logical slots that refer to the
	 * to-be-dropped database. The database lock we are holding prevents the
	 * creation of new slots using the database or existing slots becoming
	 * active.
	 */
	(void) ReplicationSlotsCountDBSlots(db_id, &nslots, &nslots_active);
	if (nslots_active)
	{
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_IN_USE),
				 errmsg("database \"%s\" is used by an active logical replication slot",
						dbname),
				 errdetail_plural("There is %d active slot.",
								  "There are %d active slots.",
								  nslots_active, nslots_active)));
	}

	/*
	 * Check if there are subscriptions defined in the target database.
	 *
	 * We can't drop them automatically because they might be holding
	 * resources in other databases/instances.
	 */
	if ((nsubscriptions = CountDBSubscriptions(db_id)) > 0)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_IN_USE),
				 errmsg("database \"%s\" is being used by logical replication subscription",
						dbname),
				 errdetail_plural("There is %d subscription.",
								  "There are %d subscriptions.",
								  nsubscriptions, nsubscriptions)));


	/*
	 * Attempt to terminate all existing connections to the target database if
	 * the user has requested to do so.
	 */
	if (force)
		TerminateOtherDBBackends(db_id);

	/*
	 * Check for other backends in the target database.  (Because we hold the
	 * database lock, no new ones can start after this.)
	 *
	 * As in CREATE DATABASE, check this after other error conditions.
	 */
	if (CountOtherDBBackends(db_id, &notherbackends, &npreparedxacts))
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_IN_USE),
				 errmsg("database \"%s\" is being accessed by other users",
						dbname),
				 errdetail_busy_db(notherbackends, npreparedxacts)));

	/*
	 * Remove the database's tuple from pg_database.
	 */
	tup = SearchSysCache1(DATABASEOID, ObjectIdGetDatum(db_id));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for database %u", db_id);

	CatalogTupleDelete(pgdbrel, &tup->t_self);

	ReleaseSysCache(tup);

	/*
	 * Delete any comments or security labels associated with the database.
	 */
	DeleteSharedComments(db_id, DatabaseRelationId);
	DeleteSharedSecurityLabel(db_id, DatabaseRelationId);

	/*
	 * Remove settings associated with this database
	 */
	DropSetting(db_id, InvalidOid);

	/*
	 * Remove shared dependency references for the database.
	 */
	dropDatabaseDependencies(db_id);

	/*
	 * Drop db-specific replication slots.
	 */
	ReplicationSlotsDropDBSlots(db_id);

	/*
	 * Drop pages for this database that are in the shared buffer cache. This
	 * is important to ensure that no remaining backend tries to write out a
	 * dirty buffer to the dead database later...
	 */
	DropDatabaseBuffers(db_id);

	/*
	 * Tell the stats collector to forget it immediately, too.
	 */
	pgstat_drop_database(db_id);

	/*
	 * Tell checkpointer to forget any pending fsync and unlink requests for
	 * files in the database; else the fsyncs will fail at next checkpoint, or
	 * worse, it will delete files that belong to a newly created database
	 * with the same OID.
	 */
	ForgetDatabaseSyncRequests(db_id);

	/*
	 * Force a checkpoint to make sure the checkpointer has received the
	 * message sent by ForgetDatabaseSyncRequests. On Windows, this also
	 * ensures that background procs don't hold any open files, which would
	 * cause rmdir() to fail.
	 */
	RequestCheckpoint(CHECKPOINT_IMMEDIATE | CHECKPOINT_FORCE | CHECKPOINT_WAIT);

	/*
	 * Remove all tablespace subdirs belonging to the database.
	 */
	remove_dbtablespaces(db_id);

	/*
	 * Close pg_database, but keep lock till commit.
	 */
	table_close(pgdbrel, NoLock);

	/*
	 * Force synchronous commit, thus minimizing the window between removal of
	 * the database files and committal of the transaction. If we crash before
	 * committing, we'll have a DB that's gone on disk but still there
	 * according to pg_database, which is not good.
	 */
	ForceSyncCommit();
}
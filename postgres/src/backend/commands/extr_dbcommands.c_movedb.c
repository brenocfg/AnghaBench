#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ tablespace_id; scalar_t__ db_id; } ;
typedef  TYPE_1__ xl_dbase_drop_rec ;
struct TYPE_12__ {scalar_t__ src_tablespace_id; scalar_t__ src_db_id; scalar_t__ tablespace_id; scalar_t__ db_id; } ;
typedef  TYPE_2__ xl_dbase_create_rec ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  new_record_repl ;
typedef  int /*<<< orphan*/  new_record_nulls ;
typedef  int /*<<< orphan*/  new_record ;
struct TYPE_13__ {scalar_t__ dest_tsoid; scalar_t__ dest_dboid; } ;
typedef  TYPE_3__ movedb_failure_params ;
struct TYPE_14__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_4__* HeapTuple ;
typedef  int Datum ;
typedef  int /*<<< orphan*/  DIR ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_NOT_OWNER ; 
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/ * AllocateDir (char*) ; 
 int /*<<< orphan*/  Anum_pg_database_datname ; 
 int Anum_pg_database_dattablespace ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int CHECKPOINT_FLUSH_ALL ; 
 int CHECKPOINT_FORCE ; 
 int CHECKPOINT_IMMEDIATE ; 
 int CHECKPOINT_WAIT ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 scalar_t__ CountOtherDBBackends (scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  DatabaseNameIndexId ; 
 int /*<<< orphan*/  DatabaseRelationId ; 
 int /*<<< orphan*/  DropDatabaseBuffers (scalar_t__) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_IN_USE ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_DATABASE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  ForceSyncCommit () ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 scalar_t__ GLOBALTABLESPACE_OID ; 
 char* GetDatabasePath (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_4__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockSharedObjectForSession (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 scalar_t__ MyDatabaseId ; 
 int Natts_pg_database ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OBJECT_DATABASE ; 
 int /*<<< orphan*/  OBJECT_TABLESPACE ; 
 int ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  PG_END_ENSURE_ERROR_CLEANUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_ENSURE_ERROR_CLEANUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_3__*) ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  RM_DBASE_ID ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RequestCheckpoint (int) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  UnlockSharedObjectForSession (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int XLOG_DBASE_CREATE ; 
 int XLOG_DBASE_DROP ; 
 int XLR_SPECIAL_REL_UPDATE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  copydir (char*,char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_busy_db (int,int) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_db_info (char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ get_tablespace_oid (char const*,int) ; 
 TYPE_4__* heap_modify_tuple (TYPE_4__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  movedb_failure_callback ; 
 int /*<<< orphan*/  pg_database_ownercheck (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_tablespace_aclcheck (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rmdir (char*) ; 
 int /*<<< orphan*/  rmtree (char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_4__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
movedb(const char *dbname, const char *tblspcname)
{
	Oid			db_id;
	Relation	pgdbrel;
	int			notherbackends;
	int			npreparedxacts;
	HeapTuple	oldtuple,
				newtuple;
	Oid			src_tblspcoid,
				dst_tblspcoid;
	Datum		new_record[Natts_pg_database];
	bool		new_record_nulls[Natts_pg_database];
	bool		new_record_repl[Natts_pg_database];
	ScanKeyData scankey;
	SysScanDesc sysscan;
	AclResult	aclresult;
	char	   *src_dbpath;
	char	   *dst_dbpath;
	DIR		   *dstdir;
	struct dirent *xlde;
	movedb_failure_params fparms;

	/*
	 * Look up the target database's OID, and get exclusive lock on it. We
	 * need this to ensure that no new backend starts up in the database while
	 * we are moving it, and that no one is using it as a CREATE DATABASE
	 * template or trying to delete it.
	 */
	pgdbrel = table_open(DatabaseRelationId, RowExclusiveLock);

	if (!get_db_info(dbname, AccessExclusiveLock, &db_id, NULL, NULL,
					 NULL, NULL, NULL, NULL, NULL, &src_tblspcoid, NULL, NULL))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_DATABASE),
				 errmsg("database \"%s\" does not exist", dbname)));

	/*
	 * We actually need a session lock, so that the lock will persist across
	 * the commit/restart below.  (We could almost get away with letting the
	 * lock be released at commit, except that someone could try to move
	 * relations of the DB back into the old directory while we rmtree() it.)
	 */
	LockSharedObjectForSession(DatabaseRelationId, db_id, 0,
							   AccessExclusiveLock);

	/*
	 * Permission checks
	 */
	if (!pg_database_ownercheck(db_id, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_DATABASE,
					   dbname);

	/*
	 * Obviously can't move the tables of my own database
	 */
	if (db_id == MyDatabaseId)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_IN_USE),
				 errmsg("cannot change the tablespace of the currently open database")));

	/*
	 * Get tablespace's oid
	 */
	dst_tblspcoid = get_tablespace_oid(tblspcname, false);

	/*
	 * Permission checks
	 */
	aclresult = pg_tablespace_aclcheck(dst_tblspcoid, GetUserId(),
									   ACL_CREATE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_TABLESPACE,
					   tblspcname);

	/*
	 * pg_global must never be the default tablespace
	 */
	if (dst_tblspcoid == GLOBALTABLESPACE_OID)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("pg_global cannot be used as default tablespace")));

	/*
	 * No-op if same tablespace
	 */
	if (src_tblspcoid == dst_tblspcoid)
	{
		table_close(pgdbrel, NoLock);
		UnlockSharedObjectForSession(DatabaseRelationId, db_id, 0,
									 AccessExclusiveLock);
		return;
	}

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
	 * Get old and new database paths
	 */
	src_dbpath = GetDatabasePath(db_id, src_tblspcoid);
	dst_dbpath = GetDatabasePath(db_id, dst_tblspcoid);

	/*
	 * Force a checkpoint before proceeding. This will force all dirty
	 * buffers, including those of unlogged tables, out to disk, to ensure
	 * source database is up-to-date on disk for the copy.
	 * FlushDatabaseBuffers() would suffice for that, but we also want to
	 * process any pending unlink requests. Otherwise, the check for existing
	 * files in the target directory might fail unnecessarily, not to mention
	 * that the copy might fail due to source files getting deleted under it.
	 * On Windows, this also ensures that background procs don't hold any open
	 * files, which would cause rmdir() to fail.
	 */
	RequestCheckpoint(CHECKPOINT_IMMEDIATE | CHECKPOINT_FORCE | CHECKPOINT_WAIT
					  | CHECKPOINT_FLUSH_ALL);

	/*
	 * Now drop all buffers holding data of the target database; they should
	 * no longer be dirty so DropDatabaseBuffers is safe.
	 *
	 * It might seem that we could just let these buffers age out of shared
	 * buffers naturally, since they should not get referenced anymore.  The
	 * problem with that is that if the user later moves the database back to
	 * its original tablespace, any still-surviving buffers would appear to
	 * contain valid data again --- but they'd be missing any changes made in
	 * the database while it was in the new tablespace.  In any case, freeing
	 * buffers that should never be used again seems worth the cycles.
	 *
	 * Note: it'd be sufficient to get rid of buffers matching db_id and
	 * src_tblspcoid, but bufmgr.c presently provides no API for that.
	 */
	DropDatabaseBuffers(db_id);

	/*
	 * Check for existence of files in the target directory, i.e., objects of
	 * this database that are already in the target tablespace.  We can't
	 * allow the move in such a case, because we would need to change those
	 * relations' pg_class.reltablespace entries to zero, and we don't have
	 * access to the DB's pg_class to do so.
	 */
	dstdir = AllocateDir(dst_dbpath);
	if (dstdir != NULL)
	{
		while ((xlde = ReadDir(dstdir, dst_dbpath)) != NULL)
		{
			if (strcmp(xlde->d_name, ".") == 0 ||
				strcmp(xlde->d_name, "..") == 0)
				continue;

			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("some relations of database \"%s\" are already in tablespace \"%s\"",
							dbname, tblspcname),
					 errhint("You must move them back to the database's default tablespace before using this command.")));
		}

		FreeDir(dstdir);

		/*
		 * The directory exists but is empty. We must remove it before using
		 * the copydir function.
		 */
		if (rmdir(dst_dbpath) != 0)
			elog(ERROR, "could not remove directory \"%s\": %m",
				 dst_dbpath);
	}

	/*
	 * Use an ENSURE block to make sure we remove the debris if the copy fails
	 * (eg, due to out-of-disk-space).  This is not a 100% solution, because
	 * of the possibility of failure during transaction commit, but it should
	 * handle most scenarios.
	 */
	fparms.dest_dboid = db_id;
	fparms.dest_tsoid = dst_tblspcoid;
	PG_ENSURE_ERROR_CLEANUP(movedb_failure_callback,
							PointerGetDatum(&fparms));
	{
		/*
		 * Copy files from the old tablespace to the new one
		 */
		copydir(src_dbpath, dst_dbpath, false);

		/*
		 * Record the filesystem change in XLOG
		 */
		{
			xl_dbase_create_rec xlrec;

			xlrec.db_id = db_id;
			xlrec.tablespace_id = dst_tblspcoid;
			xlrec.src_db_id = db_id;
			xlrec.src_tablespace_id = src_tblspcoid;

			XLogBeginInsert();
			XLogRegisterData((char *) &xlrec, sizeof(xl_dbase_create_rec));

			(void) XLogInsert(RM_DBASE_ID,
							  XLOG_DBASE_CREATE | XLR_SPECIAL_REL_UPDATE);
		}

		/*
		 * Update the database's pg_database tuple
		 */
		ScanKeyInit(&scankey,
					Anum_pg_database_datname,
					BTEqualStrategyNumber, F_NAMEEQ,
					CStringGetDatum(dbname));
		sysscan = systable_beginscan(pgdbrel, DatabaseNameIndexId, true,
									 NULL, 1, &scankey);
		oldtuple = systable_getnext(sysscan);
		if (!HeapTupleIsValid(oldtuple))	/* shouldn't happen... */
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_DATABASE),
					 errmsg("database \"%s\" does not exist", dbname)));

		MemSet(new_record, 0, sizeof(new_record));
		MemSet(new_record_nulls, false, sizeof(new_record_nulls));
		MemSet(new_record_repl, false, sizeof(new_record_repl));

		new_record[Anum_pg_database_dattablespace - 1] = ObjectIdGetDatum(dst_tblspcoid);
		new_record_repl[Anum_pg_database_dattablespace - 1] = true;

		newtuple = heap_modify_tuple(oldtuple, RelationGetDescr(pgdbrel),
									 new_record,
									 new_record_nulls, new_record_repl);
		CatalogTupleUpdate(pgdbrel, &oldtuple->t_self, newtuple);

		InvokeObjectPostAlterHook(DatabaseRelationId, db_id, 0);

		systable_endscan(sysscan);

		/*
		 * Force another checkpoint here.  As in CREATE DATABASE, this is to
		 * ensure that we don't have to replay a committed XLOG_DBASE_CREATE
		 * operation, which would cause us to lose any unlogged operations
		 * done in the new DB tablespace before the next checkpoint.
		 */
		RequestCheckpoint(CHECKPOINT_IMMEDIATE | CHECKPOINT_FORCE | CHECKPOINT_WAIT);

		/*
		 * Force synchronous commit, thus minimizing the window between
		 * copying the database files and committal of the transaction. If we
		 * crash before committing, we'll leave an orphaned set of files on
		 * disk, which is not fatal but not good either.
		 */
		ForceSyncCommit();

		/*
		 * Close pg_database, but keep lock till commit.
		 */
		table_close(pgdbrel, NoLock);
	}
	PG_END_ENSURE_ERROR_CLEANUP(movedb_failure_callback,
								PointerGetDatum(&fparms));

	/*
	 * Commit the transaction so that the pg_database update is committed. If
	 * we crash while removing files, the database won't be corrupt, we'll
	 * just leave some orphaned files in the old directory.
	 *
	 * (This is OK because we know we aren't inside a transaction block.)
	 *
	 * XXX would it be safe/better to do this inside the ensure block?	Not
	 * convinced it's a good idea; consider elog just after the transaction
	 * really commits.
	 */
	PopActiveSnapshot();
	CommitTransactionCommand();

	/* Start new transaction for the remaining work; don't need a snapshot */
	StartTransactionCommand();

	/*
	 * Remove files from the old tablespace
	 */
	if (!rmtree(src_dbpath, true))
		ereport(WARNING,
				(errmsg("some useless files may be left behind in old database directory \"%s\"",
						src_dbpath)));

	/*
	 * Record the filesystem change in XLOG
	 */
	{
		xl_dbase_drop_rec xlrec;

		xlrec.db_id = db_id;
		xlrec.tablespace_id = src_tblspcoid;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, sizeof(xl_dbase_drop_rec));

		(void) XLogInsert(RM_DBASE_ID,
						  XLOG_DBASE_DROP | XLR_SPECIAL_REL_UPDATE);
	}

	/* Now it's safe to release the database lock */
	UnlockSharedObjectForSession(DatabaseRelationId, db_id, 0,
								 AccessExclusiveLock);
}
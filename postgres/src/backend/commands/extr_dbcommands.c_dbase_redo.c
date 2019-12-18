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
struct TYPE_3__ {int /*<<< orphan*/  db_id; int /*<<< orphan*/  tablespace_id; } ;
typedef  TYPE_1__ xl_dbase_drop_rec ;
struct TYPE_4__ {int /*<<< orphan*/  src_db_id; int /*<<< orphan*/  tablespace_id; int /*<<< orphan*/  db_id; int /*<<< orphan*/  src_tablespace_id; } ;
typedef  TYPE_2__ xl_dbase_create_rec ;
typedef  scalar_t__ uint8 ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  XLogReaderState ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatabaseRelationId ; 
 int /*<<< orphan*/  DropDatabaseBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlushDatabaseBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ForgetDatabaseSyncRequests (int /*<<< orphan*/ ) ; 
 char* GetDatabasePath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ InHotStandby ; 
 int /*<<< orphan*/  LockSharedObjectForSession (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  ReplicationSlotsDropDBSlots (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResolveRecoveryConflictWithDatabase (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockSharedObjectForSession (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 scalar_t__ XLOG_DBASE_CREATE ; 
 scalar_t__ XLOG_DBASE_DROP ; 
 scalar_t__ XLR_INFO_MASK ; 
 int /*<<< orphan*/  XLogDropDatabase (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogRecGetData (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecHasAnyBlockRefs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copydir (char*,char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  rmtree (char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 

void
dbase_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	/* Backup blocks are not used in dbase records */
	Assert(!XLogRecHasAnyBlockRefs(record));

	if (info == XLOG_DBASE_CREATE)
	{
		xl_dbase_create_rec *xlrec = (xl_dbase_create_rec *) XLogRecGetData(record);
		char	   *src_path;
		char	   *dst_path;
		struct stat st;

		src_path = GetDatabasePath(xlrec->src_db_id, xlrec->src_tablespace_id);
		dst_path = GetDatabasePath(xlrec->db_id, xlrec->tablespace_id);

		/*
		 * Our theory for replaying a CREATE is to forcibly drop the target
		 * subdirectory if present, then re-copy the source data. This may be
		 * more work than needed, but it is simple to implement.
		 */
		if (stat(dst_path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			if (!rmtree(dst_path, true))
				/* If this failed, copydir() below is going to error. */
				ereport(WARNING,
						(errmsg("some useless files may be left behind in old database directory \"%s\"",
								dst_path)));
		}

		/*
		 * Force dirty buffers out to disk, to ensure source database is
		 * up-to-date for the copy.
		 */
		FlushDatabaseBuffers(xlrec->src_db_id);

		/*
		 * Copy this subdirectory to the new location
		 *
		 * We don't need to copy subdirectories
		 */
		copydir(src_path, dst_path, false);
	}
	else if (info == XLOG_DBASE_DROP)
	{
		xl_dbase_drop_rec *xlrec = (xl_dbase_drop_rec *) XLogRecGetData(record);
		char	   *dst_path;

		dst_path = GetDatabasePath(xlrec->db_id, xlrec->tablespace_id);

		if (InHotStandby)
		{
			/*
			 * Lock database while we resolve conflicts to ensure that
			 * InitPostgres() cannot fully re-execute concurrently. This
			 * avoids backends re-connecting automatically to same database,
			 * which can happen in some cases.
			 *
			 * This will lock out walsenders trying to connect to db-specific
			 * slots for logical decoding too, so it's safe for us to drop
			 * slots.
			 */
			LockSharedObjectForSession(DatabaseRelationId, xlrec->db_id, 0, AccessExclusiveLock);
			ResolveRecoveryConflictWithDatabase(xlrec->db_id);
		}

		/* Drop any database-specific replication slots */
		ReplicationSlotsDropDBSlots(xlrec->db_id);

		/* Drop pages for this database that are in the shared buffer cache */
		DropDatabaseBuffers(xlrec->db_id);

		/* Also, clean out any fsync requests that might be pending in md.c */
		ForgetDatabaseSyncRequests(xlrec->db_id);

		/* Clean out the xlog relcache too */
		XLogDropDatabase(xlrec->db_id);

		/* And remove the physical files */
		if (!rmtree(dst_path, true))
			ereport(WARNING,
					(errmsg("some useless files may be left behind in old database directory \"%s\"",
							dst_path)));

		if (InHotStandby)
		{
			/*
			 * Release locks prior to commit. XXX There is a race condition
			 * here that may allow backends to reconnect, but the window for
			 * this is small because the gap between here and commit is mostly
			 * fairly small and it is unlikely that people will be dropping
			 * databases that we are trying to connect to anyway.
			 */
			UnlockSharedObjectForSession(DatabaseRelationId, xlrec->db_id, 0, AccessExclusiveLock);
		}
	}
	else
		elog(PANIC, "dbase_redo: unknown op code %u", info);
}
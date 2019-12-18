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
typedef  int uint64 ;
typedef  int uint32 ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  path ;
typedef  scalar_t__ XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char*) ; 
 scalar_t__ CloseTransientFile (int) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 scalar_t__ GetRedoRecPtr () ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LOGICAL_REWRITE_FORMAT ; 
 int /*<<< orphan*/  MAXPGPATH ; 
 int O_RDWR ; 
 int OpenTransientFile (char*,int) ; 
 int PG_BINARY ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ReplicationSlotsComputeLogicalRestartLSN () ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_LOGICAL_REWRITE_CHECKPOINT_SYNC ; 
 int /*<<< orphan*/  data_sync_elevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ pg_fsync (int) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int sscanf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ unlink (char*) ; 

void
CheckPointLogicalRewriteHeap(void)
{
	XLogRecPtr	cutoff;
	XLogRecPtr	redo;
	DIR		   *mappings_dir;
	struct dirent *mapping_de;
	char		path[MAXPGPATH + 20];

	/*
	 * We start of with a minimum of the last redo pointer. No new decoding
	 * slot will start before that, so that's a safe upper bound for removal.
	 */
	redo = GetRedoRecPtr();

	/* now check for the restart ptrs from existing slots */
	cutoff = ReplicationSlotsComputeLogicalRestartLSN();

	/* don't start earlier than the restart lsn */
	if (cutoff != InvalidXLogRecPtr && redo < cutoff)
		cutoff = redo;

	mappings_dir = AllocateDir("pg_logical/mappings");
	while ((mapping_de = ReadDir(mappings_dir, "pg_logical/mappings")) != NULL)
	{
		struct stat statbuf;
		Oid			dboid;
		Oid			relid;
		XLogRecPtr	lsn;
		TransactionId rewrite_xid;
		TransactionId create_xid;
		uint32		hi,
					lo;

		if (strcmp(mapping_de->d_name, ".") == 0 ||
			strcmp(mapping_de->d_name, "..") == 0)
			continue;

		snprintf(path, sizeof(path), "pg_logical/mappings/%s", mapping_de->d_name);
		if (lstat(path, &statbuf) == 0 && !S_ISREG(statbuf.st_mode))
			continue;

		/* Skip over files that cannot be ours. */
		if (strncmp(mapping_de->d_name, "map-", 4) != 0)
			continue;

		if (sscanf(mapping_de->d_name, LOGICAL_REWRITE_FORMAT,
				   &dboid, &relid, &hi, &lo, &rewrite_xid, &create_xid) != 6)
			elog(ERROR, "could not parse filename \"%s\"", mapping_de->d_name);

		lsn = ((uint64) hi) << 32 | lo;

		if (lsn < cutoff || cutoff == InvalidXLogRecPtr)
		{
			elog(DEBUG1, "removing logical rewrite file \"%s\"", path);
			if (unlink(path) < 0)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not remove file \"%s\": %m", path)));
		}
		else
		{
			/* on some operating systems fsyncing a file requires O_RDWR */
			int			fd = OpenTransientFile(path, O_RDWR | PG_BINARY);

			/*
			 * The file cannot vanish due to concurrency since this function
			 * is the only one removing logical mappings and it's run while
			 * CheckpointLock is held exclusively.
			 */
			if (fd < 0)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not open file \"%s\": %m", path)));

			/*
			 * We could try to avoid fsyncing files that either haven't
			 * changed or have only been created since the checkpoint's start,
			 * but it's currently not deemed worth the effort.
			 */
			pgstat_report_wait_start(WAIT_EVENT_LOGICAL_REWRITE_CHECKPOINT_SYNC);
			if (pg_fsync(fd) != 0)
				ereport(data_sync_elevel(ERROR),
						(errcode_for_file_access(),
						 errmsg("could not fsync file \"%s\": %m", path)));
			pgstat_report_wait_end();

			if (CloseTransientFile(fd) != 0)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not close file \"%s\": %m", path)));
		}
	}
	FreeDir(mappings_dir);
}
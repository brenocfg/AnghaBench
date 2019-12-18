#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  int uint32 ;
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  strfbuf ;
typedef  int /*<<< orphan*/  startpoint ;
typedef  scalar_t__ pg_time_t ;
typedef  int /*<<< orphan*/  XLogSegNo ;
typedef  scalar_t__ XLogRecPtr ;
typedef  int TimeLineID ;
struct TYPE_6__ {scalar_t__ minRecoveryPoint; int minRecoveryPointTLI; } ;
struct TYPE_4__ {scalar_t__ exclusiveBackupState; scalar_t__ nonExclusiveBackups; int forcePageWrites; } ;
struct TYPE_5__ {scalar_t__ lastFpwDisableRecPtr; int /*<<< orphan*/  info_lck; TYPE_1__ Insert; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char*,char*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 char* BACKUP_LABEL_FILE ; 
 int /*<<< orphan*/  BackupHistoryFileName (char*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BackupHistoryFilePath (char*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ BoolGetDatum (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CleanupBackupHistory () ; 
 TYPE_3__* ControlFile ; 
 int /*<<< orphan*/  ControlFileLock ; 
 int /*<<< orphan*/  DEBUG1 ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ EXCLUSIVE_BACKUP_IN_PROGRESS ; 
 scalar_t__ EXCLUSIVE_BACKUP_NONE ; 
 scalar_t__ EXCLUSIVE_BACKUP_STOPPING ; 
 scalar_t__ FreeFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int MAXFNAMELEN ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  PG_END_ENSURE_ERROR_CLEANUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_ENSURE_ERROR_CLEANUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RM_XLOG_ID ; 
 int RecoveryInProgress () ; 
 int /*<<< orphan*/  RequestXLogSwitch (int) ; 
 int /*<<< orphan*/  SESSION_BACKUP_NONE ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 char* TABLESPACE_MAP ; 
 int ThisTimeLineID ; 
 int /*<<< orphan*/  WALInsertLockAcquireExclusive () ; 
 int /*<<< orphan*/  WALInsertLockRelease () ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XLByteToPrevSeg (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLByteToSeg (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_BACKUP_END ; 
 scalar_t__ XLogArchiveIsBusy (char*) ; 
 scalar_t__ XLogArchivingActive () ; 
 scalar_t__ XLogArchivingAlways () ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 TYPE_2__* XLogCtl ; 
 int /*<<< orphan*/  XLogFileName (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogIsNeeded () ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  durable_unlink (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ errno ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_timezone ; 
 char* palloc (int) ; 
 int /*<<< orphan*/  pg_localtime (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_stop_backup_callback ; 
 int /*<<< orphan*/  pg_strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 int /*<<< orphan*/  sessionBackupState ; 
 int sscanf (char*,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strstr (char*,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wal_segment_size ; 

XLogRecPtr
do_pg_stop_backup(char *labelfile, bool waitforarchive, TimeLineID *stoptli_p)
{
	bool		exclusive = (labelfile == NULL);
	bool		backup_started_in_recovery = false;
	XLogRecPtr	startpoint;
	XLogRecPtr	stoppoint;
	TimeLineID	stoptli;
	pg_time_t	stamp_time;
	char		strfbuf[128];
	char		histfilepath[MAXPGPATH];
	char		startxlogfilename[MAXFNAMELEN];
	char		stopxlogfilename[MAXFNAMELEN];
	char		lastxlogfilename[MAXFNAMELEN];
	char		histfilename[MAXFNAMELEN];
	char		backupfrom[20];
	XLogSegNo	_logSegNo;
	FILE	   *lfp;
	FILE	   *fp;
	char		ch;
	int			seconds_before_warning;
	int			waits = 0;
	bool		reported_waiting = false;
	char	   *remaining;
	char	   *ptr;
	uint32		hi,
				lo;

	backup_started_in_recovery = RecoveryInProgress();

	/*
	 * Currently only non-exclusive backup can be taken during recovery.
	 */
	if (backup_started_in_recovery && exclusive)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("recovery is in progress"),
				 errhint("WAL control functions cannot be executed during recovery.")));

	/*
	 * During recovery, we don't need to check WAL level. Because, if WAL
	 * level is not sufficient, it's impossible to get here during recovery.
	 */
	if (!backup_started_in_recovery && !XLogIsNeeded())
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("WAL level not sufficient for making an online backup"),
				 errhint("wal_level must be set to \"replica\" or \"logical\" at server start.")));

	if (exclusive)
	{
		/*
		 * At first, mark that we're now stopping an exclusive backup, to
		 * ensure that there are no other sessions currently running
		 * pg_start_backup() or pg_stop_backup().
		 */
		WALInsertLockAcquireExclusive();
		if (XLogCtl->Insert.exclusiveBackupState != EXCLUSIVE_BACKUP_IN_PROGRESS)
		{
			WALInsertLockRelease();
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("exclusive backup not in progress")));
		}
		XLogCtl->Insert.exclusiveBackupState = EXCLUSIVE_BACKUP_STOPPING;
		WALInsertLockRelease();

		/*
		 * Remove backup_label. In case of failure, the state for an exclusive
		 * backup is switched back to in-progress.
		 */
		PG_ENSURE_ERROR_CLEANUP(pg_stop_backup_callback, (Datum) BoolGetDatum(exclusive));
		{
			/*
			 * Read the existing label file into memory.
			 */
			struct stat statbuf;
			int			r;

			if (stat(BACKUP_LABEL_FILE, &statbuf))
			{
				/* should not happen per the upper checks */
				if (errno != ENOENT)
					ereport(ERROR,
							(errcode_for_file_access(),
							 errmsg("could not stat file \"%s\": %m",
									BACKUP_LABEL_FILE)));
				ereport(ERROR,
						(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
						 errmsg("a backup is not in progress")));
			}

			lfp = AllocateFile(BACKUP_LABEL_FILE, "r");
			if (!lfp)
			{
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not read file \"%s\": %m",
								BACKUP_LABEL_FILE)));
			}
			labelfile = palloc(statbuf.st_size + 1);
			r = fread(labelfile, statbuf.st_size, 1, lfp);
			labelfile[statbuf.st_size] = '\0';

			/*
			 * Close and remove the backup label file
			 */
			if (r != 1 || ferror(lfp) || FreeFile(lfp))
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not read file \"%s\": %m",
								BACKUP_LABEL_FILE)));
			durable_unlink(BACKUP_LABEL_FILE, ERROR);

			/*
			 * Remove tablespace_map file if present, it is created only if
			 * there are tablespaces.
			 */
			durable_unlink(TABLESPACE_MAP, DEBUG1);
		}
		PG_END_ENSURE_ERROR_CLEANUP(pg_stop_backup_callback, (Datum) BoolGetDatum(exclusive));
	}

	/*
	 * OK to update backup counters, forcePageWrites and session-level lock.
	 *
	 * Note that CHECK_FOR_INTERRUPTS() must not occur while updating them.
	 * Otherwise they can be updated inconsistently, and which might cause
	 * do_pg_abort_backup() to fail.
	 */
	WALInsertLockAcquireExclusive();
	if (exclusive)
	{
		XLogCtl->Insert.exclusiveBackupState = EXCLUSIVE_BACKUP_NONE;
	}
	else
	{
		/*
		 * The user-visible pg_start/stop_backup() functions that operate on
		 * exclusive backups can be called at any time, but for non-exclusive
		 * backups, it is expected that each do_pg_start_backup() call is
		 * matched by exactly one do_pg_stop_backup() call.
		 */
		Assert(XLogCtl->Insert.nonExclusiveBackups > 0);
		XLogCtl->Insert.nonExclusiveBackups--;
	}

	if (XLogCtl->Insert.exclusiveBackupState == EXCLUSIVE_BACKUP_NONE &&
		XLogCtl->Insert.nonExclusiveBackups == 0)
	{
		XLogCtl->Insert.forcePageWrites = false;
	}

	/*
	 * Clean up session-level lock.
	 *
	 * You might think that WALInsertLockRelease() can be called before
	 * cleaning up session-level lock because session-level lock doesn't need
	 * to be protected with WAL insertion lock. But since
	 * CHECK_FOR_INTERRUPTS() can occur in it, session-level lock must be
	 * cleaned up before it.
	 */
	sessionBackupState = SESSION_BACKUP_NONE;

	WALInsertLockRelease();

	/*
	 * Read and parse the START WAL LOCATION line (this code is pretty crude,
	 * but we are not expecting any variability in the file format).
	 */
	if (sscanf(labelfile, "START WAL LOCATION: %X/%X (file %24s)%c",
			   &hi, &lo, startxlogfilename,
			   &ch) != 4 || ch != '\n')
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("invalid data in file \"%s\"", BACKUP_LABEL_FILE)));
	startpoint = ((uint64) hi) << 32 | lo;
	remaining = strchr(labelfile, '\n') + 1;	/* %n is not portable enough */

	/*
	 * Parse the BACKUP FROM line. If we are taking an online backup from the
	 * standby, we confirm that the standby has not been promoted during the
	 * backup.
	 */
	ptr = strstr(remaining, "BACKUP FROM:");
	if (!ptr || sscanf(ptr, "BACKUP FROM: %19s\n", backupfrom) != 1)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("invalid data in file \"%s\"", BACKUP_LABEL_FILE)));
	if (strcmp(backupfrom, "standby") == 0 && !backup_started_in_recovery)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("the standby was promoted during online backup"),
				 errhint("This means that the backup being taken is corrupt "
						 "and should not be used. "
						 "Try taking another online backup.")));

	/*
	 * During recovery, we don't write an end-of-backup record. We assume that
	 * pg_control was backed up last and its minimum recovery point can be
	 * available as the backup end location. Since we don't have an
	 * end-of-backup record, we use the pg_control value to check whether
	 * we've reached the end of backup when starting recovery from this
	 * backup. We have no way of checking if pg_control wasn't backed up last
	 * however.
	 *
	 * We don't force a switch to new WAL file but it is still possible to
	 * wait for all the required files to be archived if waitforarchive is
	 * true. This is okay if we use the backup to start a standby and fetch
	 * the missing WAL using streaming replication. But in the case of an
	 * archive recovery, a user should set waitforarchive to true and wait for
	 * them to be archived to ensure that all the required files are
	 * available.
	 *
	 * We return the current minimum recovery point as the backup end
	 * location. Note that it can be greater than the exact backup end
	 * location if the minimum recovery point is updated after the backup of
	 * pg_control. This is harmless for current uses.
	 *
	 * XXX currently a backup history file is for informational and debug
	 * purposes only. It's not essential for an online backup. Furthermore,
	 * even if it's created, it will not be archived during recovery because
	 * an archiver is not invoked. So it doesn't seem worthwhile to write a
	 * backup history file during recovery.
	 */
	if (backup_started_in_recovery)
	{
		XLogRecPtr	recptr;

		/*
		 * Check to see if all WAL replayed during online backup contain
		 * full-page writes.
		 */
		SpinLockAcquire(&XLogCtl->info_lck);
		recptr = XLogCtl->lastFpwDisableRecPtr;
		SpinLockRelease(&XLogCtl->info_lck);

		if (startpoint <= recptr)
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("WAL generated with full_page_writes=off was replayed "
							"during online backup"),
					 errhint("This means that the backup being taken on the standby "
							 "is corrupt and should not be used. "
							 "Enable full_page_writes and run CHECKPOINT on the master, "
							 "and then try an online backup again.")));


		LWLockAcquire(ControlFileLock, LW_SHARED);
		stoppoint = ControlFile->minRecoveryPoint;
		stoptli = ControlFile->minRecoveryPointTLI;
		LWLockRelease(ControlFileLock);
	}
	else
	{
		/*
		 * Write the backup-end xlog record
		 */
		XLogBeginInsert();
		XLogRegisterData((char *) (&startpoint), sizeof(startpoint));
		stoppoint = XLogInsert(RM_XLOG_ID, XLOG_BACKUP_END);
		stoptli = ThisTimeLineID;

		/*
		 * Force a switch to a new xlog segment file, so that the backup is
		 * valid as soon as archiver moves out the current segment file.
		 */
		RequestXLogSwitch(false);

		XLByteToPrevSeg(stoppoint, _logSegNo, wal_segment_size);
		XLogFileName(stopxlogfilename, stoptli, _logSegNo, wal_segment_size);

		/* Use the log timezone here, not the session timezone */
		stamp_time = (pg_time_t) time(NULL);
		pg_strftime(strfbuf, sizeof(strfbuf),
					"%Y-%m-%d %H:%M:%S %Z",
					pg_localtime(&stamp_time, log_timezone));

		/*
		 * Write the backup history file
		 */
		XLByteToSeg(startpoint, _logSegNo, wal_segment_size);
		BackupHistoryFilePath(histfilepath, stoptli, _logSegNo,
							  startpoint, wal_segment_size);
		fp = AllocateFile(histfilepath, "w");
		if (!fp)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not create file \"%s\": %m",
							histfilepath)));
		fprintf(fp, "START WAL LOCATION: %X/%X (file %s)\n",
				(uint32) (startpoint >> 32), (uint32) startpoint, startxlogfilename);
		fprintf(fp, "STOP WAL LOCATION: %X/%X (file %s)\n",
				(uint32) (stoppoint >> 32), (uint32) stoppoint, stopxlogfilename);

		/*
		 * Transfer remaining lines including label and start timeline to
		 * history file.
		 */
		fprintf(fp, "%s", remaining);
		fprintf(fp, "STOP TIME: %s\n", strfbuf);
		fprintf(fp, "STOP TIMELINE: %u\n", stoptli);
		if (fflush(fp) || ferror(fp) || FreeFile(fp))
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not write file \"%s\": %m",
							histfilepath)));

		/*
		 * Clean out any no-longer-needed history files.  As a side effect,
		 * this will post a .ready file for the newly created history file,
		 * notifying the archiver that history file may be archived
		 * immediately.
		 */
		CleanupBackupHistory();
	}

	/*
	 * If archiving is enabled, wait for all the required WAL files to be
	 * archived before returning. If archiving isn't enabled, the required WAL
	 * needs to be transported via streaming replication (hopefully with
	 * wal_keep_segments set high enough), or some more exotic mechanism like
	 * polling and copying files from pg_wal with script. We have no knowledge
	 * of those mechanisms, so it's up to the user to ensure that he gets all
	 * the required WAL.
	 *
	 * We wait until both the last WAL file filled during backup and the
	 * history file have been archived, and assume that the alphabetic sorting
	 * property of the WAL files ensures any earlier WAL files are safely
	 * archived as well.
	 *
	 * We wait forever, since archive_command is supposed to work and we
	 * assume the admin wanted his backup to work completely. If you don't
	 * wish to wait, then either waitforarchive should be passed in as false,
	 * or you can set statement_timeout.  Also, some notices are issued to
	 * clue in anyone who might be doing this interactively.
	 */

	if (waitforarchive &&
		((!backup_started_in_recovery && XLogArchivingActive()) ||
		 (backup_started_in_recovery && XLogArchivingAlways())))
	{
		XLByteToPrevSeg(stoppoint, _logSegNo, wal_segment_size);
		XLogFileName(lastxlogfilename, stoptli, _logSegNo, wal_segment_size);

		XLByteToSeg(startpoint, _logSegNo, wal_segment_size);
		BackupHistoryFileName(histfilename, stoptli, _logSegNo,
							  startpoint, wal_segment_size);

		seconds_before_warning = 60;
		waits = 0;

		while (XLogArchiveIsBusy(lastxlogfilename) ||
			   XLogArchiveIsBusy(histfilename))
		{
			CHECK_FOR_INTERRUPTS();

			if (!reported_waiting && waits > 5)
			{
				ereport(NOTICE,
						(errmsg("base backup done, waiting for required WAL segments to be archived")));
				reported_waiting = true;
			}

			pg_usleep(1000000L);

			if (++waits >= seconds_before_warning)
			{
				seconds_before_warning *= 2;	/* This wraps in >10 years... */
				ereport(WARNING,
						(errmsg("still waiting for all required WAL segments to be archived (%d seconds elapsed)",
								waits),
						 errhint("Check that your archive_command is executing properly.  "
								 "You can safely cancel this backup, "
								 "but the database backup will not be usable without all the WAL segments.")));
			}
		}

		ereport(NOTICE,
				(errmsg("all required WAL segments have been archived")));
	}
	else if (waitforarchive)
		ereport(NOTICE,
				(errmsg("WAL archiving is not enabled; you must ensure that all required WAL segments are copied through other means to complete the backup")));

	/*
	 * We're done.  As a convenience, return the ending WAL location.
	 */
	if (stoptli_p)
		*stoptli_p = stoptli;
	return stoppoint;
}
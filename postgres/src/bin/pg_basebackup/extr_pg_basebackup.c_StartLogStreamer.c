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
typedef  int uint64 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  statusdir ;
struct TYPE_5__ {int timeline; char* sysidentifier; int startptr; char* xlog; int /*<<< orphan*/  bgconn; } ;
typedef  TYPE_1__ logstreamer_param ;

/* Variables and functions */
 int /*<<< orphan*/  CreateReplicationSlot (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int,int,int) ; 
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  GetConnection () ; 
 int LogStreamerMain (TYPE_1__*) ; 
 int MAXPGPATH ; 
 scalar_t__ MINIMUM_VERSION_FOR_PG_WAL ; 
 scalar_t__ MINIMUM_VERSION_FOR_TEMP_SLOTS ; 
 scalar_t__ PQbackendPID (int /*<<< orphan*/ ) ; 
 scalar_t__ PQserverVersion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalSegSz ; 
 scalar_t__ XLogSegmentOffset (int,int /*<<< orphan*/ ) ; 
 scalar_t__ _beginthreadex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 char* basedir ; 
 scalar_t__ bgchild ; 
 int /*<<< orphan*/  bgpipe ; 
 int /*<<< orphan*/  conn ; 
 scalar_t__ create_slot ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 char format ; 
 int /*<<< orphan*/  kill_bgchild_atexit ; 
 int /*<<< orphan*/  pg_dir_create_mode ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  pg_log_info (char*,scalar_t__) ; 
 TYPE_1__* pg_malloc0 (int) ; 
 scalar_t__ pg_mkdir_p (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe (int /*<<< orphan*/ ) ; 
 scalar_t__ psprintf (char*,int) ; 
 scalar_t__ replication_slot ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int sscanf (char*,char*,int*,int*) ; 
 int temp_replication_slot ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
StartLogStreamer(char *startpos, uint32 timeline, char *sysidentifier)
{
	logstreamer_param *param;
	uint32		hi,
				lo;
	char		statusdir[MAXPGPATH];

	param = pg_malloc0(sizeof(logstreamer_param));
	param->timeline = timeline;
	param->sysidentifier = sysidentifier;

	/* Convert the starting position */
	if (sscanf(startpos, "%X/%X", &hi, &lo) != 2)
	{
		pg_log_error("could not parse write-ahead log location \"%s\"",
					 startpos);
		exit(1);
	}
	param->startptr = ((uint64) hi) << 32 | lo;
	/* Round off to even segment position */
	param->startptr -= XLogSegmentOffset(param->startptr, WalSegSz);

#ifndef WIN32
	/* Create our background pipe */
	if (pipe(bgpipe) < 0)
	{
		pg_log_error("could not create pipe for background process: %m");
		exit(1);
	}
#endif

	/* Get a second connection */
	param->bgconn = GetConnection();
	if (!param->bgconn)
		/* Error message already written in GetConnection() */
		exit(1);

	/* In post-10 cluster, pg_xlog has been renamed to pg_wal */
	snprintf(param->xlog, sizeof(param->xlog), "%s/%s",
			 basedir,
			 PQserverVersion(conn) < MINIMUM_VERSION_FOR_PG_WAL ?
			 "pg_xlog" : "pg_wal");

	/* Temporary replication slots are only supported in 10 and newer */
	if (PQserverVersion(conn) < MINIMUM_VERSION_FOR_TEMP_SLOTS)
		temp_replication_slot = false;

	/*
	 * Create replication slot if requested
	 */
	if (temp_replication_slot && !replication_slot)
		replication_slot = psprintf("pg_basebackup_%d", (int) PQbackendPID(param->bgconn));
	if (temp_replication_slot || create_slot)
	{
		if (!CreateReplicationSlot(param->bgconn, replication_slot, NULL,
								   temp_replication_slot, true, true, false))
			exit(1);

		if (verbose)
		{
			if (temp_replication_slot)
				pg_log_info("created temporary replication slot \"%s\"",
							replication_slot);
			else
				pg_log_info("created replication slot \"%s\"",
							replication_slot);
		}
	}

	if (format == 'p')
	{
		/*
		 * Create pg_wal/archive_status or pg_xlog/archive_status (and thus
		 * pg_wal or pg_xlog) depending on the target server so we can write
		 * to basedir/pg_wal or basedir/pg_xlog as the directory entry in the
		 * tar file may arrive later.
		 */
		snprintf(statusdir, sizeof(statusdir), "%s/%s/archive_status",
				 basedir,
				 PQserverVersion(conn) < MINIMUM_VERSION_FOR_PG_WAL ?
				 "pg_xlog" : "pg_wal");

		if (pg_mkdir_p(statusdir, pg_dir_create_mode) != 0 && errno != EEXIST)
		{
			pg_log_error("could not create directory \"%s\": %m", statusdir);
			exit(1);
		}
	}

	/*
	 * Start a child process and tell it to start streaming. On Unix, this is
	 * a fork(). On Windows, we create a thread.
	 */
#ifndef WIN32
	bgchild = fork();
	if (bgchild == 0)
	{
		/* in child process */
		exit(LogStreamerMain(param));
	}
	else if (bgchild < 0)
	{
		pg_log_error("could not create background process: %m");
		exit(1);
	}

	/*
	 * Else we are in the parent process and all is well.
	 */
	atexit(kill_bgchild_atexit);
#else							/* WIN32 */
	bgchild = _beginthreadex(NULL, 0, (void *) LogStreamerMain, param, 0, NULL);
	if (bgchild == 0)
	{
		pg_log_error("could not create background thread: %m");
		exit(1);
	}
#endif
}
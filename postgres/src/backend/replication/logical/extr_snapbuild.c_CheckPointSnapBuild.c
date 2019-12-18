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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char*) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 scalar_t__ GetRedoRecPtr () ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MAXPGPATH ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ReplicationSlotsComputeLogicalRestartLSN () ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int sscanf (char*,char*,int*,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ unlink (char*) ; 

void
CheckPointSnapBuild(void)
{
	XLogRecPtr	cutoff;
	XLogRecPtr	redo;
	DIR		   *snap_dir;
	struct dirent *snap_de;
	char		path[MAXPGPATH + 21];

	/*
	 * We start off with a minimum of the last redo pointer. No new
	 * replication slot will start before that, so that's a safe upper bound
	 * for removal.
	 */
	redo = GetRedoRecPtr();

	/* now check for the restart ptrs from existing slots */
	cutoff = ReplicationSlotsComputeLogicalRestartLSN();

	/* don't start earlier than the restart lsn */
	if (redo < cutoff)
		cutoff = redo;

	snap_dir = AllocateDir("pg_logical/snapshots");
	while ((snap_de = ReadDir(snap_dir, "pg_logical/snapshots")) != NULL)
	{
		uint32		hi;
		uint32		lo;
		XLogRecPtr	lsn;
		struct stat statbuf;

		if (strcmp(snap_de->d_name, ".") == 0 ||
			strcmp(snap_de->d_name, "..") == 0)
			continue;

		snprintf(path, sizeof(path), "pg_logical/snapshots/%s", snap_de->d_name);

		if (lstat(path, &statbuf) == 0 && !S_ISREG(statbuf.st_mode))
		{
			elog(DEBUG1, "only regular files expected: %s", path);
			continue;
		}

		/*
		 * temporary filenames from SnapBuildSerialize() include the LSN and
		 * everything but are postfixed by .$pid.tmp. We can just remove them
		 * the same as other files because there can be none that are
		 * currently being written that are older than cutoff.
		 *
		 * We just log a message if a file doesn't fit the pattern, it's
		 * probably some editors lock/state file or similar...
		 */
		if (sscanf(snap_de->d_name, "%X-%X.snap", &hi, &lo) != 2)
		{
			ereport(LOG,
					(errmsg("could not parse file name \"%s\"", path)));
			continue;
		}

		lsn = ((uint64) hi) << 32 | lo;

		/* check whether we still need it */
		if (lsn < cutoff || cutoff == InvalidXLogRecPtr)
		{
			elog(DEBUG1, "removing snapbuild snapshot %s", path);

			/*
			 * It's not particularly harmful, though strange, if we can't
			 * remove the file here. Don't prevent the checkpoint from
			 * completing, that'd be a cure worse than the disease.
			 */
			if (unlink(path) < 0)
			{
				ereport(LOG,
						(errcode_for_file_access(),
						 errmsg("could not remove file \"%s\": %m",
								path)));
				continue;
			}
		}
	}
	FreeDir(snap_dir);
}
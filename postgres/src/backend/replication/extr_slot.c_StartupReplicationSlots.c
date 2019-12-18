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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char*) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAXPGPATH ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ReplicationSlotsComputeRequiredLSN () ; 
 int /*<<< orphan*/  ReplicationSlotsComputeRequiredXmin (int) ; 
 int /*<<< orphan*/  RestoreSlotFromDisk (char*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  fsync_fname (char*,int) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ max_replication_slots ; 
 scalar_t__ pg_str_endswith (char*,char*) ; 
 int /*<<< orphan*/  rmtree (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

void
StartupReplicationSlots(void)
{
	DIR		   *replication_dir;
	struct dirent *replication_de;

	elog(DEBUG1, "starting up replication slots");

	/* restore all slots by iterating over all on-disk entries */
	replication_dir = AllocateDir("pg_replslot");
	while ((replication_de = ReadDir(replication_dir, "pg_replslot")) != NULL)
	{
		struct stat statbuf;
		char		path[MAXPGPATH + 12];

		if (strcmp(replication_de->d_name, ".") == 0 ||
			strcmp(replication_de->d_name, "..") == 0)
			continue;

		snprintf(path, sizeof(path), "pg_replslot/%s", replication_de->d_name);

		/* we're only creating directories here, skip if it's not our's */
		if (lstat(path, &statbuf) == 0 && !S_ISDIR(statbuf.st_mode))
			continue;

		/* we crashed while a slot was being setup or deleted, clean up */
		if (pg_str_endswith(replication_de->d_name, ".tmp"))
		{
			if (!rmtree(path, true))
			{
				ereport(WARNING,
						(errmsg("could not remove directory \"%s\"",
								path)));
				continue;
			}
			fsync_fname("pg_replslot", true);
			continue;
		}

		/* looks like a slot in a normal state, restore */
		RestoreSlotFromDisk(replication_de->d_name);
	}
	FreeDir(replication_dir);

	/* currently no slots exist, we're done. */
	if (max_replication_slots <= 0)
		return;

	/* Now that we have recovered all the data, compute replication xmin */
	ReplicationSlotsComputeRequiredXmin(false);
	ReplicationSlotsComputeRequiredLSN();
}
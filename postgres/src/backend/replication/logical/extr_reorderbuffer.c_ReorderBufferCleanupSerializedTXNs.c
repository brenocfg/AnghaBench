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
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFO ; 
 int MAXPGPATH ; 
 struct dirent* ReadDirExtended (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*,char const*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static void
ReorderBufferCleanupSerializedTXNs(const char *slotname)
{
	DIR		   *spill_dir;
	struct dirent *spill_de;
	struct stat statbuf;
	char		path[MAXPGPATH * 2 + 12];

	sprintf(path, "pg_replslot/%s", slotname);

	/* we're only handling directories here, skip if it's not ours */
	if (lstat(path, &statbuf) == 0 && !S_ISDIR(statbuf.st_mode))
		return;

	spill_dir = AllocateDir(path);
	while ((spill_de = ReadDirExtended(spill_dir, path, INFO)) != NULL)
	{
		/* only look at names that can be ours */
		if (strncmp(spill_de->d_name, "xid", 3) == 0)
		{
			snprintf(path, sizeof(path),
					 "pg_replslot/%s/%s", slotname,
					 spill_de->d_name);

			if (unlink(path) != 0)
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not remove file \"%s\" during removal of pg_replslot/%s/xid*: %m",
								path, slotname)));
		}
	}
	FreeDir(spill_dir);
}
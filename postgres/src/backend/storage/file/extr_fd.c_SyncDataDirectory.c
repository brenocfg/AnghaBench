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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  LOG ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datadir_fsync_fname ; 
 int /*<<< orphan*/  enableFsync ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ pgwin32_is_junction (char*) ; 
 int /*<<< orphan*/  pre_sync_fname ; 
 int /*<<< orphan*/  walkdir (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
SyncDataDirectory(void)
{
	bool		xlog_is_symlink;

	/* We can skip this whole thing if fsync is disabled. */
	if (!enableFsync)
		return;

	/*
	 * If pg_wal is a symlink, we'll need to recurse into it separately,
	 * because the first walkdir below will ignore it.
	 */
	xlog_is_symlink = false;

#ifndef WIN32
	{
		struct stat st;

		if (lstat("pg_wal", &st) < 0)
			ereport(LOG,
					(errcode_for_file_access(),
					 errmsg("could not stat file \"%s\": %m",
							"pg_wal")));
		else if (S_ISLNK(st.st_mode))
			xlog_is_symlink = true;
	}
#else
	if (pgwin32_is_junction("pg_wal"))
		xlog_is_symlink = true;
#endif

	/*
	 * If possible, hint to the kernel that we're soon going to fsync the data
	 * directory and its contents.  Errors in this step are even less
	 * interesting than normal, so log them only at DEBUG1.
	 */
#ifdef PG_FLUSH_DATA_WORKS
	walkdir(".", pre_sync_fname, false, DEBUG1);
	if (xlog_is_symlink)
		walkdir("pg_wal", pre_sync_fname, false, DEBUG1);
	walkdir("pg_tblspc", pre_sync_fname, true, DEBUG1);
#endif

	/*
	 * Now we do the fsync()s in the same order.
	 *
	 * The main call ignores symlinks, so in addition to specially processing
	 * pg_wal if it's a symlink, pg_tblspc has to be visited separately with
	 * process_symlinks = true.  Note that if there are any plain directories
	 * in pg_tblspc, they'll get fsync'd twice.  That's not an expected case
	 * so we don't worry about optimizing it.
	 */
	walkdir(".", datadir_fsync_fname, false, LOG);
	if (xlog_is_symlink)
		walkdir("pg_wal", datadir_fsync_fname, false, LOG);
	walkdir("pg_tblspc", datadir_fsync_fname, true, LOG);
}
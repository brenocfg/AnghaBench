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
 int MAXPGPATH ; 
 int MINIMUM_VERSION_FOR_PG_WAL ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync_fname ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 scalar_t__ pgwin32_is_junction (char*) ; 
 int /*<<< orphan*/  pre_sync_fname ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  walkdir (char const*,int /*<<< orphan*/ ,int) ; 

void
fsync_pgdata(const char *pg_data,
			 int serverVersion)
{
	bool		xlog_is_symlink;
	char		pg_wal[MAXPGPATH];
	char		pg_tblspc[MAXPGPATH];

	/* handle renaming of pg_xlog to pg_wal in post-10 clusters */
	snprintf(pg_wal, MAXPGPATH, "%s/%s", pg_data,
			 serverVersion < MINIMUM_VERSION_FOR_PG_WAL ? "pg_xlog" : "pg_wal");
	snprintf(pg_tblspc, MAXPGPATH, "%s/pg_tblspc", pg_data);

	/*
	 * If pg_wal is a symlink, we'll need to recurse into it separately,
	 * because the first walkdir below will ignore it.
	 */
	xlog_is_symlink = false;

#ifndef WIN32
	{
		struct stat st;

		if (lstat(pg_wal, &st) < 0)
			pg_log_error("could not stat file \"%s\": %m", pg_wal);
		else if (S_ISLNK(st.st_mode))
			xlog_is_symlink = true;
	}
#else
	if (pgwin32_is_junction(pg_wal))
		xlog_is_symlink = true;
#endif

	/*
	 * If possible, hint to the kernel that we're soon going to fsync the data
	 * directory and its contents.
	 */
#ifdef PG_FLUSH_DATA_WORKS
	walkdir(pg_data, pre_sync_fname, false);
	if (xlog_is_symlink)
		walkdir(pg_wal, pre_sync_fname, false);
	walkdir(pg_tblspc, pre_sync_fname, true);
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
	walkdir(pg_data, fsync_fname, false);
	if (xlog_is_symlink)
		walkdir(pg_wal, fsync_fname, false);
	walkdir(pg_tblspc, fsync_fname, true);
}
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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  char* Oid ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TABLESPACE_VERSION_DIRECTORY ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  directory_is_empty (char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  get_parent_directory (char*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* psprintf (char*,char*,int /*<<< orphan*/ ) ; 
 char* pstrdup (char*) ; 
 scalar_t__ rmdir (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static bool
destroy_tablespace_directories(Oid tablespaceoid, bool redo)
{
	char	   *linkloc;
	char	   *linkloc_with_version_dir;
	DIR		   *dirdesc;
	struct dirent *de;
	char	   *subfile;
	struct stat st;

	linkloc_with_version_dir = psprintf("pg_tblspc/%u/%s", tablespaceoid,
										TABLESPACE_VERSION_DIRECTORY);

	/*
	 * Check if the tablespace still contains any files.  We try to rmdir each
	 * per-database directory we find in it.  rmdir failure implies there are
	 * still files in that subdirectory, so give up.  (We do not have to worry
	 * about undoing any already completed rmdirs, since the next attempt to
	 * use the tablespace from that database will simply recreate the
	 * subdirectory via TablespaceCreateDbspace.)
	 *
	 * Since we hold TablespaceCreateLock, no one else should be creating any
	 * fresh subdirectories in parallel. It is possible that new files are
	 * being created within subdirectories, though, so the rmdir call could
	 * fail.  Worst consequence is a less friendly error message.
	 *
	 * If redo is true then ENOENT is a likely outcome here, and we allow it
	 * to pass without comment.  In normal operation we still allow it, but
	 * with a warning.  This is because even though ProcessUtility disallows
	 * DROP TABLESPACE in a transaction block, it's possible that a previous
	 * DROP failed and rolled back after removing the tablespace directories
	 * and/or symlink.  We want to allow a new DROP attempt to succeed at
	 * removing the catalog entries (and symlink if still present), so we
	 * should not give a hard error here.
	 */
	dirdesc = AllocateDir(linkloc_with_version_dir);
	if (dirdesc == NULL)
	{
		if (errno == ENOENT)
		{
			if (!redo)
				ereport(WARNING,
						(errcode_for_file_access(),
						 errmsg("could not open directory \"%s\": %m",
								linkloc_with_version_dir)));
			/* The symlink might still exist, so go try to remove it */
			goto remove_symlink;
		}
		else if (redo)
		{
			/* in redo, just log other types of error */
			ereport(LOG,
					(errcode_for_file_access(),
					 errmsg("could not open directory \"%s\": %m",
							linkloc_with_version_dir)));
			pfree(linkloc_with_version_dir);
			return false;
		}
		/* else let ReadDir report the error */
	}

	while ((de = ReadDir(dirdesc, linkloc_with_version_dir)) != NULL)
	{
		if (strcmp(de->d_name, ".") == 0 ||
			strcmp(de->d_name, "..") == 0)
			continue;

		subfile = psprintf("%s/%s", linkloc_with_version_dir, de->d_name);

		/* This check is just to deliver a friendlier error message */
		if (!redo && !directory_is_empty(subfile))
		{
			FreeDir(dirdesc);
			pfree(subfile);
			pfree(linkloc_with_version_dir);
			return false;
		}

		/* remove empty directory */
		if (rmdir(subfile) < 0)
			ereport(redo ? LOG : ERROR,
					(errcode_for_file_access(),
					 errmsg("could not remove directory \"%s\": %m",
							subfile)));

		pfree(subfile);
	}

	FreeDir(dirdesc);

	/* remove version directory */
	if (rmdir(linkloc_with_version_dir) < 0)
	{
		ereport(redo ? LOG : ERROR,
				(errcode_for_file_access(),
				 errmsg("could not remove directory \"%s\": %m",
						linkloc_with_version_dir)));
		pfree(linkloc_with_version_dir);
		return false;
	}

	/*
	 * Try to remove the symlink.  We must however deal with the possibility
	 * that it's a directory instead of a symlink --- this could happen during
	 * WAL replay (see TablespaceCreateDbspace), and it is also the case on
	 * Windows where junction points lstat() as directories.
	 *
	 * Note: in the redo case, we'll return true if this final step fails;
	 * there's no point in retrying it.  Also, ENOENT should provoke no more
	 * than a warning.
	 */
remove_symlink:
	linkloc = pstrdup(linkloc_with_version_dir);
	get_parent_directory(linkloc);
	if (lstat(linkloc, &st) < 0)
	{
		int			saved_errno = errno;

		ereport(redo ? LOG : (saved_errno == ENOENT ? WARNING : ERROR),
				(errcode_for_file_access(),
				 errmsg("could not stat file \"%s\": %m",
						linkloc)));
	}
	else if (S_ISDIR(st.st_mode))
	{
		if (rmdir(linkloc) < 0)
		{
			int			saved_errno = errno;

			ereport(redo ? LOG : (saved_errno == ENOENT ? WARNING : ERROR),
					(errcode_for_file_access(),
					 errmsg("could not remove directory \"%s\": %m",
							linkloc)));
		}
	}
#ifdef S_ISLNK
	else if (S_ISLNK(st.st_mode))
	{
		if (unlink(linkloc) < 0)
		{
			int			saved_errno = errno;

			ereport(redo ? LOG : (saved_errno == ENOENT ? WARNING : ERROR),
					(errcode_for_file_access(),
					 errmsg("could not remove symbolic link \"%s\": %m",
							linkloc)));
		}
	}
#endif
	else
	{
		/* Refuse to remove anything that's not a directory or symlink */
		ereport(redo ? LOG : ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("\"%s\" is not a directory or symbolic link",
						linkloc)));
	}

	pfree(linkloc_with_version_dir);
	pfree(linkloc);

	return true;
}
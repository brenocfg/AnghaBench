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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GLOBALTABLESPACE_OID ; 
 char* GetDatabasePath (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ MakePGDirectory (char*) ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TablespaceCreateLock ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  get_parent_directory (char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* pstrdup (char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

void
TablespaceCreateDbspace(Oid spcNode, Oid dbNode, bool isRedo)
{
	struct stat st;
	char	   *dir;

	/*
	 * The global tablespace doesn't have per-database subdirectories, so
	 * nothing to do for it.
	 */
	if (spcNode == GLOBALTABLESPACE_OID)
		return;

	Assert(OidIsValid(spcNode));
	Assert(OidIsValid(dbNode));

	dir = GetDatabasePath(dbNode, spcNode);

	if (stat(dir, &st) < 0)
	{
		/* Directory does not exist? */
		if (errno == ENOENT)
		{
			/*
			 * Acquire TablespaceCreateLock to ensure that no DROP TABLESPACE
			 * or TablespaceCreateDbspace is running concurrently.
			 */
			LWLockAcquire(TablespaceCreateLock, LW_EXCLUSIVE);

			/*
			 * Recheck to see if someone created the directory while we were
			 * waiting for lock.
			 */
			if (stat(dir, &st) == 0 && S_ISDIR(st.st_mode))
			{
				/* Directory was created */
			}
			else
			{
				/* Directory creation failed? */
				if (MakePGDirectory(dir) < 0)
				{
					char	   *parentdir;

					/* Failure other than not exists or not in WAL replay? */
					if (errno != ENOENT || !isRedo)
						ereport(ERROR,
								(errcode_for_file_access(),
								 errmsg("could not create directory \"%s\": %m",
										dir)));

					/*
					 * Parent directories are missing during WAL replay, so
					 * continue by creating simple parent directories rather
					 * than a symlink.
					 */

					/* create two parents up if not exist */
					parentdir = pstrdup(dir);
					get_parent_directory(parentdir);
					get_parent_directory(parentdir);
					/* Can't create parent and it doesn't already exist? */
					if (MakePGDirectory(parentdir) < 0 && errno != EEXIST)
						ereport(ERROR,
								(errcode_for_file_access(),
								 errmsg("could not create directory \"%s\": %m",
										parentdir)));
					pfree(parentdir);

					/* create one parent up if not exist */
					parentdir = pstrdup(dir);
					get_parent_directory(parentdir);
					/* Can't create parent and it doesn't already exist? */
					if (MakePGDirectory(parentdir) < 0 && errno != EEXIST)
						ereport(ERROR,
								(errcode_for_file_access(),
								 errmsg("could not create directory \"%s\": %m",
										parentdir)));
					pfree(parentdir);

					/* Create database directory */
					if (MakePGDirectory(dir) < 0)
						ereport(ERROR,
								(errcode_for_file_access(),
								 errmsg("could not create directory \"%s\": %m",
										dir)));
				}
			}

			LWLockRelease(TablespaceCreateLock);
		}
		else
		{
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not stat directory \"%s\": %m", dir)));
		}
	}
	else
	{
		/* Is it not a directory? */
		if (!S_ISDIR(st.st_mode))
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("\"%s\" exists but is not a directory",
							dir)));
	}

	pfree(dir);
}
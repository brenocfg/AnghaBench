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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_IN_USE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_FILE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InRecovery ; 
 scalar_t__ MakePGDirectory (char*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TABLESPACE_VERSION_DIRECTORY ; 
 int /*<<< orphan*/  WARNING ; 
 scalar_t__ chmod (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pg_dir_create_mode ; 
 char* psprintf (char*,char const*,...) ; 
 int /*<<< orphan*/  remove_tablespace_symlink (char*) ; 
 int /*<<< orphan*/  rmtree (char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ symlink (char const*,char*) ; 

__attribute__((used)) static void
create_tablespace_directories(const char *location, const Oid tablespaceoid)
{
	char	   *linkloc;
	char	   *location_with_version_dir;
	struct stat st;

	linkloc = psprintf("pg_tblspc/%u", tablespaceoid);
	location_with_version_dir = psprintf("%s/%s", location,
										 TABLESPACE_VERSION_DIRECTORY);

	/*
	 * Attempt to coerce target directory to safe permissions.  If this fails,
	 * it doesn't exist or has the wrong owner.
	 */
	if (chmod(location, pg_dir_create_mode) != 0)
	{
		if (errno == ENOENT)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_FILE),
					 errmsg("directory \"%s\" does not exist", location),
					 InRecovery ? errhint("Create this directory for the tablespace before "
										  "restarting the server.") : 0));
		else
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not set permissions on directory \"%s\": %m",
							location)));
	}

	if (InRecovery)
	{
		/*
		 * Our theory for replaying a CREATE is to forcibly drop the target
		 * subdirectory if present, and then recreate it. This may be more
		 * work than needed, but it is simple to implement.
		 */
		if (stat(location_with_version_dir, &st) == 0 && S_ISDIR(st.st_mode))
		{
			if (!rmtree(location_with_version_dir, true))
				/* If this failed, MakePGDirectory() below is going to error. */
				ereport(WARNING,
						(errmsg("some useless files may be left behind in old database directory \"%s\"",
								location_with_version_dir)));
		}
	}

	/*
	 * The creation of the version directory prevents more than one tablespace
	 * in a single location.
	 */
	if (MakePGDirectory(location_with_version_dir) < 0)
	{
		if (errno == EEXIST)
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_IN_USE),
					 errmsg("directory \"%s\" already in use as a tablespace",
							location_with_version_dir)));
		else
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("could not create directory \"%s\": %m",
							location_with_version_dir)));
	}

	/*
	 * In recovery, remove old symlink, in case it points to the wrong place.
	 */
	if (InRecovery)
		remove_tablespace_symlink(linkloc);

	/*
	 * Create the symlink under PGDATA
	 */
	if (symlink(location, linkloc) < 0)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not create symbolic link \"%s\": %m",
						linkloc)));

	pfree(linkloc);
	pfree(location_with_version_dir);
}
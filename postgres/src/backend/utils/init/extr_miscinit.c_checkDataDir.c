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
struct stat {int st_mode; scalar_t__ st_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DataDir ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  FATAL ; 
 int PG_MODE_MASK_GROUP ; 
 int /*<<< orphan*/  S_ISDIR (int) ; 
 int /*<<< orphan*/  SetDataDirectoryCreatePerm (int) ; 
 int /*<<< orphan*/  ValidatePgVersion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_directory_mode ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  pg_dir_create_mode ; 
 int /*<<< orphan*/  pg_mode_mask ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 

void
checkDataDir(void)
{
	struct stat stat_buf;

	Assert(DataDir);

	if (stat(DataDir, &stat_buf) != 0)
	{
		if (errno == ENOENT)
			ereport(FATAL,
					(errcode_for_file_access(),
					 errmsg("data directory \"%s\" does not exist",
							DataDir)));
		else
			ereport(FATAL,
					(errcode_for_file_access(),
					 errmsg("could not read permissions of directory \"%s\": %m",
							DataDir)));
	}

	/* eventual chdir would fail anyway, but let's test ... */
	if (!S_ISDIR(stat_buf.st_mode))
		ereport(FATAL,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("specified data directory \"%s\" is not a directory",
						DataDir)));

	/*
	 * Check that the directory belongs to my userid; if not, reject.
	 *
	 * This check is an essential part of the interlock that prevents two
	 * postmasters from starting in the same directory (see CreateLockFile()).
	 * Do not remove or weaken it.
	 *
	 * XXX can we safely enable this check on Windows?
	 */
#if !defined(WIN32) && !defined(__CYGWIN__)
	if (stat_buf.st_uid != geteuid())
		ereport(FATAL,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("data directory \"%s\" has wrong ownership",
						DataDir),
				 errhint("The server must be started by the user that owns the data directory.")));
#endif

	/*
	 * Check if the directory has correct permissions.  If not, reject.
	 *
	 * Only two possible modes are allowed, 0700 and 0750.  The latter mode
	 * indicates that group read/execute should be allowed on all newly
	 * created files and directories.
	 *
	 * XXX temporarily suppress check when on Windows, because there may not
	 * be proper support for Unix-y file permissions.  Need to think of a
	 * reasonable check to apply on Windows.
	 */
#if !defined(WIN32) && !defined(__CYGWIN__)
	if (stat_buf.st_mode & PG_MODE_MASK_GROUP)
		ereport(FATAL,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("data directory \"%s\" has invalid permissions",
						DataDir),
				 errdetail("Permissions should be u=rwx (0700) or u=rwx,g=rx (0750).")));
#endif

	/*
	 * Reset creation modes and mask based on the mode of the data directory.
	 *
	 * The mask was set earlier in startup to disallow group permissions on
	 * newly created files and directories.  However, if group read/execute
	 * are present on the data directory then modify the create modes and mask
	 * to allow group read/execute on newly created files and directories and
	 * set the data_directory_mode GUC.
	 *
	 * Suppress when on Windows, because there may not be proper support for
	 * Unix-y file permissions.
	 */
#if !defined(WIN32) && !defined(__CYGWIN__)
	SetDataDirectoryCreatePerm(stat_buf.st_mode);

	umask(pg_mode_mask);
	data_directory_mode = pg_dir_create_mode;
#endif

	/* Check for PG_VERSION */
	ValidatePgVersion(DataDir);
}
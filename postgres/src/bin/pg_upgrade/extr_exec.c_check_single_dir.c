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
typedef  int /*<<< orphan*/  subDirName ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_FATAL ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  report_status (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*,char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_single_dir(const char *pg_data, const char *subdir)
{
	struct stat statBuf;
	char		subDirName[MAXPGPATH];

	snprintf(subDirName, sizeof(subDirName), "%s%s%s", pg_data,
	/* Win32 can't stat() a directory with a trailing slash. */
			 *subdir ? "/" : "",
			 subdir);

	if (stat(subDirName, &statBuf) != 0)
		report_status(PG_FATAL, "check for \"%s\" failed: %s\n",
					  subDirName, strerror(errno));
	else if (!S_ISDIR(statBuf.st_mode))
		report_status(PG_FATAL, "\"%s\" is not a directory\n",
					  subDirName);
}
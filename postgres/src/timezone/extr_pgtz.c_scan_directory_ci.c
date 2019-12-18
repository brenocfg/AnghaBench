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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char const*) ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 struct dirent* ReadDirExtended (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_strncasecmp (char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static bool
scan_directory_ci(const char *dirname, const char *fname, int fnamelen,
				  char *canonname, int canonnamelen)
{
	bool		found = false;
	DIR		   *dirdesc;
	struct dirent *direntry;

	dirdesc = AllocateDir(dirname);

	while ((direntry = ReadDirExtended(dirdesc, dirname, LOG)) != NULL)
	{
		/*
		 * Ignore . and .., plus any other "hidden" files.  This is a security
		 * measure to prevent access to files outside the timezone directory.
		 */
		if (direntry->d_name[0] == '.')
			continue;

		if (strlen(direntry->d_name) == fnamelen &&
			pg_strncasecmp(direntry->d_name, fname, fnamelen) == 0)
		{
			/* Found our match */
			strlcpy(canonname, direntry->d_name, canonnamelen);
			found = true;
			break;
		}
	}

	FreeDir(dirdesc);

	return found;
}
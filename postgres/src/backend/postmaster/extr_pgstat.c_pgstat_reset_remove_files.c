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
typedef  int /*<<< orphan*/  fname ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char const*) ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int MAXPGPATH ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void
pgstat_reset_remove_files(const char *directory)
{
	DIR		   *dir;
	struct dirent *entry;
	char		fname[MAXPGPATH * 2];

	dir = AllocateDir(directory);
	while ((entry = ReadDir(dir, directory)) != NULL)
	{
		int			nchars;
		Oid			tmp_oid;

		/*
		 * Skip directory entries that don't match the file names we write.
		 * See get_dbstat_filename for the database-specific pattern.
		 */
		if (strncmp(entry->d_name, "global.", 7) == 0)
			nchars = 7;
		else
		{
			nchars = 0;
			(void) sscanf(entry->d_name, "db_%u.%n",
						  &tmp_oid, &nchars);
			if (nchars <= 0)
				continue;
			/* %u allows leading whitespace, so reject that */
			if (strchr("0123456789", entry->d_name[3]) == NULL)
				continue;
		}

		if (strcmp(entry->d_name + nchars, "tmp") != 0 &&
			strcmp(entry->d_name + nchars, "stat") != 0)
			continue;

		snprintf(fname, sizeof(fname), "%s/%s", directory,
				 entry->d_name);
		unlink(fname);
	}
	FreeDir(dir);
}
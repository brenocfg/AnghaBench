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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pg_log_warning (char*,char const*) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ repalloc (char**,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

char	  **
pgfnames(const char *path)
{
	DIR		   *dir;
	struct dirent *file;
	char	  **filenames;
	int			numnames = 0;
	int			fnsize = 200;	/* enough for many small dbs */

	dir = opendir(path);
	if (dir == NULL)
	{
		pg_log_warning("could not open directory \"%s\": %m", path);
		return NULL;
	}

	filenames = (char **) palloc(fnsize * sizeof(char *));

	while (errno = 0, (file = readdir(dir)) != NULL)
	{
		if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
		{
			if (numnames + 1 >= fnsize)
			{
				fnsize *= 2;
				filenames = (char **) repalloc(filenames,
											   fnsize * sizeof(char *));
			}
			filenames[numnames++] = pstrdup(file->d_name);
		}
	}

	if (errno)
		pg_log_warning("could not read directory \"%s\": %m", path);

	filenames[numnames] = NULL;

	if (closedir(dir))
		pg_log_warning("could not close directory \"%s\": %m", path);

	return filenames;
}
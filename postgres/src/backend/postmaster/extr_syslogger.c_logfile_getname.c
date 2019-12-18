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
typedef  int /*<<< orphan*/  pg_time_t ;

/* Variables and functions */
 char* Log_directory ; 
 int /*<<< orphan*/  Log_filename ; 
 scalar_t__ MAXPGPATH ; 
 int /*<<< orphan*/  log_timezone ; 
 char* palloc (scalar_t__) ; 
 int /*<<< orphan*/  pg_localtime (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_strftime (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,scalar_t__) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
logfile_getname(pg_time_t timestamp, const char *suffix)
{
	char	   *filename;
	int			len;

	filename = palloc(MAXPGPATH);

	snprintf(filename, MAXPGPATH, "%s/", Log_directory);

	len = strlen(filename);

	/* treat Log_filename as a strftime pattern */
	pg_strftime(filename + len, MAXPGPATH - len, Log_filename,
				pg_localtime(&timestamp, log_timezone));

	if (suffix != NULL)
	{
		len = strlen(filename);
		if (len > 4 && (strcmp(filename + (len - 4), ".log") == 0))
			len -= 4;
		strlcpy(filename + len, suffix, MAXPGPATH - len);
	}

	return filename;
}
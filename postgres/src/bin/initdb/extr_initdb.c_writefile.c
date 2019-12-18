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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 

__attribute__((used)) static void
writefile(char *path, char **lines)
{
	FILE	   *out_file;
	char	  **line;

	if ((out_file = fopen(path, "w")) == NULL)
	{
		pg_log_error("could not open file \"%s\" for writing: %m", path);
		exit(1);
	}
	for (line = lines; *line != NULL; line++)
	{
		if (fputs(*line, out_file) < 0)
		{
			pg_log_error("could not write file \"%s\": %m", path);
			exit(1);
		}
		free(*line);
	}
	if (fclose(out_file))
	{
		pg_log_error("could not write file \"%s\": %m", path);
		exit(1);
	}
}
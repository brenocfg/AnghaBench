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
 int /*<<< orphan*/  PG_BINARY_W ; 
 char* PG_MAJORVERSION ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pg_data ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 char* psprintf (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
write_version_file(const char *extrapath)
{
	FILE	   *version_file;
	char	   *path;

	if (extrapath == NULL)
		path = psprintf("%s/PG_VERSION", pg_data);
	else
		path = psprintf("%s/%s/PG_VERSION", pg_data, extrapath);

	if ((version_file = fopen(path, PG_BINARY_W)) == NULL)
	{
		pg_log_error("could not open file \"%s\" for writing: %m", path);
		exit(1);
	}
	if (fprintf(version_file, "%s\n", PG_MAJORVERSION) < 0 ||
		fclose(version_file))
	{
		pg_log_error("could not write file \"%s\": %m", path);
		exit(1);
	}
	free(path);
}
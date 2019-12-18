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
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pg_data ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 char* psprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_null_conf(void)
{
	FILE	   *conf_file;
	char	   *path;

	path = psprintf("%s/postgresql.conf", pg_data);
	conf_file = fopen(path, PG_BINARY_W);
	if (conf_file == NULL)
	{
		pg_log_error("could not open file \"%s\" for writing: %m", path);
		exit(1);
	}
	if (fclose(conf_file))
	{
		pg_log_error("could not write file \"%s\": %m", path);
		exit(1);
	}
	free(path);
}
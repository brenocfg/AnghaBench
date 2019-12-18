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
typedef  int /*<<< orphan*/  rawline ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PG_MAJORVERSION ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  pg_log_info (char*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_strip_crlf (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CheckDataVersion(void)
{
	const char *ver_file = "PG_VERSION";
	FILE	   *ver_fd;
	char		rawline[64];

	if ((ver_fd = fopen(ver_file, "r")) == NULL)
	{
		pg_log_error("could not open file \"%s\" for reading: %m",
					 ver_file);
		exit(1);
	}

	/* version number has to be the first line read */
	if (!fgets(rawline, sizeof(rawline), ver_fd))
	{
		if (!ferror(ver_fd))
			pg_log_error("unexpected empty file \"%s\"", ver_file);
		else
			pg_log_error("could not read file \"%s\": %m", ver_file);
		exit(1);
	}

	/* strip trailing newline and carriage return */
	(void) pg_strip_crlf(rawline);

	if (strcmp(rawline, PG_MAJORVERSION) != 0)
	{
		pg_log_error("data directory is of wrong version");
		pg_log_info("File \"%s\" contains \"%s\", which is not compatible with this program's version \"%s\".",
					ver_file, rawline, PG_MAJORVERSION);
		exit(1);
	}

	fclose(ver_fd);
}
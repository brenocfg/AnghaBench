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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  pgpid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fscanf (int /*<<< orphan*/ *,char*,long*) ; 
 scalar_t__ ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_data ; 
 int /*<<< orphan*/  pid_file ; 
 int /*<<< orphan*/  progname ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  version_file ; 
 int /*<<< orphan*/  write_stderr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static pgpid_t
get_pgpid(bool is_status_request)
{
	FILE	   *pidf;
	long		pid;
	struct stat statbuf;

	if (stat(pg_data, &statbuf) != 0)
	{
		if (errno == ENOENT)
			write_stderr(_("%s: directory \"%s\" does not exist\n"), progname,
						 pg_data);
		else
			write_stderr(_("%s: could not access directory \"%s\": %s\n"), progname,
						 pg_data, strerror(errno));

		/*
		 * The Linux Standard Base Core Specification 3.1 says this should
		 * return '4, program or service status is unknown'
		 * https://refspecs.linuxbase.org/LSB_3.1.0/LSB-Core-generic/LSB-Core-generic/iniscrptact.html
		 */
		exit(is_status_request ? 4 : 1);
	}

	if (stat(version_file, &statbuf) != 0 && errno == ENOENT)
	{
		write_stderr(_("%s: directory \"%s\" is not a database cluster directory\n"),
					 progname, pg_data);
		exit(is_status_request ? 4 : 1);
	}

	pidf = fopen(pid_file, "r");
	if (pidf == NULL)
	{
		/* No pid file, not an error on startup */
		if (errno == ENOENT)
			return 0;
		else
		{
			write_stderr(_("%s: could not open PID file \"%s\": %s\n"),
						 progname, pid_file, strerror(errno));
			exit(1);
		}
	}
	if (fscanf(pidf, "%ld", &pid) != 1)
	{
		/* Is the file empty? */
		if (ftell(pidf) == 0 && feof(pidf))
			write_stderr(_("%s: the PID file \"%s\" is empty\n"),
						 progname, pid_file);
		else
			write_stderr(_("%s: invalid data in PID file \"%s\"\n"),
						 progname, pid_file);
		exit(1);
	}
	fclose(pidf);
	return (pgpid_t) pid;
}
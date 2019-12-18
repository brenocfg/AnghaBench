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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
check_input(char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
	{
		if (errno == ENOENT)
		{
			pg_log_error("file \"%s\" does not exist", path);
			fprintf(stderr,
					_("This might mean you have a corrupted installation or identified\n"
					  "the wrong directory with the invocation option -L.\n"));
		}
		else
		{
			pg_log_error("could not access file \"%s\": %m", path);
			fprintf(stderr,
					_("This might mean you have a corrupted installation or identified\n"
					  "the wrong directory with the invocation option -L.\n"));
		}
		exit(1);
	}
	if (!S_ISREG(statbuf.st_mode))
	{
		pg_log_error("file \"%s\" is not a regular file", path);
		fprintf(stderr,
				_("This might mean you have a corrupted installation or identified\n"
				  "the wrong directory with the invocation option -L.\n"));
		exit(1);
	}
}
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

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* _ (char*) ; 
 scalar_t__ chdir (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  mkdirs (char const*,int) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

__attribute__((used)) static void
change_directory(char const *dir)
{
	if (chdir(dir) != 0)
	{
		int			chdir_errno = errno;

		if (chdir_errno == ENOENT)
		{
			mkdirs(dir, false);
			chdir_errno = chdir(dir) == 0 ? 0 : errno;
		}
		if (chdir_errno != 0)
		{
			fprintf(stderr, _("%s: Can't chdir to %s: %s\n"),
					progname, dir, strerror(chdir_errno));
			exit(EXIT_FAILURE);
		}
	}
}
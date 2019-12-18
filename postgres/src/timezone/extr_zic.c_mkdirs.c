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
 int EEXIST ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  MKDIR_UMASK ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* ecpyalloc (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  itsdir (char*) ; 
 scalar_t__ mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progname ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static void
mkdirs(char const *argname, bool ancestors)
{
	char	   *name;
	char	   *cp;

	cp = name = ecpyalloc(argname);

	/*
	 * On MS-Windows systems, do not worry about drive letters or backslashes,
	 * as this should suffice in practice.  Time zone names do not use drive
	 * letters and backslashes.  If the -d option of zic does not name an
	 * already-existing directory, it can use slashes to separate the
	 * already-existing ancestor prefix from the to-be-created subdirectories.
	 */

	/* Do not mkdir a root directory, as it must exist.  */
	while (*cp == '/')
		cp++;

	while (cp && ((cp = strchr(cp, '/')) || !ancestors))
	{
		if (cp)
			*cp = '\0';

		/*
		 * Try to create it.  It's OK if creation fails because the directory
		 * already exists, perhaps because some other process just created it.
		 * For simplicity do not check first whether it already exists, as
		 * that is checked anyway if the mkdir fails.
		 */
		if (mkdir(name, MKDIR_UMASK) != 0)
		{
			/*
			 * For speed, skip itsdir if errno == EEXIST.  Since mkdirs is
			 * called only after open fails with ENOENT on a subfile, EEXIST
			 * implies itsdir here.
			 */
			int			err = errno;

			if (err != EEXIST && !itsdir(name))
			{
				error(_("%s: Cannot create directory %s: %s"),
					  progname, name, strerror(err));
				exit(EXIT_FAILURE);
			}
		}
		if (cp)
			*cp++ = '/';
	}
	free(name);
}
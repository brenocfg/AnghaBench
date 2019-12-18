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
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTDIR ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_IWUSR ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ mkdir (char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 
 int umask (int) ; 

int
pg_mkdir_p(char *path, int omode)
{
	struct stat sb;
	mode_t		numask,
				oumask;
	int			last,
				retval;
	char	   *p;

	retval = 0;
	p = path;

#ifdef WIN32
	/* skip network and drive specifiers for win32 */
	if (strlen(p) >= 2)
	{
		if (p[0] == '/' && p[1] == '/')
		{
			/* network drive */
			p = strstr(p + 2, "/");
			if (p == NULL)
			{
				errno = EINVAL;
				return -1;
			}
		}
		else if (p[1] == ':' &&
				 ((p[0] >= 'a' && p[0] <= 'z') ||
				  (p[0] >= 'A' && p[0] <= 'Z')))
		{
			/* local drive */
			p += 2;
		}
	}
#endif

	/*
	 * POSIX 1003.2: For each dir operand that does not name an existing
	 * directory, effects equivalent to those caused by the following command
	 * shall occur:
	 *
	 * mkdir -p -m $(umask -S),u+wx $(dirname dir) && mkdir [-m mode] dir
	 *
	 * We change the user's umask and then restore it, instead of doing
	 * chmod's.  Note we assume umask() can't change errno.
	 */
	oumask = umask(0);
	numask = oumask & ~(S_IWUSR | S_IXUSR);
	(void) umask(numask);

	if (p[0] == '/')			/* Skip leading '/'. */
		++p;
	for (last = 0; !last; ++p)
	{
		if (p[0] == '\0')
			last = 1;
		else if (p[0] != '/')
			continue;
		*p = '\0';
		if (!last && p[1] == '\0')
			last = 1;

		if (last)
			(void) umask(oumask);

		/* check for pre-existing directory */
		if (stat(path, &sb) == 0)
		{
			if (!S_ISDIR(sb.st_mode))
			{
				if (last)
					errno = EEXIST;
				else
					errno = ENOTDIR;
				retval = -1;
				break;
			}
		}
		else if (mkdir(path, last ? omode : S_IRWXU | S_IRWXG | S_IRWXO) < 0)
		{
			retval = -1;
			break;
		}
		if (!last)
			*p = '/';
	}

	/* ensure we restored umask */
	(void) umask(oumask);

	return retval;
}
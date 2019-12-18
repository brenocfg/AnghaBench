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
struct tztry {int dummy; } ;
typedef  int /*<<< orphan*/  link_target ;

/* Variables and functions */
 int MAXPGPATH ; 
 scalar_t__ TZ_STRLEN_MAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 scalar_t__ perfect_timezone_match (char const*,struct tztry*) ; 
 int readlink (char const*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static bool
check_system_link_file(const char *linkname, struct tztry *tt,
					   char *bestzonename)
{
#ifdef HAVE_READLINK
	char		link_target[MAXPGPATH];
	int			len;
	const char *cur_name;

	/*
	 * Try to read the symlink.  If not there, not a symlink, etc etc, just
	 * quietly fail; the precise reason needn't concern us.
	 */
	len = readlink(linkname, link_target, sizeof(link_target));
	if (len < 0 || len >= sizeof(link_target))
		return false;
	link_target[len] = '\0';

#ifdef DEBUG_IDENTIFY_TIMEZONE
	fprintf(stderr, "symbolic link \"%s\" contains \"%s\"\n",
			linkname, link_target);
#endif

	/*
	 * The symlink is probably of the form "/path/to/zones/zone/name", or
	 * possibly it is a relative path.  Nobody puts their zone DB directly in
	 * the root directory, so we can definitely skip the first component; but
	 * after that it's trial-and-error to identify which path component begins
	 * the zone name.
	 */
	cur_name = link_target;
	while (*cur_name)
	{
		/* Advance to next segment of path */
		cur_name = strchr(cur_name + 1, '/');
		if (cur_name == NULL)
			break;
		/* If there are consecutive slashes, skip all, as the kernel would */
		do
		{
			cur_name++;
		} while (*cur_name == '/');

		/*
		 * Test remainder of path to see if it is a matching zone name.
		 * Relative paths might contain ".."; we needn't bother testing if the
		 * first component is that.  Also defend against overlength names.
		 */
		if (*cur_name && *cur_name != '.' &&
			strlen(cur_name) <= TZ_STRLEN_MAX &&
			perfect_timezone_match(cur_name, tt))
		{
			/* Success! */
			strcpy(bestzonename, cur_name);
			return true;
		}
	}

	/* Couldn't extract a matching zone name */
	return false;
#else
	/* No symlinks?  Forget it */
	return false;
#endif
}
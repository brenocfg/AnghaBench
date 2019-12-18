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
struct passwd {int /*<<< orphan*/  pw_dir; } ;
typedef  int /*<<< orphan*/  home ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_home_path (char*) ; 
 struct passwd* getpwnam (char*) ; 
 char* psprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 

void
expand_tilde(char **filename)
{
	if (!filename || !(*filename))
		return;

	/*
	 * WIN32 doesn't use tilde expansion for file names. Also, it uses tilde
	 * for short versions of long file names, though the tilde is usually
	 * toward the end, not at the beginning.
	 */
#ifndef WIN32

	/* try tilde expansion */
	if (**filename == '~')
	{
		char	   *fn;
		char		oldp,
				   *p;
		struct passwd *pw;
		char		home[MAXPGPATH];

		fn = *filename;
		*home = '\0';

		p = fn + 1;
		while (*p != '/' && *p != '\0')
			p++;

		oldp = *p;
		*p = '\0';

		if (*(fn + 1) == '\0')
			get_home_path(home);	/* ~ or ~/ only */
		else if ((pw = getpwnam(fn + 1)) != NULL)
			strlcpy(home, pw->pw_dir, sizeof(home));	/* ~user */

		*p = oldp;
		if (strlen(home) != 0)
		{
			char	   *newfn;

			newfn = psprintf("%s%s", home, p);
			free(fn);
			*filename = newfn;
		}
	}
#endif

	return;
}
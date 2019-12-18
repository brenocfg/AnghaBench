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
 int ENOENT ; 
 int ENOTSUP ; 
 int EOF ; 
 int EPERM ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  close_file (int /*<<< orphan*/ *,char*,char const*) ; 
 char* directory ; 
 int errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int hardlinkerr (char const*,char const*) ; 
 scalar_t__ itsdir (char const*) ; 
 int itssymlink (char const*) ; 
 int /*<<< orphan*/  mkdirs (char const*,int) ; 
 char* progname ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 char* relname (char const*,char const*) ; 
 scalar_t__ remove (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 scalar_t__ symlink (char const*,char const*) ; 
 int /*<<< orphan*/  warning (char*,char*) ; 

__attribute__((used)) static void
dolink(char const *fromfield, char const *tofield, bool staysymlink)
{
	bool		todirs_made = false;
	int			link_errno;

	/*
	 * We get to be careful here since there's a fair chance of root running
	 * us.
	 */
	if (itsdir(fromfield))
	{
		fprintf(stderr, _("%s: link from %s/%s failed: %s\n"),
				progname, directory, fromfield, strerror(EPERM));
		exit(EXIT_FAILURE);
	}
	if (staysymlink)
		staysymlink = itssymlink(tofield);
	if (remove(tofield) == 0)
		todirs_made = true;
	else if (errno != ENOENT)
	{
		char const *e = strerror(errno);

		fprintf(stderr, _("%s: Can't remove %s/%s: %s\n"),
				progname, directory, tofield, e);
		exit(EXIT_FAILURE);
	}
	link_errno = staysymlink ? ENOTSUP : hardlinkerr(fromfield, tofield);
	if (link_errno == ENOENT && !todirs_made)
	{
		mkdirs(tofield, true);
		todirs_made = true;
		link_errno = hardlinkerr(fromfield, tofield);
	}
	if (link_errno != 0)
	{
#ifdef HAVE_SYMLINK
		bool		absolute = *fromfield == '/';
		char	   *linkalloc = absolute ? NULL : relname(fromfield, tofield);
		char const *contents = absolute ? fromfield : linkalloc;
		int			symlink_errno = symlink(contents, tofield) == 0 ? 0 : errno;

		if (!todirs_made
			&& (symlink_errno == ENOENT || symlink_errno == ENOTSUP))
		{
			mkdirs(tofield, true);
			if (symlink_errno == ENOENT)
				symlink_errno = symlink(contents, tofield) == 0 ? 0 : errno;
		}
		free(linkalloc);
		if (symlink_errno == 0)
		{
			if (link_errno != ENOTSUP)
				warning(_("symbolic link used because hard link failed: %s"),
						strerror(link_errno));
		}
		else
#endif							/* HAVE_SYMLINK */
		{
			FILE	   *fp,
					   *tp;
			int			c;

			fp = fopen(fromfield, "rb");
			if (!fp)
			{
				char const *e = strerror(errno);

				fprintf(stderr, _("%s: Can't read %s/%s: %s\n"),
						progname, directory, fromfield, e);
				exit(EXIT_FAILURE);
			}
			tp = fopen(tofield, "wb");
			if (!tp)
			{
				char const *e = strerror(errno);

				fprintf(stderr, _("%s: Can't create %s/%s: %s\n"),
						progname, directory, tofield, e);
				exit(EXIT_FAILURE);
			}
			while ((c = getc(fp)) != EOF)
				putc(c, tp);
			close_file(fp, directory, fromfield);
			close_file(tp, directory, tofield);
			if (link_errno != ENOTSUP)
				warning(_("copy used because hard link failed: %s"),
						strerror(link_errno));
#ifdef HAVE_SYMLINK
			else if (symlink_errno != ENOTSUP)
				warning(_("copy used because symbolic link failed: %s"),
						strerror(symlink_errno));
#endif
		}
	}
}
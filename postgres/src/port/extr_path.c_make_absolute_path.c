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
 int ERANGE ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 size_t MAXPGPATH ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getcwd (char*,size_t) ; 
 int /*<<< orphan*/  is_absolute_path (char const*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const*) ; 
 char* strerror (int) ; 
 int strlen (char const*) ; 

char *
make_absolute_path(const char *path)
{
	char	   *new;

	/* Returning null for null input is convenient for some callers */
	if (path == NULL)
		return NULL;

	if (!is_absolute_path(path))
	{
		char	   *buf;
		size_t		buflen;

		buflen = MAXPGPATH;
		for (;;)
		{
			buf = malloc(buflen);
			if (!buf)
			{
#ifndef FRONTEND
				ereport(ERROR,
						(errcode(ERRCODE_OUT_OF_MEMORY),
						 errmsg("out of memory")));
#else
				fprintf(stderr, _("out of memory\n"));
				return NULL;
#endif
			}

			if (getcwd(buf, buflen))
				break;
			else if (errno == ERANGE)
			{
				free(buf);
				buflen *= 2;
				continue;
			}
			else
			{
				int			save_errno = errno;

				free(buf);
				errno = save_errno;
#ifndef FRONTEND
				elog(ERROR, "could not get current working directory: %m");
#else
				fprintf(stderr, _("could not get current working directory: %s\n"),
						strerror(errno));
				return NULL;
#endif
			}
		}

		new = malloc(strlen(buf) + strlen(path) + 2);
		if (!new)
		{
			free(buf);
#ifndef FRONTEND
			ereport(ERROR,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("out of memory")));
#else
			fprintf(stderr, _("out of memory\n"));
			return NULL;
#endif
		}
		sprintf(new, "%s/%s", buf, path);
		free(buf);
	}
	else
	{
		new = strdup(path);
		if (!new)
		{
#ifndef FRONTEND
			ereport(ERROR,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("out of memory")));
#else
			fprintf(stderr, _("out of memory\n"));
			return NULL;
#endif
		}
	}

	/* Make sure punctuation is canonical, too */
	canonicalize_path(new);

	return new;
}
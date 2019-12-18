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
typedef  int /*<<< orphan*/  fullname ;

/* Variables and functions */
 int MAXPGPATH ; 
 int O_RDONLY ; 
 int PG_BINARY ; 
 int TZ_STRLEN_MAX ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 char* pg_TZDIR () ; 
 int /*<<< orphan*/  scan_directory_ci (char*,char const*,int,char*,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char const*) ; 

int
pg_open_tzfile(const char *name, char *canonname)
{
	const char *fname;
	char		fullname[MAXPGPATH];
	int			fullnamelen;
	int			orignamelen;

	/* Initialize fullname with base name of tzdata directory */
	strlcpy(fullname, pg_TZDIR(), sizeof(fullname));
	orignamelen = fullnamelen = strlen(fullname);

	if (fullnamelen + 1 + strlen(name) >= MAXPGPATH)
		return -1;				/* not gonna fit */

	/*
	 * If the caller doesn't need the canonical spelling, first just try to
	 * open the name as-is.  This can be expected to succeed if the given name
	 * is already case-correct, or if the filesystem is case-insensitive; and
	 * we don't need to distinguish those situations if we aren't tasked with
	 * reporting the canonical spelling.
	 */
	if (canonname == NULL)
	{
		int			result;

		fullname[fullnamelen] = '/';
		/* test above ensured this will fit: */
		strcpy(fullname + fullnamelen + 1, name);
		result = open(fullname, O_RDONLY | PG_BINARY, 0);
		if (result >= 0)
			return result;
		/* If that didn't work, fall through to do it the hard way */
		fullname[fullnamelen] = '\0';
	}

	/*
	 * Loop to split the given name into directory levels; for each level,
	 * search using scan_directory_ci().
	 */
	fname = name;
	for (;;)
	{
		const char *slashptr;
		int			fnamelen;

		slashptr = strchr(fname, '/');
		if (slashptr)
			fnamelen = slashptr - fname;
		else
			fnamelen = strlen(fname);
		if (!scan_directory_ci(fullname, fname, fnamelen,
							   fullname + fullnamelen + 1,
							   MAXPGPATH - fullnamelen - 1))
			return -1;
		fullname[fullnamelen++] = '/';
		fullnamelen += strlen(fullname + fullnamelen);
		if (slashptr)
			fname = slashptr + 1;
		else
			break;
	}

	if (canonname)
		strlcpy(canonname, fullname + orignamelen + 1, TZ_STRLEN_MAX + 1);

	return open(fullname, O_RDONLY | PG_BINARY, 0);
}
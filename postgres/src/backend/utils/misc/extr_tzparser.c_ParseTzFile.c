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
typedef  int /*<<< orphan*/  tzbuf ;
typedef  int /*<<< orphan*/  tzEntry ;
typedef  int /*<<< orphan*/  file_path ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char*) ; 
 int /*<<< orphan*/ * AllocateFile (char*,char*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GUC_check_errhint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUC_check_errmsg (char*,char const*,...) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  WHITESPACE ; 
 int addToArray (int /*<<< orphan*/ **,int*,int,int /*<<< orphan*/ *,int) ; 
 int errno ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_share_path (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isalpha (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  my_exec_path ; 
 scalar_t__ pg_strncasecmp (char*,char*,int) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  splitTzLine (char const*,int,char*,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validateTzEntry (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ParseTzFile(const char *filename, int depth,
			tzEntry **base, int *arraysize, int n)
{
	char		share_path[MAXPGPATH];
	char		file_path[MAXPGPATH];
	FILE	   *tzFile;
	char		tzbuf[1024];
	char	   *line;
	tzEntry		tzentry;
	int			lineno = 0;
	bool		override = false;
	const char *p;

	/*
	 * We enforce that the filename is all alpha characters.  This may be
	 * overly restrictive, but we don't want to allow access to anything
	 * outside the timezonesets directory, so for instance '/' *must* be
	 * rejected.
	 */
	for (p = filename; *p; p++)
	{
		if (!isalpha((unsigned char) *p))
		{
			/* at level 0, just use guc.c's regular "invalid value" message */
			if (depth > 0)
				GUC_check_errmsg("invalid time zone file name \"%s\"",
								 filename);
			return -1;
		}
	}

	/*
	 * The maximal recursion depth is a pretty arbitrary setting. It is hard
	 * to imagine that someone needs more than 3 levels so stick with this
	 * conservative setting until someone complains.
	 */
	if (depth > 3)
	{
		GUC_check_errmsg("time zone file recursion limit exceeded in file \"%s\"",
						 filename);
		return -1;
	}

	get_share_path(my_exec_path, share_path);
	snprintf(file_path, sizeof(file_path), "%s/timezonesets/%s",
			 share_path, filename);
	tzFile = AllocateFile(file_path, "r");
	if (!tzFile)
	{
		/*
		 * Check to see if the problem is not the filename but the directory.
		 * This is worth troubling over because if the installation share/
		 * directory is missing or unreadable, this is likely to be the first
		 * place we notice a problem during postmaster startup.
		 */
		int			save_errno = errno;
		DIR		   *tzdir;

		snprintf(file_path, sizeof(file_path), "%s/timezonesets",
				 share_path);
		tzdir = AllocateDir(file_path);
		if (tzdir == NULL)
		{
			GUC_check_errmsg("could not open directory \"%s\": %m",
							 file_path);
			GUC_check_errhint("This may indicate an incomplete PostgreSQL installation, or that the file \"%s\" has been moved away from its proper location.",
							  my_exec_path);
			return -1;
		}
		FreeDir(tzdir);
		errno = save_errno;

		/*
		 * otherwise, if file doesn't exist and it's level 0, guc.c's
		 * complaint is enough
		 */
		if (errno != ENOENT || depth > 0)
			GUC_check_errmsg("could not read time zone file \"%s\": %m",
							 filename);

		return -1;
	}

	while (!feof(tzFile))
	{
		lineno++;
		if (fgets(tzbuf, sizeof(tzbuf), tzFile) == NULL)
		{
			if (ferror(tzFile))
			{
				GUC_check_errmsg("could not read time zone file \"%s\": %m",
								 filename);
				return -1;
			}
			/* else we're at EOF after all */
			break;
		}
		if (strlen(tzbuf) == sizeof(tzbuf) - 1)
		{
			/* the line is too long for tzbuf */
			GUC_check_errmsg("line is too long in time zone file \"%s\", line %d",
							 filename, lineno);
			return -1;
		}

		/* skip over whitespace */
		line = tzbuf;
		while (*line && isspace((unsigned char) *line))
			line++;

		if (*line == '\0')		/* empty line */
			continue;
		if (*line == '#')		/* comment line */
			continue;

		if (pg_strncasecmp(line, "@INCLUDE", strlen("@INCLUDE")) == 0)
		{
			/* pstrdup so we can use filename in result data structure */
			char	   *includeFile = pstrdup(line + strlen("@INCLUDE"));

			includeFile = strtok(includeFile, WHITESPACE);
			if (!includeFile || !*includeFile)
			{
				GUC_check_errmsg("@INCLUDE without file name in time zone file \"%s\", line %d",
								 filename, lineno);
				return -1;
			}
			n = ParseTzFile(includeFile, depth + 1,
							base, arraysize, n);
			if (n < 0)
				return -1;
			continue;
		}

		if (pg_strncasecmp(line, "@OVERRIDE", strlen("@OVERRIDE")) == 0)
		{
			override = true;
			continue;
		}

		if (!splitTzLine(filename, lineno, line, &tzentry))
			return -1;
		if (!validateTzEntry(&tzentry))
			return -1;
		n = addToArray(base, arraysize, n, &tzentry, override);
		if (n < 0)
			return -1;
	}

	FreeFile(tzFile);

	return n;
}
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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* pstrdup (char*) ; 
 scalar_t__ scanner_isspace (char) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

bool
SplitDirectoriesString(char *rawstring, char separator,
					   List **namelist)
{
	char	   *nextp = rawstring;
	bool		done = false;

	*namelist = NIL;

	while (scanner_isspace(*nextp))
		nextp++;				/* skip leading whitespace */

	if (*nextp == '\0')
		return true;			/* allow empty string */

	/* At the top of the loop, we are at start of a new directory. */
	do
	{
		char	   *curname;
		char	   *endp;

		if (*nextp == '"')
		{
			/* Quoted name --- collapse quote-quote pairs */
			curname = nextp + 1;
			for (;;)
			{
				endp = strchr(nextp + 1, '"');
				if (endp == NULL)
					return false;	/* mismatched quotes */
				if (endp[1] != '"')
					break;		/* found end of quoted name */
				/* Collapse adjacent quotes into one quote, and look again */
				memmove(endp, endp + 1, strlen(endp));
				nextp = endp;
			}
			/* endp now points at the terminating quote */
			nextp = endp + 1;
		}
		else
		{
			/* Unquoted name --- extends to separator or end of string */
			curname = endp = nextp;
			while (*nextp && *nextp != separator)
			{
				/* trailing whitespace should not be included in name */
				if (!scanner_isspace(*nextp))
					endp = nextp + 1;
				nextp++;
			}
			if (curname == endp)
				return false;	/* empty unquoted name not allowed */
		}

		while (scanner_isspace(*nextp))
			nextp++;			/* skip trailing whitespace */

		if (*nextp == separator)
		{
			nextp++;
			while (scanner_isspace(*nextp))
				nextp++;		/* skip leading whitespace for next */
			/* we expect another name, so done remains false */
		}
		else if (*nextp == '\0')
			done = true;
		else
			return false;		/* invalid syntax */

		/* Now safe to overwrite separator with a null */
		*endp = '\0';

		/* Truncate path if it's overlength */
		if (strlen(curname) >= MAXPGPATH)
			curname[MAXPGPATH - 1] = '\0';

		/*
		 * Finished isolating current name --- add it to list
		 */
		curname = pstrdup(curname);
		canonicalize_path(curname);
		*namelist = lappend(*namelist, curname);

		/* Loop back if we didn't reach end of string */
	} while (!done);

	return true;
}